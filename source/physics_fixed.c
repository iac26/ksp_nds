

#include "physics_fixed.h"

#include <math.h>
#include <nds.h>


#define TIME_STEP	0.01




static ROCKET_STATE_FIXED_t rocket_integrate_rk4_fixed(ROCKET_STATE_FIXED_t x, ROCKET_INPUT_FIXED_t u, int32_t h, ROCKET_STATE_FIXED_t (*f)(ROCKET_STATE_FIXED_t, ROCKET_INPUT_FIXED_t));

static ROCKET_STATE_FIXED_t rocket_model_fixed(ROCKET_STATE_FIXED_t x, ROCKET_INPUT_FIXED_t u);


//ABANDON TOO HARD TO DO....

int32_t arctan2_fixed(int32_t y, int32_t x)
{
   int32_t abs_y = abs(y)+0x1;  // kludge to prevent 0/0 condition
   int32_t r;
   int32_t angle;
   if (x>=0)
   {
      r = (x - abs_y) / (x + abs_y);
      angle = M_PI_4_FIXED - M_PI_4_FIXED * r;
   }
   else
   {
      r = (x + abs_y) / (abs_y - x);
      angle = M_3_PI_4_FIXED - M_PI_4_FIXED * r;
   }
   if (y < 0)
   return(-angle);     // negate if in quad III or IV
   else
   return(angle);
}


ROCKET_STATE_FIXED_t physics_step_grav_fixed(ROCKET_STATE_FIXED_t x, ROCKET_INPUT_FIXED_t u) {
	return rocket_integrate_rk4_fixed(x, u, TIME_STEP, rocket_model_fixed);
}


void physics_world_boundary_fixed(ROCKET_STATE_FIXED_t * x) {
	while(x->x < WORLD_X_MIN) {
		x->x += WORLD_X_SIZE;
	}
	while(x->x >= WORLD_X_MAX) {
		x->x -= WORLD_X_SIZE;
	}
	while(x->y < WORLD_Y_MIN) {
		x->y += WORLD_Y_SIZE;
	}
	while(x->y >= WORLD_Y_MAX) {
		x->y -= WORLD_Y_SIZE;
	}
}

float physics_get_phi_fixed(ROCKET_STATE_FIXED_t x) {
	int32_t vx = -EARTH_X+x.x;
	int32_t vy = -EARTH_Y+x.y;


	int32_t phi = atan2(vy, vx);

	return phi;

}

float physics_get_r_fixed(ROCKET_STATE_FIXED_t x) {
	float vx = -EARTH_X+x.x;
	float vy = -EARTH_Y+x.y;


	float r = sqrt(vy*vy+ vx*vx);

	return r;
}

float physics_get_vel_fixed(ROCKET_STATE_FIXED_t x) {

	float vel = sqrt(x.xp*x.xp+x.yp*x.yp);

	return vel;
}

float physics_get_theta_fixed(ROCKET_STATE_FIXED_t x) {
	float theta = atan2(x.xp, -x.yp);
	return theta;
}

void physics_angle_reach_fixed(float * subject, float target) {
	if(*subject < target) {
		while (*subject < target-M_PI) {
			*subject += 2*M_PI;
		}
	} else {
		while (*subject > target+M_PI) {
			*subject -= 2*M_PI;
		}
	}
}

//STATIC FUNCTIONS

//CREATE A FIXED POINT MODEL
//MAYBE NOT AS IT WORKS ON THE NDS
static ROCKET_STATE_FIXED_t rocket_model_fixed(ROCKET_STATE_FIXED_t x, ROCKET_INPUT_FIXED_t u) {
	float GM = 1e3;
	ROCKET_STATE_FIXED_t dx;

	float vx = -EARTH_X+x.x;
	float vy = -EARTH_Y+x.y;


	float phi = atan2(vy, vx);
	float rs = vx*vx + vy*vy;

	float ag = -GM/(rs);

	dx.x = x.xp;
	dx.y = x.yp;
	dx.a = x.ap;

	dx.xp = cos(phi)*ag + sin(x.a)*u.Ft*ROCKET_INV_MASS;
	dx.yp = sin(phi)*ag - cos(x.a)*u.Ft*ROCKET_INV_MASS;
	dx.ap = u.Tt*ROCKET_INV_INERTIA;

	return dx;
}


static ROCKET_STATE_FIXED_t rocket_integrate_rk4_fixed(ROCKET_STATE_FIXED_t x, ROCKET_INPUT_FIXED_t u, int32_t h, ROCKET_STATE_FIXED_t (*f)(ROCKET_STATE_FIXED_t, ROCKET_INPUT_FIXED_t)) {
	ROCKET_STATE_FIXED_t k1, k2, k3, k4, tx, dx = {0};


	k1 = f(x, u);


	tx.x  = x.x  + h*0.5 * k1.x;
	tx.xp = x.xp + h*0.5 * k1.xp;
	tx.y  = x.y  + h*0.5 * k1.y;
	tx.yp = x.yp + h*0.5 * k1.yp;
	tx.a  = x.a  + h*0.5 * k1.a;
	tx.ap = x.ap + h*0.5 * k1.ap;

	k2 = f(tx, u);

	tx.x  = x.x  + h*0.5 * k2.x;
	tx.xp = x.xp + h*0.5 * k2.xp;
	tx.y  = x.y  + h*0.5 * k2.y;
	tx.yp = x.yp + h*0.5 * k2.yp;
	tx.a  = x.a  + h*0.5 * k2.a;
	tx.ap = x.ap + h*0.5 * k2.ap;

	k3 = f(tx, u);

	tx.x  = x.x  + h * k3.x;
	tx.xp = x.xp + h * k3.xp;
	tx.y  = x.y  + h * k3.y;
	tx.yp = x.yp + h * k3.yp;
	tx.a  = x.a  + h * k3.a;
	tx.ap = x.ap + h * k3.ap;

	k4 = f(tx, u);

	dx.x  = x.x  + h*0.16667*(k1.x  + 2*k2.x  + 2*k3.x  + k4.x );
	dx.xp = x.xp + h*0.16667*(k1.xp + 2*k2.xp + 2*k3.xp + k4.xp);
	dx.y  = x.y  + h*0.16667*(k1.y  + 2*k2.y  + 2*k3.y  + k4.y );
	dx.yp = x.yp + h*0.16667*(k1.yp + 2*k2.yp + 2*k3.yp + k4.yp);
	dx.a  = x.a  + h*0.16667*(k1.a  + 2*k2.a  + 2*k3.a  + k4.a );
	dx.ap = x.ap + h*0.16667*(k1.ap + 2*k2.ap + 2*k3.ap + k4.ap);

	return dx;
}

