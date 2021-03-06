
#include "graphics_main.h"

#include <nds.h>
#include <math.h>
#include <stdio.h>


#include "splash.h"
#include "planets.h"
#include "crash_moon.h"
#include "crash_earth.h"
#include "crash_wall.h"
#include "rocket.h"
#include "backplate.h"
#include "intro.h"

//#define	SPRITE_WIDTH	8
//#define	SPRITE_HEIGHT	8

static uint16_t * simulated_fb = 0;

//Pointer to the graphic buffer where to store the sprite
static uint16_t * sprite_gfx;

#define BG_PATH		(0)
#define BG_IMG		(3)


void graphics_main_config_sprite() {

	//Initialize sprite manager and the engine
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	//Allocate space for the graphic to show in the sprite
	sprite_gfx = oamAllocateGfx(&oamMain, SpriteSize_8x8, SpriteColorFormat_256Color);

	//Copy data for the graphic (palette and bitmap)
	swiCopy(rocketPal, SPRITE_PALETTE, rocketPalLen/2);
	swiCopy(rocketTiles, sprite_gfx, rocketTilesLen/2);
}


void graphics_main_init() {

	// memory for backgrounds
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	// memory for sprites
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

}


void graphics_main_config_splash() {
	//only bg2 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//background 2
	BGCTRL[2] = BG_BMP_BASE(BG_IMG) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	swiCopy(splashBitmap, BG_BMP_RAM(BG_IMG), splashBitmapLen/2);
	swiCopy(splashPal, BG_PALETTE, splashPalLen/2);
}

void graphics_main_config_crash_moon() {
	//only bg2 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//background 2
	BGCTRL[2] = BG_BMP_BASE(BG_IMG) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	swiCopy(crash_moonBitmap, BG_BMP_RAM(BG_IMG), crash_moonBitmapLen/2);
	swiCopy(crash_moonPal, BG_PALETTE, crash_moonPalLen/2);
}

void graphics_main_config_crash_earth() {

	//only bg2 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//background 2
	BGCTRL[2] = BG_BMP_BASE(BG_IMG) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	swiCopy(crash_earthBitmap, BG_BMP_RAM(BG_IMG), crash_earthBitmapLen/2);
	swiCopy(crash_earthPal, BG_PALETTE, crash_earthPalLen/2);


}

void graphics_main_config_crash_wall() {

	//only bg2 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//background 2
	BGCTRL[2] = BG_BMP_BASE(BG_IMG) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	swiCopy(crash_wallBitmap, BG_BMP_RAM(BG_IMG), crash_wallBitmapLen/2);
	swiCopy(crash_wallPal, BG_PALETTE, crash_wallPalLen/2);

}


void graphics_main_config_intro() {
	//only bg3 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG3_ACTIVE;

	//background 3
	BGCTRL[3] = BG_BMP_BASE(BG_IMG) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	swiCopy(introBitmap, BG_BMP_RAM(BG_IMG), introBitmapLen/2);
	swiCopy(introPal, BG_PALETTE, introPalLen/2);
}




//simulated framebuffer for tests
void graphics_main_config_ingame() {
	//BG2 and BG3 active
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG2_ACTIVE;
	//background 2
	BGCTRL[2] = BG_BMP_BASE(BG_PATH) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;

	unsigned short * pal = BG_PALETTE;

	simulated_fb = BG_BMP_RAM(BG_PATH);

	pal[0] = RGB15(0, 0, 0);
	pal[255] = RGB15(31, 31, 31);
	pal[254] = RGB15(0, 15, 0);


	BGCTRL[3] = BG_BMP_BASE(BG_IMG) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG3PA = 256;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = 256;

	swiCopy(planetsBitmap, BG_BMP_RAM(BG_IMG), planetsBitmapLen/2);
	swiCopy(planetsPal, BG_PALETTE, planetsPalLen/2);

	//Configure sprites and fill graphics
	graphics_main_config_sprite();

}

void graphics_main_clear_path() {
	memset(simulated_fb, 0, 256*192);
}


#define FB_IX(x, y) ((x) + (y)*256)

void graphics_main_draw_path(IVEC_t pos) {
	simulated_fb[FB_IX(pos.x, pos.y)/2] |= pos.x%2?254<<8:254;


}

#define RAD2DEG(a) (a*180/M_PI)

void graphics_main_update_sprite(IVEC_t pos, float angle) {
	oamSet(&oamMain, 	// oam handler
			0,				// Number of sprite
			(pos.x-4), (pos.y-4),			// Coordinates
			0,				// Priority
			0,				// Palette to use
			SpriteSize_8x8,			// Sprite size
			SpriteColorFormat_256Color,	// Color format
			sprite_gfx,			// Loaded graphic to display
			0,				// Affine rotation to use (-1 none)
			false,			// Double size if rotating
			false,			// Hide this sprite
			false, false,	// Horizontal or vertical flip
			false			// Mosaic
			);

	oamRotateScale(&oamMain, 0, degreesToAngle(RAD2DEG(angle)), 256, 256);

	swiWaitForVBlank();
	//Update the sprites
	oamUpdate(&oamMain);
}




