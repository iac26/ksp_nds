#ifndef POSITIONS_H
#define POSITIONS_H



//inside check macro

#define INSIDE_AXIS(min, max, val)  ((min) <= (val) && (val) < (max))

#define INSIDE(x1, x2, y1, y2, x, y) (INSIDE_AXIS(x1, x2, x) && INSIDE_AXIS(y1, y2, y))

//slider positions
#define SLIDER_X	(32)
#define SLIDER_W	(192)
#define SLIDER_Y	(160)
#define SLIDER_H	(8)
#define SLIDER_M	(4)

#define SLIDER_X1	(SLIDER_X-SLIDER_M)
#define SLIDER_X2	(SLIDER_X+SLIDER_W+SLIDER_M)
#define SLIDER_Y1	(SLIDER_Y-SLIDER_M)
#define SLIDER_Y2	(SLIDER_Y+SLIDER_H+SLIDER_M)

#define SLIDER_INSIDE(x, y)  INSIDE(SLIDER_X1, SLIDER_X2, SLIDER_Y1, SLIDER_Y2, x, y)

#define SLIDER_POS_X	(3)
#define SLIDER_POS_W	(23)

#define SLIDER_POS_Y	(19)

#define SLIDER_POS(x)	 (((x) - SLIDER_X)*SLIDER_POS_W/SLIDER_W+SLIDER_POS_X)

#define SLIDER_VAL(x)	 (((x) - SLIDER_X)*256/SLIDER_W)




//autopilot mode




//AP btns

#define AP_BTN_W	(24)
#define AP_BTN_H	(24)

//off

#define AP_OFF_X	(48)
#define AP_OFF_Y	(16)


#define AP_OFF_X1	(AP_OFF_X)
#define AP_OFF_X2	(AP_OFF_X+AP_BTN_W)
#define AP_OFF_Y1	(AP_OFF_Y)
#define AP_OFF_Y2	(AP_OFF_Y+AP_BTN_H)

#define AP_OFF_INSIDE(x, y)  INSIDE(AP_OFF_X1, AP_OFF_X2, AP_OFF_Y1, AP_OFF_Y2, x, y)

//prograde

#define AP_PROG_X	(80)
#define AP_PROG_Y	(16)

#define AP_PROG_X1	(AP_PROG_X)
#define AP_PROG_X2	(AP_PROG_X+AP_BTN_W)
#define AP_PROG_Y1	(AP_PROG_Y)
#define AP_PROG_Y2	(AP_PROG_Y+AP_BTN_H)

#define AP_PROG_INSIDE(x, y)  INSIDE(AP_PROG_X1, AP_PROG_X2, AP_PROG_Y1, AP_PROG_Y2, x, y)

//retrograde

#define AP_RETR_X	(112)
#define AP_RETR_Y	(16)


#define AP_RETR_X1	(AP_RETR_X)
#define AP_RETR_X2	(AP_RETR_X+AP_BTN_W)
#define AP_RETR_Y1	(AP_RETR_Y)
#define AP_RETR_Y2	(AP_RETR_Y+AP_BTN_H)

#define AP_RETR_INSIDE(x, y)  INSIDE(AP_RETR_X1, AP_RETR_X2, AP_RETR_Y1, AP_RETR_Y2, x, y)

//radial

#define AP_RAD_X	(144)
#define AP_RAD_Y	(16)

#define AP_RAD_X1	(AP_RAD_X)
#define AP_RAD_X2	(AP_RAD_X+AP_BTN_W)
#define AP_RAD_Y1	(AP_RAD_Y)
#define AP_RAD_Y2	(AP_RAD_Y+AP_BTN_H)

#define AP_RAD_INSIDE(x, y)  INSIDE(AP_RAD_X1, AP_RAD_X2, AP_RAD_Y1, AP_RAD_Y2, x, y)

//antiradial

#define AP_ARAD_X	(176)
#define AP_ARAD_Y	(16)

#define AP_ARAD_X1	(AP_ARAD_X)
#define AP_ARAD_X2	(AP_ARAD_X+AP_BTN_W)
#define AP_ARAD_Y1	(AP_ARAD_Y)
#define AP_ARAD_Y2	(AP_ARAD_Y+AP_BTN_H)

#define AP_ARAD_INSIDE(x, y)  INSIDE(AP_ARAD_X1, AP_ARAD_X2, AP_ARAD_Y1, AP_ARAD_Y2, x, y)



#endif
