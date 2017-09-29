#ifndef UI_HANDLER_H
#define UI_HANDLER_H

#define ARA_TIME_HOURS			0
#define ARA_TIME_MINUTES		1
#define ARA_TIME_SECONDS		2
#define ARA_TIME_TENTHS			3

#define ARA_BLINK_HOURS			0
#define ARA_BLINK_MINUTES		1

#define ARA_MODE_TIME			0
#define ARA_MODE_TIMESET		1
#define ARA_MODE_ALARM			2
#define ARA_MODE_STOPWATCH		3

#include "simulink/rtwtypes.h"

extern void update_interface(uint8_T mode, uint8_T * time, uint8_T * blink, uint8_T is_alarm_active, uint8_T is_alarm_ringing);
extern void init_interface();

#endif
