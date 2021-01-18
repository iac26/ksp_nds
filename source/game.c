

#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "game.h"
#include "physics.h"
#include "positions.h"
#include "sound.h"



//PRIVATE FUNCTIONS

float get_rcs(CONTROLS_t controls) {
	float rcs = 0;
	if (controls.keysH & KEY_UP) {
		rcs -= 1;
	}
	if (controls.keysH & KEY_DOWN) {
		rcs += 1;
	}

	return rcs;
}

void update_thrust(CONTROLS_t * controls) {

	if (controls->keysDR & KEY_RIGHT) {
		if(controls->slider_pos < SLIDER_POS_MAX) {
			controls->slider_pos += 1;
		}
	}
	if (controls->keysDR & KEY_LEFT) {
		if(controls->slider_pos > SLIDER_POS_MIN) {
			controls->slider_pos -= 1;
		}
	}
	controls->slider_val = SLIDER_POS2VAL(controls->slider_pos);
}


int get_rocket_type(CONTROLS_t controls) {
	if(controls.slider_val < 10) {
		return 0;
	} else if (controls.slider_val < 70) {
		return 1;
	} else {
		return 2;
	}
}

typedef enum {ANGLE, ANGVEL, OFF}AP_FUNC;

float auto_pilot(GAME_STATE_t * state) {
	float theta = physics_get_theta(state->rocket);
	float rcs = 0;
	float target = 0;
	AP_FUNC mode = OFF;
	switch (state->control_input.ap_mode) {
	case AP_PROGRADE:
		target = theta;
		mode = ANGLE;
		break;
	case AP_RETROGRADE:
		target = theta - M_PI;
		mode = ANGLE;
		break;
	case AP_RADIAL:
		target = theta + M_PI/2;
		mode = ANGLE;
		break;
	case AP_ANTIRADIAL:
		target = theta - M_PI/2;
		mode = ANGLE;
		break;
	case AP_KILL_ROT:
		target = 0;
		mode = ANGVEL;
		break;
	default:
		mode = OFF;
		break;
	}
	float err = 0;
	float kpp = 1;
	float kpv = 1;
	float perr = 0;
	if(mode == ANGLE) {
		physics_angle_reach(&target, state->rocket.a);
		perr = target-state->rocket.a;
		target = kpp*perr;
	}
	if(mode != OFF) {
		err = target - state->rocket.ap;
		rcs = kpv*err;
	}
	return rcs;
}



//PUBLIC FUNCTIONS

void game_init(GAME_STATE_t * state) {
	state->game_fsm = SPLASH;
	state->control_input.ap_mode = AP_OFF;
	state->control_input.slider_pos = SLIDER_POS_X;
	state->control_input.slider_val = 0;
	state->rocket.x = 128;
	state->rocket.xp = 6;
	state->rocket.y = 70;
	state->rocket.yp = 0;
	state->rocket.a = M_PI_2;
	state->rocket.ap = 0;
	state->moon = 0;
	graphics_main_config_splash();
	graphics_sub_config_splash();
}

void game_splash(GAME_STATE_t * state) {
	if(state->control_input.keysD & (KEY_START | KEY_TOUCH | KEY_A )) {
		state->game_fsm = INGAME;
		graphics_main_config_ingame();
		graphics_sub_config_ingame();
		graphics_main_clear_path();
		state->control_input.abort = 0;
	}

}

void game_intro(GAME_STATE_t * state){
	if(!state->intro) {
		graphics_main_config_intro();
		graphics_sub_config_intro();
		state->intro = 1;
		state->previous = state->game_fsm;
	}
}

void game_exit_intro(GAME_STATE_t * state) {
	if(state->intro) {
		state->intro = 0;
		switch(state->previous) {
		case INGAME:
			graphics_main_config_ingame();
			graphics_sub_config_ingame();
			break;
		case CRASH:
			game_init_crash(state);
			break;
		case PAUSE:
			graphics_main_config_ingame();
			graphics_sub_config_pause();
			break;
		case SPLASH:
			graphics_main_config_splash();
			graphics_sub_config_splash();
			break;
		}
	}
}

