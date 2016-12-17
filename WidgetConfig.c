/*
 * WidgetConfig.c
 *
 *  Created on: 21/ott/2015
 *      Author: admim
 */

#include "Widget.h"
#include "WidgetConfig.h"
#include "pictures.h"
#include "stm32f4_discovery_lcd.h"
#include "fonts.h"

ButtonIcon buttontime = {
		picture_time_active, picture_time_unactive, EVT_TIMEMODE
};

ButtonIcon buttontimeset = {
		picture_timeset_active, picture_timeset_unactive, EVT_TIMESETMODE
};

ButtonIcon buttonalarm = {
		picture_alarm_active, picture_alarm_unactive, EVT_ALARMMODE
};

ButtonIcon buttonswatch = {
		picture_stopwatch_active, picture_stopwatch_unactive, EVT_SWATCHMODE
};

ButtonIcon buttonplus = {
		picture_plus_button, 0, EVT_PLUS
};

ButtonIcon buttonminus = {
		picture_minus_button, 0, EVT_MINUS
};

Text txt = {
		&Font32x48, White
};

#define TXT_EL {&Font32x48, White}

/*extern const unsigned char back_hh_mm[3254];
extern const unsigned char back_hours[3254];
extern const unsigned char back_minutes[3254];
extern const unsigned char back_mm_ss[3254];
extern const unsigned char back_seconds[3254];
extern const unsigned char back_ss_t[3254];
extern const unsigned char back_tenths[3254];
*/

BackText wid_hh_mm = {
		TXT_EL, back_hh_mm
};

BackText wid_hours = {
		TXT_EL, back_hours
};

BackText wid_minutes = {
		TXT_EL, back_minutes
};

BackText wid_mm_ss = {
		TXT_EL, back_mm_ss
};

BackText wid_seconds = {
		TXT_EL, back_seconds
};

BackText wid_ss_t = {
		TXT_EL, back_ss_t
};

BackText wid_tenths = {
		TXT_EL, back_tenths
};


ButtonIcon buttonswitch = {
		picture_switch_on, picture_switch_off, EVT_SWITCH
};

Image backg = {
	picture_background
};

const Widget MyWatchScr[NUMWIDGETS] = {
		{0, 0, 320, 240, BACKGROUND, (void *)&backg},
		{22, 166, 52, 52, BUTTONICON, (void *)&buttontime},
		{96, 166, 52, 52, BUTTONICON, (void *)&buttontimeset},
		{170, 166, 52, 52, BUTTONICON, (void *)&buttonalarm},
		{244, 166, 52, 52, BUTTONICON, (void *)&buttonswatch},
		{250, 48, 40, 40, BUTTONICON, (void *)&buttonplus},
		{250, 107, 40, 40, BUTTONICON, (void *)&buttonminus},
		{100, 0, 100, 52, BUTTONICON, (void *)&buttonswitch},
		{9, 90, 40, 40, BACKTEXT, (void *)&wid_hours},
		{79, 90, 40, 40, BACKTEXT, (void *)&wid_minutes},
		{148, 90, 40, 40, BACKTEXT, (void *)&wid_seconds},
		{223, 90, 40, 40, BACKTEXT, (void *)&wid_tenths},
		{60, 90, 40, 40, BACKTEXT, (void *)&wid_hh_mm},
		{129, 90, 40, 40, BACKTEXT, (void *)&wid_mm_ss},
		{198, 90, 40, 40, BACKTEXT, (void *)&wid_ss_t},
};

