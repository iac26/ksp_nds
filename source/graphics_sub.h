#ifndef GRAPHICS_SUB_H
#define GRAPHICS_SUB_H

#include "input.h"


/*
 * REQUIRES MODIFIED GRIT
 *
 */

void graphics_sub_init();

void graphics_sub_config_ingame();

void graphics_sub_rocket_ingame(int rocket);

void graphics_sub_config_splash();

void graphics_sub_put_digit(unsigned short digit, unsigned short x, unsigned short y);

void graphics_sub_put_slider(unsigned short x);

void graphics_sub_set_ap(AP_MODE_t mode);

void graphics_sub_put_speed(unsigned int number);

void graphics_sub_put_alt(unsigned int number);

void graphics_sub_put_nav(float angle, float scale);

void graphics_sub_put_hor(float angle, float scale, int shift);


#endif
