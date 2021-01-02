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
