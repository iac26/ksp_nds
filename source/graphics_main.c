
#include "graphics_main.h"

#include <nds.h>
#include <math.h>
#include <stdio.h>


#include "splash.h"
#include "planets.h"
#include "crash_moon.h"
#include "crash_earth.h"
#include "rocket.h"

#define	SPRITE_WIDTH	32
#define	SPRITE_HEIGHT	32

static unsigned short * simulated_fb = 0;

//Pointer to the graphic buffer where to store the sprite
u16* gfx;


void configureSprites() {
	//Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	//Initialize sprite manager and the engine
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	//Allocate space for the graphic to show in the sprite
	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	//Copy data for the graphic (palette and bitmap)
	swiCopy(rocketPal, SPRITE_PALETTE, rocketPalLen/2);
	swiCopy(rocketTiles, gfx, rocketTilesLen/2);
}


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

void graphics_main_config_crash_wall() {

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

void graphics_main_config_intro() {

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

	//Configure sprites and fill graphics
	configureSprites();

}

#define FB_IX(x, y) ((x) + (y)*256)

void graphics_main_path(IVEC_t * pos, int len) {
	int i;
	for(i = 0; i < len; i++) {
		simulated_fb[FB_IX(pos[i].x, pos[i].y)/2] |= pos[i].x%2?254<<8:254;
		//int theta = acos(pos[i].x/sqrt((pos[i].x^2)+(pos[i].y^2)));
		oamSet(&oamMain, 	// oam handler
		    		0,				// Number of sprite
		    		(pos[i].x-16), (pos[i].y-16),			// Coordinates
		    		0,				// Priority
		    		0,				// Palette to use
		    		SpriteSize_32x32,			// Sprite size
		    		SpriteColorFormat_256Color,	// Color format
		    		gfx,			// Loaded graphic to display
		    		-1,				// Affine rotation to use (-1 none)
		    		false,			// Double size if rotating
		    		false,			// Hide this sprite
		    		false, false,	// Horizontal or vertical flip
		    		false			// Mosaic
		    		);
		    	swiWaitForVBlank();
		    	//Update the sprites
				oamUpdate(&oamMain);
	}
}
