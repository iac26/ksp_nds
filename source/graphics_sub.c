

#include "graphics_sub.h"

#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "shared.h"
#include "numbers.h"
#include "backplate.h"
#include "fusee.h"


static unsigned short * overlay_map = 0;

void graphics_sub_init() {
	// everything in vram C

	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE;

}


void graphics_sub_config() {

	//background 2
	BGCTRL_SUB[2] = BG_BMP_BASE(5) | (u16) BgSize_B8_128x128;

	//Affine Marix Transformation
	REG_BG2PA_SUB = 256;
	REG_BG2PC_SUB = 0;
	REG_BG2PB_SUB = 0;
	REG_BG2PD_SUB = 256;

	swiCopy(fuseeBitmap, BG_BMP_RAM_SUB(5), fuseeBitmapLen);



	//background 1
	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) ;

	swiCopy(backplateTiles, BG_TILE_RAM_SUB(1), backplateTilesLen);
	swiCopy(backplateMap, BG_MAP_RAM_SUB(0), backplateMapLen);

	swiCopy(fuseePal, BG_PALETTE_SUB+84, fuseePalLen);
	swiCopy(backplatePal, BG_PALETTE_SUB, backplatePalLen);

	//background 0
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(2) | BG_TILE_BASE(3);

	swiCopy(numbersTiles, BG_TILE_RAM_SUB(3), numbersTilesLen);
	swiCopy(numbersPal, BG_PALETTE_SUB+64, numbersPalLen);


	overlay_map = BG_MAP_RAM_SUB(2);

	memset(overlay_map, 73, 2*backplateMapLen); // fill with empty tiles



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


#define SPEED_POS 4

void graphics_sub_put_speed(unsigned int number) {


	unsigned short digit[6] = {0};

	number_to_digits(digit, number);

	graphics_sub_put_digit(digit[0], SPEED_POS, 6);
	graphics_sub_put_digit(digit[1], SPEED_POS, 8);
	graphics_sub_put_digit(digit[2], SPEED_POS, 10);
	graphics_sub_put_digit(digit[3], SPEED_POS, 12);
	graphics_sub_put_digit(digit[4], SPEED_POS, 14);
	graphics_sub_put_digit(digit[5], SPEED_POS, 16);
}

#define ALT_POS 10

void graphics_sub_put_alt(unsigned int number) {


	unsigned short digit[6] = {0};

	number_to_digits(digit, number);

	graphics_sub_put_digit(digit[0], ALT_POS, 6);
	graphics_sub_put_digit(digit[1], ALT_POS, 8);
	graphics_sub_put_digit(digit[2], ALT_POS, 10);
	graphics_sub_put_digit(digit[3], ALT_POS, 12);
	graphics_sub_put_digit(digit[4], ALT_POS, 14);
	graphics_sub_put_digit(digit[5], ALT_POS, 16);
}


#define MAP_32x32_POS(x, y) (x+(y)*32)

#define DIGIT_ROW_SIZE 39
#define DIGIT_SKIP_SIZE 3

void graphics_sub_put_digit(unsigned short digit, unsigned short x, unsigned short y) {

	overlay_map[MAP_32x32_POS(x+0, y)] = digit*DIGIT_SKIP_SIZE+0;
	overlay_map[MAP_32x32_POS(x+1, y)] = digit*DIGIT_SKIP_SIZE+1;
	overlay_map[MAP_32x32_POS(x+2, y)] = digit*DIGIT_SKIP_SIZE+2;
	overlay_map[MAP_32x32_POS(x+0, y+1)] = digit*DIGIT_SKIP_SIZE+0+DIGIT_ROW_SIZE;
	overlay_map[MAP_32x32_POS(x+1, y+1)] = digit*DIGIT_SKIP_SIZE+1+DIGIT_ROW_SIZE;
	overlay_map[MAP_32x32_POS(x+2, y+1)] = digit*DIGIT_SKIP_SIZE+2+DIGIT_ROW_SIZE;


}

void graphics_sub_put_nav(float angle) {
	float scale = 2;
	int x = 166*scale;
	int y = 96*scale;
	float r = sqrt(x*x + y*y);
	float alpha = atan((float)x/(float)y)+angle;


	REG_BG2PA_SUB = cos(angle)*scale*256;
	REG_BG2PB_SUB = sin(angle)*scale*256;
	REG_BG2PC_SUB = -sin(angle)*scale*256;
	REG_BG2PD_SUB = cos(angle)*scale*256;

	REG_BG2X_SUB = (x - 135*scale - r*sin(alpha))*256;
	REG_BG2Y_SUB = (y - 64*scale - r*cos(alpha))*256;
}






