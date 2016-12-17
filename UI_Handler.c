#include "Widget.h"
#include "WidgetConfig.h"
#include "UI_Handler.h"

// TODO: ifndef C++
#define	true	(1)
#define false	(0)


#define BLINK_PERIOD	(10)
#define BLINK_TRESHOLD	(BLINK_PERIOD / 2)

#define RING_PERIOD		(4)
#define RING_TRESHOLD	(RING_PERIOD / 2)


uint8_T blink_counter = 0;
uint8_T oh = 99, om = 99, os = 99, ot = 99, oldmode = 99;
boolean_T is_blink_time = false;
boolean_T hours_drawn = false;
boolean_T minutes_drawn = false;
boolean_T seconds_drawn = false;
boolean_T tenths_drawn = false;

boolean_T was_alarm_active = false;

uint8_T ringing_counter = 0;
boolean_T is_ringing_time = false;
boolean_T was_ringing = false;
boolean_T alarm_icon_active = false;

void init_interface() {
	DrawInit(MyWatchScr);
	WPrint(&MyWatchScr[WID_SEP_HH_MM], ":");

	DrawOff(&MyWatchScr[WID_SWITCH]);
	DrawOn(&MyWatchScr[WID_MINUS]);
	DrawOn(&MyWatchScr[WID_PLUS]);
}

void UpdateMode(unsigned char m)
{

	// TODO: images bigger!!!!

	switch(oldmode) {
	case ARA_MODE_ALARM:
		DrawOff(&MyWatchScr[WID_ALARM]);
		alarm_icon_active = false;
		break;
	case ARA_MODE_TIMESET:
		DrawOff(&MyWatchScr[WID_TIMESET]);
		break;
	case ARA_MODE_TIME:
		DrawOff(&MyWatchScr[WID_TIME]);
		if(m != ARA_MODE_STOPWATCH)
			WErase(&MyWatchScr[WID_SEP_MM_SS]);
		break;
	case ARA_MODE_STOPWATCH:
		DrawOff(&MyWatchScr[WID_STOPWATCH]);
		if(m != ARA_MODE_TIME)
			WErase(&MyWatchScr[WID_SEP_MM_SS]);
		WErase(&MyWatchScr[WID_SEP_SS_T]);
		break;
	}

	switch(m) {
	case ARA_MODE_ALARM:
		DrawOn(&MyWatchScr[WID_ALARM]);
		alarm_icon_active = true;
		break;
	case ARA_MODE_TIMESET:
		DrawOn(&MyWatchScr[WID_TIMESET]);
		break;
	case ARA_MODE_TIME:
		DrawOn(&MyWatchScr[WID_TIME]);
		if(oldmode != ARA_MODE_STOPWATCH)
			WPrint(&MyWatchScr[WID_SEP_MM_SS], ":");
		blink_counter = 0;
		break;
	case ARA_MODE_STOPWATCH:
		DrawOn(&MyWatchScr[WID_STOPWATCH]);
		if(oldmode != ARA_MODE_TIME)
			WPrint(&MyWatchScr[WID_SEP_MM_SS], ":");
		WPrint(&MyWatchScr[WID_SEP_SS_T], ".");
		blink_counter = 0;
		break;
	}

	oldmode = m;
}

void strencode2digit(char *str, int digit)
{
	str[2]=0;
	str[0]=digit/10+'0';
	str[1]=digit%10+'0';
}

void strencode1digit(char *str, int digit)
{
	str[1]=0;
	str[0]=digit%10+'0';
}

