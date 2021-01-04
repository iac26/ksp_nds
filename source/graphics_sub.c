

#include "graphics_sub.h"

#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "numbers.h"
#include "backplate.h"
#include "fusee.h"
#include "horizon.h"
#include "splash2.h"

#include "positions.h"


static unsigned short * overlay_map = 0;

void graphics_sub_init() {
	// everything in vram C

	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;

}

//VRAM BANK SEL https://mtheall.com/banks.html#C=SBG

//LAYOUT https://mtheall.com/vram.html#SUB=1&T0=1&NT0=320&MB0=11&TB0=0&S0=0&T1=1&NT1=64&MB1=14&TB1=2&S1=0&T2=5&MB2=3&S2=0&T3=5&MB3=4&S3=0
/*
 * BG0 : numbers 	320 tiles 32x32 map		64 colors  map(11) tile(0)  palette offset: 0
 * BG1 : backplate 	62 tiles 32x32 map		64 colors  map(14) tile(2)  palette offset: 64
 * BG2 : fusee		16kb bitmap				64 colors  bmp(3)			palette offset: 128
 * BG3 : horizon	16kb bitmap				64 colors  bmp(4)			palette offset: 192
 */

#define BG0_TILE	0
#define BG0_MAP		11

#define BG1_TILE	2
#define BG1_MAP 	14

#define BG2_BMP		3

#define BG3_BMP 	4

#define BG0_PALETTE_OFS		0
#define BG1_PALETTE_OFS		64
#define BG2_PALETTE_OFS		128
#define BG3_PALETTE_OFS		192


#define BG3_BMP_SPLASH	4



#define EMPTY_TILE	36

void graphics_sub_config_splash() {

	//background 3
	BGCTRL_SUB[3] = BG_BMP_BASE(BG3_BMP_SPLASH) | (u16) BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG3PA_SUB = 256;
	REG_BG3PC_SUB = 0;
	REG_BG3PB_SUB = 0;
	REG_BG3PD_SUB = 256;

	dmaCopy(splash2Bitmap, BG_BMP_RAM_SUB(BG3_BMP_SPLASH), splash2BitmapLen);
	dmaCopy(splash2Pal, BG_PALETTE_SUB, splash2PalLen);

}

void graphics_sub_config_ingame() {

	//background 3
	BGCTRL_SUB[3] = BG_BMP_BASE(BG3_BMP) | (u16) BgSize_B8_128x128;

	//Affine Marix Transformation
	REG_BG3PA_SUB = 256;
	REG_BG3PC_SUB = 0;
	REG_BG3PB_SUB = 0;
	REG_BG3PD_SUB = 256;

	dmaCopy(horizonBitmap, BG_BMP_RAM_SUB(BG3_BMP), horizonBitmapLen);
	dmaCopy(horizonPal, BG_PALETTE_SUB+BG3_PALETTE_OFS, horizonPalLen);

	//background 2
	BGCTRL_SUB[2] = BG_BMP_BASE(BG2_BMP) | (u16) BgSize_B8_128x128;

	//Affine Marix Transformation
	REG_BG2PA_SUB = 256;
	REG_BG2PC_SUB = 0;
	REG_BG2PB_SUB = 0;
	REG_BG2PD_SUB = 256;

	dmaCopy(fuseeBitmap, BG_BMP_RAM_SUB(BG2_BMP), fuseeBitmapLen);
	dmaCopy(fuseePal, BG_PALETTE_SUB+BG2_PALETTE_OFS, fuseePalLen);


	//background 1
	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(BG1_MAP) | BG_TILE_BASE(BG1_TILE) ;

	dmaCopy(backplateTiles, BG_TILE_RAM_SUB(BG1_TILE), backplateTilesLen);
	dmaCopy(backplateMap, BG_MAP_RAM_SUB(BG1_MAP), backplateMapLen);


	dmaCopy(backplatePal, BG_PALETTE_SUB+BG1_PALETTE_OFS, backplatePalLen);

	//background 0
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(BG0_MAP) | BG_TILE_BASE(BG0_TILE);

	dmaCopy(numbersTiles, BG_TILE_RAM_SUB(BG0_TILE), numbersTilesLen);
	dmaCopy(numbersPal, BG_PALETTE_SUB+BG0_PALETTE_OFS, numbersPalLen);


	overlay_map = BG_MAP_RAM_SUB(BG0_MAP);

	//create empty tile

	memset(overlay_map, EMPTY_TILE, 2*backplateMapLen); // fill with empty tiles

}


