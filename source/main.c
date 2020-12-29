/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include <math.h>

#include "graphics_main.h"
#include "graphics_sub.h"

int main(void) {
	
	graphics_main_init();

    graphics_sub_init();

    graphics_main_config();

    graphics_sub_config();

    graphics_sub_put_speed(1000);
    graphics_sub_put_alt(123);
    graphics_sub_put_nav(0, 2);
    graphics_sub_put_slider(6, 19);
    float angl = 0;
    int i =0;
    while(1) {
        swiWaitForVBlank();	
        i +=999;
        angl += 0.005;
        graphics_sub_put_speed(i);
        graphics_sub_put_nav(angl, sin(angl)+2);
        graphics_sub_put_hor(1.5, 0.2, -30);
    }
}
