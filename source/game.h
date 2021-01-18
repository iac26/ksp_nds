#ifndef GAME_H
#define GAME_H


#include <nds.h>
#include "input.h"
#include "graphics_main.h"
#include "graphics_sub.h"
#include "physics.h"


typedef enum {
	SPLASH,
	INGAME,
	CRASH,
	PAUSE,
}GAME_FSM_t;

typedef enum {
	EARTH,
	MOON,
	WALL
}CRASH_TYPE_t;

typedef struct {
	GAME_FSM_t game_fsm;
	GAME_FSM_t previous;
	CONTROLS_t control_input;
	ROCKET_STATE_t rocket;
	CRASH_TYPE_t crash_type;
	uint8_t intro;
	float r_moon;
	float r_earth;
	float r;
	float phi_earth;
	float phi_moon;
	float phi;
	float vel;
	uint8_t moon;

}GAME_STATE_t;





void game_init(GAME_STATE_t * state);

void game_splash(GAME_STATE_t * state);

void game_intro(GAME_STATE_t * state);

void game_exit_intro(GAME_STATE_t * state);

void game_ingame(GAME_STATE_t * state);

void game_init_crash(GAME_STATE_t * state);

void game_crash(GAME_STATE_t * state);

void game_pause(GAME_STATE_t * state);





#endif
