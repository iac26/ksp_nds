

#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "game.h"
#include "physics.h"






//PUBLIC FUNCTIONS

void game_init(GAME_STATE_t * state) {
	state->game_fsm = SPLASH;
	state->control_input.ap_mode = AP_OFF;
	state->control_input.slider_pos = 3;
	state->control_input.slider_val = 0;
	graphics_main_config_splash();
	graphics_sub_config_splash();
}

void game_splash(GAME_STATE_t * state) {
	if(state->control_input.keysD & (KEY_START | KEY_TOUCH)) {
		state->game_fsm = INGAME;
		graphics_main_config_ingame();
		graphics_sub_config_ingame();
	}


}

void game_ingame(GAME_STATE_t * state) {
	//update game dynamics

	IVEC_t orb[1];
	ROCKET_STATE_t x0 = {0, -0.5, 25, 0, 0, 0};

	physics_predict_orbit(orb, x0, 1);

	//update display

	graphics_sub_put_slider(state->control_input.slider_pos);
	graphics_sub_set_ap(state->control_input.ap_mode);
	graphics_sub_put_speed(0);
	graphics_sub_put_alt(0);
	graphics_sub_put_nav(0, 2);
	graphics_sub_put_hor(1.5, 0.2, -30);

	graphics_main_path(orb, 1);

}

void game_end(GAME_STATE_t * state) {
	state->game_fsm = SPLASH;
	graphics_main_config_splash();
	graphics_sub_config_splash();
}