static void number_to_digits(unsigned short digits[6], unsigned int number) {
	if (number > 1e8) {
		digits[0] = 11;
		number = number / 1e6;
	} else if (number > 1e5) {
		digits[0] = 10;
		number = number / 1e3;
	} else {
		digits[0] = 12;
	}

	for (int i = 1; i < 6; i++ ) {
		digits[i] = number % 10;
		number = number / 10;
	}
}


#define SPEED_POS 25

void graphics_sub_put_speed(unsigned int number) {


	unsigned short digit[6] = {0};

	number_to_digits(digit, number);

	graphics_sub_put_digit(digit[0], SPEED_POS, 16);
	graphics_sub_put_digit(digit[1], SPEED_POS, 14);
	graphics_sub_put_digit(digit[2], SPEED_POS, 12);
	graphics_sub_put_digit(digit[3], SPEED_POS, 10);
	graphics_sub_put_digit(digit[4], SPEED_POS, 8);
	graphics_sub_put_digit(digit[5], SPEED_POS, 6);
}

#define ALT_POS 19

void graphics_sub_put_alt(unsigned int number) {


	unsigned short digit[6] = {0};

	number_to_digits(digit, number);

	graphics_sub_put_digit(digit[0], ALT_POS, 16);
	graphics_sub_put_digit(digit[1], ALT_POS, 14);
	graphics_sub_put_digit(digit[2], ALT_POS, 12);
	graphics_sub_put_digit(digit[3], ALT_POS, 10);
	graphics_sub_put_digit(digit[4], ALT_POS, 8);
	graphics_sub_put_digit(digit[5], ALT_POS, 6);
}


#define MAP_32x32_POS(x, y) (x+(y)*32)

#define DIGIT_ROW_SIZE 80
#define DIGIT_SKIP_SIZE 3

void graphics_sub_put_digit(unsigned short digit, unsigned short x, unsigned short y) {

	overlay_map[MAP_32x32_POS(x+0, y)] = digit*DIGIT_SKIP_SIZE+0;
	overlay_map[MAP_32x32_POS(x+1, y)] = digit*DIGIT_SKIP_SIZE+1;
	overlay_map[MAP_32x32_POS(x+2, y)] = digit*DIGIT_SKIP_SIZE+2;
	overlay_map[MAP_32x32_POS(x+0, y+1)] = digit*DIGIT_SKIP_SIZE+0+DIGIT_ROW_SIZE;
	overlay_map[MAP_32x32_POS(x+1, y+1)] = digit*DIGIT_SKIP_SIZE+1+DIGIT_ROW_SIZE;
	overlay_map[MAP_32x32_POS(x+2, y+1)] = digit*DIGIT_SKIP_SIZE+2+DIGIT_ROW_SIZE;


}

#define SLIDER_START 39

void graphics_sub_put_slider(unsigned short x) {

	static unsigned short prev_x = 0;
	unsigned short y = SLIDER_POS_Y;
	//erase prev position
	overlay_map[MAP_32x32_POS(prev_x+0, y+0)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+1, y+0)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+2, y+0)] = EMPTY_TILE;

	overlay_map[MAP_32x32_POS(prev_x+0, y+1)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+1, y+1)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+2, y+1)] = EMPTY_TILE;

	overlay_map[MAP_32x32_POS(prev_x+0, y+2)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+1, y+2)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+2, y+2)] = EMPTY_TILE;

	//set new tiles

	overlay_map[MAP_32x32_POS(x+0, y+0)] = SLIDER_START+0;
	overlay_map[MAP_32x32_POS(x+1, y+0)] = SLIDER_START+1;
	overlay_map[MAP_32x32_POS(x+2, y+0)] = SLIDER_START+2;

	overlay_map[MAP_32x32_POS(x+0, y+1)] = SLIDER_START+DIGIT_ROW_SIZE+0;
	overlay_map[MAP_32x32_POS(x+1, y+1)] = SLIDER_START+DIGIT_ROW_SIZE+1;
	overlay_map[MAP_32x32_POS(x+2, y+1)] = SLIDER_START+DIGIT_ROW_SIZE+2;

	overlay_map[MAP_32x32_POS(x+0, y+2)] = SLIDER_START+2*DIGIT_ROW_SIZE+0;
	overlay_map[MAP_32x32_POS(x+1, y+2)] = SLIDER_START+2*DIGIT_ROW_SIZE+1;
	overlay_map[MAP_32x32_POS(x+2, y+2)] = SLIDER_START+2*DIGIT_ROW_SIZE+2;

	prev_x = x;
}


