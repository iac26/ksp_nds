#ifndef INPUT_H
#define INPUT_H


typedef enum {
	AP_OFF = 0,
	AP_PROGRADE,
	AP_RETROGRADE,
	AP_RADIAL,
	AP_ANTIRADIAL,
	AP_KILL_ROT
}AP_MODE_t;


typedef struct {
	int l_hold;
	int r_hold;
	int u_hold;
	int d_hold;
	int slider_pos;
	int slider_val;
	AP_MODE_t ap_mode;

}CONTROLS_t;

void input_init();

void input_read(CONTROLS_t * control);




#endif
