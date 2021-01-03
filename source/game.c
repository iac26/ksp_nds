

#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "game.h"

typedef struct {
	float x;
	float xp;
	float y;
	float yp;
	float a;
	float ap;
}ROCKET_STATE_t;

typedef struct {
	float Ft;
	float Tt;
}ROCKET_INPUT_t;

#define ROCKET_STATE_N 6

#define TIME_STEP	0.1



static float rk4(float x, float h, float (*f)(float));

static ROCKET_STATE_t rocket_integrate_rk4(ROCKET_STATE_t x, ROCKET_INPUT_t u, float h, ROCKET_STATE_t (*f)(ROCKET_STATE_t, ROCKET_INPUT_t));

static ROCKET_STATE_t rocket_model(ROCKET_STATE_t x, ROCKET_INPUT_t u);



//STATIC FUNCTIONS

static ROCKET_STATE_t rocket_model(ROCKET_STATE_t x, ROCKET_INPUT_t u) {
	float GM = 1e4;
	float m = 1;
	float I = 1;
	ROCKET_STATE_t dx;


	float phi = atan2(x.y, x.x);
	float r = sqrt(x.x*x.x + x.y*x.y);

	float ag = -GM/(r*r);

	dx.x = x.xp;
	dx.y = x.yp;
	dx.a = x.ap;

	dx.xp = cos(phi)*ag + cos(x.a)*u.Ft/m;
	dx.yp = sin(phi)*ag + sin(x.a)*u.Ft/m;
	dx.ap = u.Tt/I;

	return dx;
}


static float rk4(float x, float h, float (*f)(float)) {
	float k1 = f(x);
	float k2 = f(x + h/2 * k1);
	float k3 = f(x + h/2 * k2);
	float k4 = f(x + h * k3);
	return x + h/6*(k1 + 2*k2 + 2*k3 + k4);
}

static ROCKET_STATE_t rocket_integrate_rk4(ROCKET_STATE_t x, ROCKET_INPUT_t u, float h, ROCKET_STATE_t (*f)(ROCKET_STATE_t, ROCKET_INPUT_t)) {
	ROCKET_STATE_t k1, k2, k3, k4, dx = {0};
	float * px  = &( x.x);
	float * p1  = &(k1.x);
	float * p2  = &(k2.x);
	float * p3  = &(k3.x);
	float * p4  = &(k4.x);
	float * pdx = &(dx.x);

	k1 = f(x, u);

	for(int i = 0; i < ROCKET_STATE_N; i++) {
		p2[i] = px[i] + h/2 + p1[i];
	}

	k2 = f(k2, u);

	for(int i = 0; i < ROCKET_STATE_N; i++) {
		p3[i] = px[i] + h/2 + p2[i];
	}

	k3 = f(k3, u);

	for(int i = 0; i < ROCKET_STATE_N; i++) {
		p4[i] = px[i] + h + p3[i];
	}

	k4 = f(k4, u);

	for(int i = 0; i < ROCKET_STATE_N; i++) {
		pdx[i] = h/6*(p1[i] + 2*p2[i] + 2*p3[i] + p4[i]);
	}

	return dx;
}





//PUBLIC FUNCTIONS

void game_init(GAME_STATE_t * state) {

}

void game_splash(GAME_STATE_t * state) {

}

void game_ingame(GAME_STATE_t * state) {

}

void game_end(GAME_STATE_t * state) {

}




