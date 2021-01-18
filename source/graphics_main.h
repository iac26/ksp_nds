#ifndef GRAPHICS_MAIN_H
#define GRAPHICS_MAIN_H

#include "physics.h"

void graphics_main_config_sprite();
void graphics_main_init();

void graphics_main_config_ingame();
void graphics_main_config_splash();
void graphics_main_config_crash_moon();
void graphics_main_config_crash_earth();
void graphics_main_config_crash_wall();
void graphics_main_config_intro();



void graphics_main_draw_path(IVEC_t pos);

void graphics_main_clear_path();

void graphics_main_update_sprite(IVEC_t pos, float angle);


#endif
