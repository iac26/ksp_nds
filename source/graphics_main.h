#ifndef GRAPHICS_MAIN_H
#define GRAPHICS_MAIN_H

#include "physics.h"

void configureSprites();
void graphics_main_init();

void graphics_main_config_ingame();
void graphics_main_config_splash();
void graphics_main_config_crash_moon();
void graphics_main_config_crash_earth();
void graphics_main_config_crash_wall();
void graphics_main_config_intro();



//simulated FB for tests IACOPO



void graphics_main_path(IVEC_t * pos, int len);



#endif
