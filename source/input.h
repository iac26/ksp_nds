#ifndef INPUT_H
#define INPUT_H

#include <nds.h>


typedef enum {
	AP_KILL_ROT = 0,
	AP_PROGRADE,
	AP_RETROGRADE,
	AP_RADIAL,
	AP_ANTIRADIAL,
	AP_OFF
}AP_MODE_t;


typedef struct {
	int slider_pos;
	int slider_val;
	AP_MODE_t ap_mode;
	uint8_t intro;
	uint8_t abort;
	unsigned keysD;
	unsigned keysH;
	unsigned keysDR;

}CONTROLS_t;

void input_init();

void input_read(CONTROLS_t * control, uint8_t touch_active);



#endif
