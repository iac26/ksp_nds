

#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "game.h"
#include "physics.h"
#include "positions.h"



//PRIVATE FUNCTIONS

float get_rcs(CONTROLS_t controls) {
	float rcs = 0;
	if (controls.keysH & KEY_UP) {
		rcs += 1;
	}
	if (controls.keysH & KEY_DOWN) {
		rcs -= 1;
	}

	return rcs;
}

void update_thrust(CONTROLS_t * controls) {

	if (controls->keysD & KEY_RIGHT) {
		if(controls->slider_pos < SLIDER_POS_MAX) {
			controls->slider_pos += 1;
		}
	}
	if (controls->keysD & KEY_LEFT) {
		if(controls->slider_pos > SLIDER_POS_MIN) {
			controls->slider_pos -= 1;
		}
	}
	controls->slider_val = SLIDER_POS2VAL(controls->slider_pos);
}




//PUBLIC FUNCTIONS

void game_init(GAME_STATE_t * state) {
	state->game_fsm = SPLASH;
	state->control_input.ap_mode = AP_OFF;
	state->control_input.slider_pos = 3;
	state->control_input.slider_val = 0;
	state->rocket.x = 128;
	state->rocket.xp = 2;
	state->rocket.y = 10;
	state->rocket.yp = 0;
	state->rocket.a = 0;
	state->rocket.ap = 0;
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

	//update control inputs

	ROCKET_INPUT_t input;

	input.Tt = get_rcs(state->control_input);

	update_thrust(&state->control_input);

	input.Ft = (float)state->control_input.slider_val*ROCKET_THRUST;


	//update rocket dynamics

	state->rocket = physics_step_grav(state->rocket, input);

	float phi = physics_get_phi(state->rocket);

	physics_world_boundary(&state->rocket);

	IVEC_t orb[] = {{state->rocket.x, state->rocket.y}};




	//update display

	graphics_sub_put_slider(state->control_input.slider_pos);
	graphics_sub_set_ap(state->control_input.ap_mode);
	graphics_sub_put_speed(0);
	graphics_sub_put_alt(0);
	graphics_sub_put_nav(state->rocket.a, 2);
	graphics_sub_put_hor(ROCKET_CORRECT_ANGLE(phi), 0.2, -30);

	graphics_main_path(orb, 1);

}

void game_end(GAME_STATE_t * state) {
	state->game_fsm = SPLASH;
	graphics_main_config_splash();
	graphics_sub_config_splash();
}




