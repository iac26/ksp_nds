
#include "graphics_main.h"

#include <nds.h>
#include <math.h>
#include <stdio.h>


#include "splash.h"
#include "planets.h"
#include "crash_moon.h"
#include "crash_earth.h"

static unsigned short * simulated_fb = 0;

void graphics_main_init() {
	// everything in vram C

	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

}


void graphics_main_config_splash() {
	//only bg3 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG3_ACTIVE;

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

void graphics_main_config_crash_moon() {
	//only bg2 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//background 3
	BGCTRL[2] = BG_BMP_BASE(0) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	swiCopy(crash_moonBitmap, BG_BMP_RAM(0), crash_moonBitmapLen/2);
	swiCopy(crash_moonPal, BG_PALETTE, crash_moonPalLen/2);
}

void graphics_main_config_crash_earth() {

	//only bg2 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//background 3
	BGCTRL[2] = BG_BMP_BASE(0) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	swiCopy(crash_earthBitmap, BG_BMP_RAM(0), crash_earthBitmapLen/2);
	swiCopy(crash_earthPal, BG_PALETTE, crash_earthPalLen/2);


}

void graphics_main_config_crash() {

	//only bg2 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//background 3
	BGCTRL[2] = BG_BMP_BASE(0) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	swiCopy(crash_earthBitmap, BG_BMP_RAM(0), crash_earthBitmapLen/2);
	swiCopy(crash_earthPal, BG_PALETTE, crash_earthPalLen/2);


}



//simulated framebuffer for tests
void graphics_main_config_ingame() {
	//BG2 and BG3 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG2_ACTIVE;
	//background 2
	BGCTRL[2] = BG_BMP_BASE(0) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	unsigned short * pal = BG_PALETTE;

	simulated_fb = BG_BMP_RAM(0);

	pal[0] = RGB15(0, 0, 0);
	pal[255] = RGB15(31, 31, 31);
	pal[254] = RGB15(0, 15, 0);

	memset(simulated_fb, 0, 256*192);


	BGCTRL[3] = BG_BMP_BASE(3) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	swiCopy(planetsBitmap, BG_BMP_RAM(3), planetsBitmapLen/2);
	swiCopy(planetsPal, BG_PALETTE, planetsPalLen/2);

}

#define FB_IX(x, y) ((x) + (y)*256)

void graphics_main_path(IVEC_t * pos, int len) {
	int i;
	for(i = 0; i < len; i++) {
		simulated_fb[FB_IX(pos[i].x, pos[i].y)/2] |= pos[i].x%2?254<<8:254;
	}
}
