

#include "physics.h"

#include <math.h>



#define ROCKET_STATE_N 6

#define TIME_STEP	0.01



//static float rk4(float x, float h, float (*f)(float));

static ROCKET_STATE_t rocket_integrate_rk4(ROCKET_STATE_t x, ROCKET_INPUT_t u, float h, ROCKET_STATE_t (*f)(ROCKET_STATE_t, ROCKET_INPUT_t));

static ROCKET_STATE_t rocket_model_earth(ROCKET_STATE_t x, ROCKET_INPUT_t u);


static ROCKET_STATE_t rocket_model_moon(ROCKET_STATE_t x, ROCKET_INPUT_t u);

static ROCKET_STATE_t rocket_lin(ROCKET_STATE_t x, ROCKET_INPUT_t u);


//exported functions
//result must be N long
void physics_predict_orbit( IVEC_t * result, ROCKET_STATE_t x, int N) {
	ROCKET_INPUT_t u = {0, 0};

	int i;
	for(i = 0; i < N; i++) {
		x = rocket_integrate_rk4(x, u, TIME_STEP, rocket_model_earth);
		result[i].x = (int) x.x + 128;
		result[i].y = (int) x.y + 96;

	}
}

ROCKET_STATE_t physics_step_lin(ROCKET_STATE_t x, ROCKET_INPUT_t u) {
	return rocket_integrate_rk4(x, u, TIME_STEP, rocket_lin);
}


ROCKET_STATE_t physics_step_grav(ROCKET_STATE_t x, ROCKET_INPUT_t u, uint8_t moon) {
	if(moon){
		return rocket_integrate_rk4(x, u, TIME_STEP, rocket_model_moon);
	} else {
		return rocket_integrate_rk4(x, u, TIME_STEP, rocket_model_earth);
	}
}



void physics_world_boundary(ROCKET_STATE_t * x) {
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

float physics_get_phi_earth(ROCKET_STATE_t x) {
	float vx = -EARTH_X+x.x;
	float vy = -EARTH_Y+x.y;


	float phi = atan2(vy, vx);

	return phi;

}

float physics_get_r_earth(ROCKET_STATE_t x) {
	float vx = -EARTH_X+x.x;
	float vy = -EARTH_Y+x.y;


	float r = sqrt(vy*vy+ vx*vx);

	return r;
}

float physics_get_phi_moon(ROCKET_STATE_t x) {
	float vx = -MOON_X+x.x;
	float vy = -MOON_Y+x.y;


	float phi = atan2(vy, vx);

	return phi;

}

float physics_get_r_moon(ROCKET_STATE_t x) {
	float vx = -MOON_X+x.x;
	float vy = -MOON_Y+x.y;


	float r = sqrt(vy*vy+ vx*vx);

	return r;
}

float physics_get_vel(ROCKET_STATE_t x) {

	float vel = sqrt(x.xp*x.xp+x.yp*x.yp);

	return vel;
}

float physics_get_theta(ROCKET_STATE_t x) {
	float theta = atan2(x.xp, -x.yp);
	return theta;
}

void physics_angle_reach(float * subject, float target) {
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

//Linear model used initially to test the rk4
static ROCKET_STATE_t rocket_lin(ROCKET_STATE_t x, ROCKET_INPUT_t u) {
	ROCKET_STATE_t dx;

	dx.x = x.xp;
	dx.y = x.yp;
	dx.a = x.ap;

	dx.xp = sin(x.a)*u.Ft*ROCKET_INV_MASS;
	dx.yp = -cos(x.a)*u.Ft*ROCKET_INV_MASS;
	dx.ap = u.Tt*ROCKET_INV_INERTIA;

	return dx;
}



static ROCKET_STATE_t rocket_model_earth(ROCKET_STATE_t x, ROCKET_INPUT_t u) {
	float GM = 1e3;
	ROCKET_STATE_t dx;

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

static ROCKET_STATE_t rocket_model_moon(ROCKET_STATE_t x, ROCKET_INPUT_t u) {
	float GM = 10e2;
	ROCKET_STATE_t dx;

	float vx = -MOON_X+x.x;
	float vy = -MOON_Y+x.y;


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

/*

static float rk4(float x, float h, float (*f)(float)) {
	float k1 = f(x);
	float k2 = f(x + h/2 * k1);
	float k3 = f(x + h/2 * k2);
	float k4 = f(x + h * k3);
	return x + h/6*(k1 + 2*k2 + 2*k3 + k4);
}

*/

static ROCKET_STATE_t rocket_integrate_rk4(ROCKET_STATE_t x, ROCKET_INPUT_t u, float h, ROCKET_STATE_t (*f)(ROCKET_STATE_t, ROCKET_INPUT_t)) {
	ROCKET_STATE_t k1, k2, k3, k4, tx, dx = {0};


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
