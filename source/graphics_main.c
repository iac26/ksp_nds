
#include "graphics_main.h"

#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "splash.h"

void graphics_main_init() {
	// everything in vram C

	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG3_ACTIVE;

}


void graphics_main_config() {

	//background 3
	BGCTRL[3] = BG_BMP_BASE(0) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	dmaCopy(splashBitmap, BG_BMP_RAM(0), splashBitmapLen);
	dmaCopy(splashPal, BG_PALETTE, splashPalLen);
}
