
#include <nds.h>
#include <math.h>
#include <stdio.h>

#include "input.h"
#include "positions.h"





static void handle_touch_hold(CONTROLS_t * control);

static void handle_touch_down(CONTROLS_t * control);


void input_init() {

}





void input_read(CONTROLS_t * control) {
	scanKeys();

	unsigned keysH = keysHeld();
	unsigned keysD = keysDown();

	if(keysH & KEY_TOUCH) {
		handle_touch_hold(control);
	}
	if(keysD & KEY_TOUCH) {
		handle_touch_down(control);
	}

	control->l_hold = keysH & KEY_LEFT;
	control->r_hold = keysH & KEY_RIGHT;
	control->u_hold = keysH & KEY_UP;
	control->d_hold = keysH & KEY_DOWN;






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

	if(AP_OFF_INSIDE(touch.px, touch.py)) {
		control->ap_mode = AP_OFF;
	} else if (AP_PROG_INSIDE(touch.px, touch.py)) {
		control->ap_mode = AP_PROGRADE;
	} else if (AP_RETR_INSIDE(touch.px, touch.py)) {
		control->ap_mode = AP_RETROGRADE;
	} else if (AP_RAD_INSIDE(touch.px, touch.py)) {
		control->ap_mode = AP_RADIAL;
	} else if (AP_ARAD_INSIDE(touch.px, touch.py)) {
		control->ap_mode = AP_ANTIRADIAL;
	}


}