void update_ringing_interface(uint8_T is_alarm_active, uint8_T is_alarm_ringing) {
	if(is_alarm_active != was_alarm_active) {
		if(is_alarm_active)
			DrawOn(&MyWatchScr[WID_SWITCH]);
		else
			DrawOff(&MyWatchScr[WID_SWITCH]);
	}

	if(is_alarm_ringing) {
		if(!was_ringing)
			ringing_counter = 0;

		is_ringing_time = ringing_counter >= RING_TRESHOLD;
		ringing_counter = ++ringing_counter % RING_PERIOD;

		if(is_ringing_time && alarm_icon_active) {
			DrawOff(&MyWatchScr[WID_ALARM]);
			alarm_icon_active = false;
		}

		if(!is_ringing_time && !alarm_icon_active) {
			DrawOn(&MyWatchScr[WID_ALARM]);
			alarm_icon_active = true;
		}
	}

	if(was_ringing && !is_alarm_ringing) {
		if(alarm_icon_active && oldmode != ARA_MODE_ALARM) {
			DrawOff(&MyWatchScr[WID_ALARM]);
			alarm_icon_active = false;
		}

		if(!alarm_icon_active && oldmode == ARA_MODE_ALARM) {
			DrawOn(&MyWatchScr[WID_ALARM]);
			alarm_icon_active = true;
		}
	}

	was_ringing = is_alarm_ringing;
	was_alarm_active = is_alarm_active;
}

void update_interface(uint8_T mode, uint8_T * time, uint8_T * blink, uint8_T is_alarm_active, uint8_T is_alarm_ringing) {
	char tstr[3];

	if (mode != oldmode)
		UpdateMode(mode);

	is_blink_time = blink_counter >= BLINK_TRESHOLD;

	blink_counter = ++blink_counter % BLINK_PERIOD;

	// TODO: is_ringing

	update_ringing_interface(is_alarm_active, is_alarm_ringing);


	// Erase everything not needed

	if(hours_drawn && ((is_blink_time && blink[ARA_BLINK_HOURS]) || time[ARA_TIME_HOURS] != oh)) {
		WErase(&MyWatchScr[WID_TIME_HOURS]);
		hours_drawn = false;
	}

	if(minutes_drawn && ((is_blink_time && blink[ARA_BLINK_MINUTES]) || time[ARA_TIME_MINUTES] != om)) {
		WErase(&MyWatchScr[WID_TIME_MINS]);
		minutes_drawn = false;
	}

	if(seconds_drawn && (!(mode == ARA_MODE_TIME || mode == ARA_MODE_STOPWATCH) || time[ARA_TIME_SECONDS] != os)) {
		WErase(&MyWatchScr[WID_TIME_SECS]);
		seconds_drawn = false;
	}

	if(tenths_drawn && (mode != ARA_MODE_STOPWATCH || time[ARA_TIME_TENTHS] != ot)) {
		WErase(&MyWatchScr[WID_TIME_TENTHS]);
		tenths_drawn = false;
	}

	// Writing everything needed

	if(!hours_drawn && !(is_blink_time && blink[ARA_BLINK_HOURS])) {
		strencode2digit(tstr, time[ARA_TIME_HOURS]);
		WPrint(&MyWatchScr[WID_TIME_HOURS], tstr);
		oh=time[ARA_TIME_HOURS];
		hours_drawn = true;
	}

	if(!minutes_drawn && !(is_blink_time && blink[ARA_BLINK_MINUTES])) {
		strencode2digit(tstr, time[ARA_TIME_MINUTES]);
		WPrint(&MyWatchScr[WID_TIME_MINS], tstr);
		om=time[ARA_TIME_MINUTES];
		minutes_drawn = true;
	}

	if(!seconds_drawn && (mode == ARA_MODE_TIME || mode == ARA_MODE_STOPWATCH)) {
		strencode2digit(tstr, time[ARA_TIME_SECONDS]);
		WPrint(&MyWatchScr[WID_TIME_SECS], tstr);
		os=time[ARA_TIME_SECONDS];
		seconds_drawn = true;
	}

	if(!tenths_drawn && (mode == ARA_MODE_STOPWATCH)) {
		strencode1digit(tstr, time[ARA_TIME_TENTHS]);
		WPrint(&MyWatchScr[WID_TIME_TENTHS], tstr);
		ot=time[ARA_TIME_TENTHS];
		tenths_drawn = true;
	}
}
