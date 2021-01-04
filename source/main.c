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

	input_init();


	graphics_main_init();
	graphics_sub_init();


	//do the right configuration for the main and sub screens


	while(1) {
		swiWaitForVBlank();
		input_read(&(game_state.control_input));
		switch(game_state.game_fsm) {
		case SPLASH:
			game_splash(&game_state);
			break;
		case INGAME:
			game_ingame(&game_state);
			break;
		case END:
			game_end(&game_state);
			break;
		default:
			game_end(&game_state);
			break;
		}
	}
}



/*
 * TEST MAIN TO TRY THE GRAPHICS
int main(void) {

	graphics_main_init();

    graphics_sub_init();

    graphics_main_config();

    graphics_sub_config();

    graphics_sub_put_speed(1000);
    graphics_sub_put_alt(123);
    graphics_sub_put_nav(0, 2);
    graphics_sub_put_slider(3);
    float angl = 3.14/2;
    int i =0;
    graphics_sub_set_ap(AP_OFF);
    while(1) {
        swiWaitForVBlank();
        CONTROLS_t control;
        input_read(&control);

        if(control.r_hold) {
			i +=999;
		}
        if(control.l_hold) {
			i -=999;
		}
        if(control.u_hold) {
        	angl -= 0.005;
		}
        if(control.d_hold) {
			angl += 0.005;
		}
        graphics_sub_put_slider(control.slider_pos);
        graphics_sub_set_ap(control.ap_mode);
        graphics_sub_put_speed(i);
        graphics_sub_put_nav(angl, 2);
        graphics_sub_put_hor(1.5, 0.2, -30);
    }
}

*/
