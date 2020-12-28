

#include "graphics_sub.h"

#include <nds.h>
#include <stdio.h>

#include "numbers.h"
#include "backplate.h"

static unsigned short * overlay_map = 0;

void graphics_sub_init() {
	// everything in vram C

	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE;

}


void graphics_sub_config() {
	//background 1
	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) ;

	swiCopy(backplateTiles, BG_TILE_RAM_SUB(1), backplateTilesLen);
	swiCopy(backplateMap, BG_MAP_RAM_SUB(0), backplateMapLen);
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


void graphics_sub_put_speed(unsigned int number) {


	unsigned short digit[6] = {0};

	number_to_digits(digit, number);

	graphics_sub_put_digit(digit[0], 4, 6);
	graphics_sub_put_digit(digit[1], 4, 8);
	graphics_sub_put_digit(digit[2], 4, 10);
	graphics_sub_put_digit(digit[3], 4, 12);
	graphics_sub_put_digit(digit[4], 4, 14);
	graphics_sub_put_digit(digit[5], 4, 16);
}

void graphics_sub_put_alt(unsigned int number) {


	unsigned short digit[6] = {0};

	number_to_digits(digit, number);

	graphics_sub_put_digit(digit[0], 10, 6);
	graphics_sub_put_digit(digit[1], 10, 8);
	graphics_sub_put_digit(digit[2], 10, 10);
	graphics_sub_put_digit(digit[3], 10, 12);
	graphics_sub_put_digit(digit[4], 10, 14);
	graphics_sub_put_digit(digit[5], 10, 16);
}


#define MAP_32x32_POS(x, y) (x+(y)*32)

void graphics_sub_put_digit(unsigned short digit, unsigned short x, unsigned short y) {

	overlay_map[MAP_32x32_POS(x+0, y)] = digit*3+0;
	overlay_map[MAP_32x32_POS(x+1, y)] = digit*3+1;
	overlay_map[MAP_32x32_POS(x+2, y)] = digit*3+2;
	overlay_map[MAP_32x32_POS(x+0, y+1)] = digit*3+0+39;
	overlay_map[MAP_32x32_POS(x+1, y+1)] = digit*3+1+39;
	overlay_map[MAP_32x32_POS(x+2, y+1)] = digit*3+2+39;


}