#define AP_START		42
#define AP_SKIP			3
#define AP_POS_SKIP		4
#define AP_POS_START	6
#define AP_POS_Y		2

void graphics_sub_set_ap(AP_MODE_t mode) {

	static unsigned short prev_x = 0;
	unsigned short y = AP_POS_Y;
	unsigned short x = AP_POS_START+AP_POS_SKIP*mode;


	//erase prev tiles
	overlay_map[MAP_32x32_POS(prev_x+0, y+0)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+1, y+0)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+2, y+0)] = EMPTY_TILE;

	overlay_map[MAP_32x32_POS(prev_x+0, y+1)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+1, y+1)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+2, y+1)] = EMPTY_TILE;

	overlay_map[MAP_32x32_POS(prev_x+0, y+2)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+1, y+2)] = EMPTY_TILE;
	overlay_map[MAP_32x32_POS(prev_x+2, y+2)] = EMPTY_TILE;

	//set new tiles

	if(mode == AP_OFF) return;

	overlay_map[MAP_32x32_POS(x+0, y+0)] = AP_SKIP*mode + AP_START+0;
	overlay_map[MAP_32x32_POS(x+1, y+0)] = AP_SKIP*mode + AP_START+1;
	overlay_map[MAP_32x32_POS(x+2, y+0)] = AP_SKIP*mode + AP_START+2;

	overlay_map[MAP_32x32_POS(x+0, y+1)] = AP_SKIP*mode + AP_START+DIGIT_ROW_SIZE+0;
	overlay_map[MAP_32x32_POS(x+1, y+1)] = AP_SKIP*mode + AP_START+DIGIT_ROW_SIZE+1;
	overlay_map[MAP_32x32_POS(x+2, y+1)] = AP_SKIP*mode + AP_START+DIGIT_ROW_SIZE+2;

	overlay_map[MAP_32x32_POS(x+0, y+2)] = AP_SKIP*mode + AP_START+2*DIGIT_ROW_SIZE+0;
	overlay_map[MAP_32x32_POS(x+1, y+2)] = AP_SKIP*mode + AP_START+2*DIGIT_ROW_SIZE+1;
	overlay_map[MAP_32x32_POS(x+2, y+2)] = AP_SKIP*mode + AP_START+2*DIGIT_ROW_SIZE+2;


	prev_x = x;

}


#define WIDTH		  (128)
#define ROT_CENTER_X  (90)
#define ROT_CENTER_Y  (96)

#define MARGIN_X(scale) (ROT_CENTER_X*(scale)-WIDTH/2)
#define MARGIN_Y(scale) (ROT_CENTER_Y*(scale)-WIDTH/2)

void graphics_sub_put_nav(float angle, float scale) {

	int x = ROT_CENTER_X*scale;
	int y = ROT_CENTER_Y*scale;
	float r = sqrt(x*x + y*y);
	float alpha = atan((float)x/(float)y)+angle;


	REG_BG2PA_SUB = cos(angle)*scale*256;
	REG_BG2PB_SUB = sin(angle)*scale*256;
	REG_BG2PC_SUB = -sin(angle)*scale*256;
	REG_BG2PD_SUB = cos(angle)*scale*256;

	REG_BG2X_SUB = (x - r*sin(alpha) - MARGIN_X(scale))*256;
	REG_BG2Y_SUB = (y - r*cos(alpha) - MARGIN_Y(scale))*256;
}



void graphics_sub_put_hor(float angle, float scale, int shift) {

	int x = ROT_CENTER_X*scale;
	int y = ROT_CENTER_Y*scale;
	float r = sqrt(x*x + y*y);
	float alpha = atan((float)x/(float)y)+angle;


	REG_BG3PA_SUB = cos(angle)*scale*256;
	REG_BG3PB_SUB = sin(angle)*scale*256;
	REG_BG3PC_SUB = -sin(angle)*scale*256;
	REG_BG3PD_SUB = cos(angle)*scale*256;

	REG_BG3X_SUB = (x - r*sin(alpha) - MARGIN_X(scale))*256;
	REG_BG3Y_SUB = (y - r*cos(alpha) - MARGIN_Y(scale)-shift)*256;
}






