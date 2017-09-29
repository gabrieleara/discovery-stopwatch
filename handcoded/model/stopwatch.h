#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "simple_types.h"

// TODO: Method for initialization and for tick
#define EVENT_NONE				(0)
#define EVENT_TIMER_TICK		(1)
#define EVENT_BPLUS				(2)
#define EVENT_BMINUS			(4)
#define EVENT_TIME				(8)
#define EVENT_TIMESET			(16)
#define EVENT_ALARM				(32)
#define EVENT_STOPWATCH			(64)
#define EVENT_ALARM_SWITCH		(128)


#define MODE_TIME				0
#define MODE_TIMESET			1
#define MODE_ALARM				2
#define MODE_STOPWATCH			3

extern void stopwatch_step(event_t events, uint8_t* dmode, uint8_t* dhours,
	uint8_t* dminutes, uint8_t* dseconds, uint8_t* dtenths,
	uint8_t* blink_hours, uint8_t* blink_minutes, uint8_t* is_alarm_active,
	uint8_t* alarm_ringing);
	
	
extern void stopwatch_init(uint8_t* dmode, uint8_t* dhours, uint8_t* dminutes,
	uint8_t* dseconds, uint8_t* dtenths, uint8_t* blink_hours,
	uint8_t* blink_minutes, uint8_t* is_alarm_active, uint8_t* alarm_ringing);


#endif