void game_ingame(GAME_STATE_t * state) {
	//update game dynamics

	if(state->control_input.keysD & (KEY_START | KEY_A)) {
		state->game_fsm = PAUSE;
		graphics_sub_config_pause();
		return;
	}
	if((state->control_input.keysD & KEY_B) || state->control_input.abort) {
		graphics_main_clear_path();
		game_init(state);
		return;
	}

	//update control inputs
	ROCKET_INPUT_t input;

	input.Tt = get_rcs(state->control_input);

	update_thrust(&state->control_input);

	input.Ft = (float)state->control_input.slider_val*ROCKET_THRUST;

	if(input.Tt == 0) {
		input.Tt = auto_pilot(state);
	}

	//update rocket dynamics

	state->rocket = physics_step_grav(state->rocket, input, state->moon);



	state->phi_earth = physics_get_phi_earth(state->rocket);
	state->r_earth = physics_get_r_earth(state->rocket);
	state->phi_moon = physics_get_phi_moon(state->rocket);
	state->r_moon = physics_get_r_moon(state->rocket);
	state->vel = physics_get_vel(state->rocket);

	if(state->r_moon < MOON_SOI) {
		state->phi = state->phi_moon;
		state->r = state->r_moon;
		state->moon = 1;
		if(state->r < MOON_RAD){
			state->game_fsm = CRASH;
			state->crash_type = MOON;
			game_init_crash(state);
			return;
		}
	} else {
		state->phi = state->phi_earth;
		state->r = state->r_earth;
		state->moon = 0;
		if(state->r < EARTH_RAD){
			state->game_fsm = CRASH;
			state->crash_type = EARTH;
			game_init_crash(state);
			return;
		}
	}
	if((state->rocket.x < WORLD_X_MIN)|(state->rocket.y < WORLD_Y_MIN)|(state->rocket.x >= WORLD_X_MAX)|(state->rocket.y >= WORLD_Y_MAX)){
		state->game_fsm = CRASH;
		state->crash_type = WALL;
		game_init_crash(state);
		return;
	}

	IVEC_t orb = {state->rocket.x, state->rocket.y};

	//update display
	graphics_sub_rocket_ingame(get_rocket_type(state->control_input));
	graphics_sub_put_slider(state->control_input.slider_pos);
	graphics_sub_set_ap(state->control_input.ap_mode);
	graphics_sub_put_speed(state->vel*1000);
	graphics_sub_put_alt(state->r*10000);
	graphics_sub_put_nav(state->rocket.a, 2);
	graphics_sub_put_hor(ROCKET_CORRECT_ANGLE(state->phi), 0.2, -50+state->r);

	graphics_main_draw_path(orb);
	graphics_main_update_sprite(orb, ROCKET_CORRECT_ANGLE(-state->rocket.a));

}


void game_init_crash(GAME_STATE_t * state) {
	switch (state->crash_type) {
	case EARTH:
		graphics_main_config_crash_earth();
		break;

	case MOON:
		graphics_main_config_crash_moon();
		break;

	case WALL:
		graphics_main_config_crash_wall();
		break;

	default:
		graphics_main_config_crash_earth();
		break;
	}

	graphics_sub_config_crash();
	sound_crash();
}

void game_crash(GAME_STATE_t * state){
	if(state->control_input.keysD & (KEY_START | KEY_TOUCH | KEY_B | KEY_A)) {
		graphics_main_clear_path();
		game_init(state);
		return;
	}
}

void game_pause(GAME_STATE_t * state) {

	if(state->control_input.keysD & (KEY_START | KEY_TOUCH| KEY_A)) {
		state->game_fsm = INGAME;
		graphics_sub_config_ingame();
		return;
	}
	if(state->control_input.keysD & KEY_B) {
		graphics_main_clear_path();
		game_init(state);
		return;
	}
}




