/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include <math.h>

#include "graphics_main.h"
#include "graphics_sub.h"
#include "input.h"
#include "game.h"










int main(void) {
	static GAME_STATE_t game_state;

	game_init(&game_state);

	input_init(&game_state.control_input);


	graphics_main_init();
	graphics_sub_init();

	game_state.game_fsm = SPLASH;

	//do the right configuration for the main and sub screens


	while(1) {
		swiWaitForVBlank();
		input_read(&game_state.control_input);
		if(game_state.control_input.intro) {
			game_intro(&game_state);
			continue;
		}else{
			game_exit_intro(&game_state);

		}
		switch(game_state.game_fsm) {
		case SPLASH:
			game_splash(&game_state);
			break;
		case INGAME:
			game_ingame(&game_state);
			break;
		case CRASH:
			game_crash(&game_state);
			break;
		case PAUSE:
			game_pause(&game_state);
			break;
		default:
			game_splash(&game_state);
			break;
		}
	}
}


