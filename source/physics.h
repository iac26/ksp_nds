#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>


typedef struct {
	int x;
	int y;
}IVEC_t;

typedef struct {
	float x;
	float y;
}FVEC_t;

typedef struct {
	float x;
	float xp;
	float y;
	float yp;
	float a;
	float ap;
	float last_phi;
	float last_rs;
}ROCKET_STATE_t;

typedef struct {
	float Ft;
	float Tt;
}ROCKET_INPUT_t;

#ifndef M_PI
	#define M_PI	3.14159265358979323846264338327950288
#endif



#define WORLD_X_MAX	(256)
#define WORLD_Y_MAX	(192)
#define WORLD_X_MIN	(0)
#define WORLD_Y_MIN	(0)
#define WORLD_X_SIZE	(WORLD_X_MAX-WORLD_X_MIN)
#define WORLD_Y_SIZE	(WORLD_Y_MAX-WORLD_Y_MIN)

#define EARTH_X		(WORLD_X_MAX/2)
#define EARTH_Y		(WORLD_Y_MAX/2)

#define MOON_X		(224)
#define MOON_Y		(96)

#define MOON_SOI	(30)


#define ROCKET_INERTIA (0.5)
#define ROCKET_INV_INERTIA	(1/(float)ROCKET_INERTIA)

#define ROCKET_MASS		(10)
#define ROCKET_INV_MASS	(1/(float)ROCKET_MASS)

#define ROCKET_THRUST (0.01)

#define ROCKET_CORRECT_ANGLE(a) ((a)+M_PI/2)


void physics_predict_orbit( IVEC_t * result, ROCKET_STATE_t x, int N);

ROCKET_STATE_t physics_step_lin(ROCKET_STATE_t x, ROCKET_INPUT_t u);

ROCKET_STATE_t physics_step_grav(ROCKET_STATE_t x, ROCKET_INPUT_t u, uint8_t moon);

float physics_get_phi_earth(ROCKET_STATE_t x);
float physics_get_r_earth(ROCKET_STATE_t x);
float physics_get_phi_moon(ROCKET_STATE_t x);
float physics_get_r_moon(ROCKET_STATE_t x);
float physics_get_vel(ROCKET_STATE_t x);
float physics_get_theta(ROCKET_STATE_t x);

void physics_world_boundary(ROCKET_STATE_t * x);

void physics_angle_reach(float * subject, float target);



#endif
