#ifndef GRAPHICS_SUB_H
#define GRAPHICS_SUB_H

void graphics_sub_init();

void graphics_sub_config();

void graphics_sub_put_digit(unsigned short digit, unsigned short x, unsigned short y);

void graphics_sub_put_speed(unsigned int number);

void graphics_sub_put_alt(unsigned int number);

void graphics_sub_put_nav(float angle);


#endif
