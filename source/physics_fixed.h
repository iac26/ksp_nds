#ifndef PHYSICS_FIXED_H
#define PHYSICS_FIXED_H

#include <math.h>
#include <nds.h>

#include "physics.h"

/*
 * FIXED POINT PHYSICS format: signed 20.12
 */
typedef struct {
	int32_t x;
	int32_t y;
}VEC_FIXED_t;

typedef struct {
	int32_t x;
	int32_t xp;
	int32_t y;
	int32_t yp;
	int32_t a;
	int32_t ap;
	int32_t last_phi;
	int32_t last_rs;
}ROCKET_STATE_FIXED_t;

typedef struct {
	int32_t Ft;
	int32_t Tt;
}ROCKET_INPUT_FIXED_t;

#ifndef M_PI
	#define M_PI	3.14159265358979323846264338327950288
	#define M_PI_2	M_PI/2
	#define M_PI_4	M_PI_2/2
#endif


#define M_PI_FIXED 	 	floatToFixed(M_PI, 12)
#define M_PI_2_FIXED 	floatToFixed(M_PI_2, 12)
#define M_PI_4_FIXED 	floatToFixed(M_PI_4, 12)
#define M_3_PI_4_FIXED	floatToFixed(3*M_PI_4, 12)


#define WORLD_X_MAX_FIXED 		floatToFixed(WORLD_X_MAX, 12)
#define WORLD_Y_MAX_FIXED		floatToFixed(WORLD_Y_MAX, 12)
#define WORLD_X_MIN_FIXED		floatToFixed(WORLD_X_MIN, 12)
#define WORLD_Y_MIN_FIXED		floatToFixed(WORLD_Y_MIN, 12)
#define WORLD_X_SIZE_FIXED		floatToFixed(WORLD_X_SIZE, 12)
#define WORLD_Y_SIZE_FIXED		floatToFixed(WORLD_Y_SIZE, 12)

#define EARTH_X_FIXED			floatToFixed(EARTH_X, 12)
#define EARTH_Y_FIXED			floatToFixed(EARTH_Y, 12)


#define ROCKET_INERTIA_FIXED 		floatToFixed(ROCKET_INERTIA, 12);
#define ROCKET_INV_INERTIA_FIXED	floatToFixed(ROCKET_INV_INERTIA, 12);

#define ROCKET_MASS_FIXED		floatToFixed(ROCKET_MASS, 12);
#define ROCKET_INV_MASS_FIXED	floatToFixed(ROCKET_INV_MASS, 12);

#define ROCKET_THRUST_FIXED		floatToFixed(ROCKET_THRUST, 12);

#define ROCKET_CORRECT_ANGLE_FIXED(a) ((a)+M_PI_2_FIXED)




ROCKET_STATE_FIXED_t physics_step_grav_fixed(ROCKET_STATE_FIXED_t x, ROCKET_INPUT_FIXED_t u);

float physics_get_phi_fixed(ROCKET_STATE_FIXED_t x);
float physics_get_r_fixed(ROCKET_STATE_FIXED_t x);
float physics_get_vel_fixed(ROCKET_STATE_FIXED_t x);
float physics_get_theta_fixed(ROCKET_STATE_FIXED_t x);

void physics_world_boundary_fixed(ROCKET_STATE_FIXED_t * x);

void physics_angle_reach_fixed(float * subject, float target);



#endif
