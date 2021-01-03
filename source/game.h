#ifndef GAME_H
#define GAME_H


#include <nds.h>
#include "input.h"
#include "graphics_main.h"
#include "graphics_sub.h"


typedef enum {
	SPLASH,
	INGAME,
	END,
	GAME_FSM_N
}GAME_FSM_t;

typedef enum {
	LAUNCHPAD,
	FLIGHT_ATMOS,
	FLIGHT_EARTH,
	FLIGHT_MOON,
	LANDED,
	CRASHED,
	FLIGHT_FSM_N
}FLIGHT_FSM_t;

typedef struct {
	GAME_FSM_t game_fsm;
	FLIGHT_FSM_t flight_fsm;
	CONTROLS_t control_input;


}GAME_STATE_t;





void game_init(GAME_STATE_t * state);

void game_splash(GAME_STATE_t * state);

void game_ingame(GAME_STATE_t * state);

void game_end(GAME_STATE_t * state);



#endif
