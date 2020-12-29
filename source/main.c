/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "graphics_sub.h"

int main(void) {
	
    graphics_sub_init();

    graphics_sub_config();

    graphics_sub_put_speed(1000);
    graphics_sub_put_alt(123456);
    graphics_sub_put_nav(0);
    float angl = 0;
    int i =0;
    while(1) {
        swiWaitForVBlank();	
        i +=999;
        angl += 0.005;
        graphics_sub_put_speed(i);
        graphics_sub_put_nav(angl);
    }
}
