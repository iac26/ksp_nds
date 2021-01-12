
#include "graphics_main.h"

#include <nds.h>
#include <math.h>
#include <stdio.h>


#include "splash.h"



static unsigned short * simulated_fb = 0;

void graphics_main_init() {
	// everything in vram C

	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG3_ACTIVE;

}


void graphics_main_config_splash() {

	//background 3
	BGCTRL[3] = BG_BMP_BASE(0) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	swiCopy(splashBitmap, BG_BMP_RAM(0), splashBitmapLen/2);
	swiCopy(splashPal, BG_PALETTE, splashPalLen/2);
}


//simulated framebuffer for tests
void graphics_main_config_ingame() {
	//background 3
	BGCTRL[3] = BG_BMP_BASE(0) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	unsigned short * pal = BG_PALETTE;

	simulated_fb = BG_BMP_RAM(0);

	pal[0] = RGB15(0, 0, 0);
	pal[1] = RGB15(31, 31, 31);
	pal[2] = RGB15(0, 15, 0);

	memset(simulated_fb, 0, 256*192);
}

#define FB_IX(x, y) ((x) + (y)*256)

void graphics_main_path(IVEC_t * pos, int len) {
	for(int i = 0; i < len; i++) {
		simulated_fb[FB_IX(pos[i].x, pos[i].y)/2] = pos[i].x%2?1<<8:1;
	}
}
