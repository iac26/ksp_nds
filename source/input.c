
#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "input.h"
#include "positions.h"



static void handle_touch_hold(CONTROLS_t * control);

static void handle_touch_down(CONTROLS_t * control);


void input_init(CONTROLS_t * control) {
	control->intro = 0;
}




void input_read(CONTROLS_t * control) {
	scanKeys();

	unsigned keysH  = keysHeld();
	unsigned keysD  = keysDown();
	unsigned keysDR = keysDownRepeat();

	if(keysH & KEY_TOUCH) {
		handle_touch_hold(control);
	}
	if(keysD & KEY_TOUCH) {
		handle_touch_down(control);
	}

	if(keysD & KEY_SELECT) {
		control->intro = !control->intro;
	}

	control->keysD  = keysD;
	control->keysH  = keysH;
	control->keysDR = keysDR;

}







static void handle_touch_hold(CONTROLS_t * control) {
	//handle touch sliders
	touchPosition touch;

	touchRead(&touch);

	if(SLIDER_INSIDE(touch.px, touch.py)) {
		control->slider_val = SLIDER_VAL(touch.px);
		control->slider_pos = SLIDER_POS(touch.px);
	}
}


static void handle_touch_down(CONTROLS_t * control) {
	//handle touch buttons
	touchPosition touch;

	touchRead(&touch);

	if(AP_KILL_ROT_INSIDE(touch.px, touch.py)) {
		control->ap_mode = control->ap_mode == AP_KILL_ROT?AP_OFF:AP_KILL_ROT;
	} else if (AP_PROG_INSIDE(touch.px, touch.py)) {
		control->ap_mode = control->ap_mode == AP_PROGRADE?AP_OFF:AP_PROGRADE;
	} else if (AP_RETR_INSIDE(touch.px, touch.py)) {
		control->ap_mode = control->ap_mode == AP_RETROGRADE?AP_OFF:AP_RETROGRADE;
	} else if (AP_RAD_INSIDE(touch.px, touch.py)) {
		control->ap_mode = control->ap_mode == AP_RADIAL?AP_OFF:AP_RADIAL;
	} else if (AP_ARAD_INSIDE(touch.px, touch.py)) {
		control->ap_mode = control->ap_mode == AP_ANTIRADIAL?AP_OFF:AP_ANTIRADIAL;
	}


}







