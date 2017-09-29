#include "stopwatch.h"
#include "stopwatch_private.h"

struct stopwatch_ldata {
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t tenths;
	uint8_t alarm_hours;
	uint8_t alarm_minutes;
	uint8_t s_tenths;
	uint8_t s_seconds;
	uint8_t s_minutes;
	uint8_t s_hours;
	uint8_t s_running; // boolean_t
} localdata;

struct stopwatch_odata {
	uint8_t dhours;
	uint8_t dminutes;
	uint8_t dseconds;
	uint8_t dtenths;
	uint8_t dmode;
	uint8_t blink_hours;
	uint8_t blink_minutes;
	uint8_t is_alarm_active;
	uint8_t alarm_ringing;
} outputdata;

struct stopwatch_ldata newdata;


// TODO: some enters could be eliminated due to struct initialization

void control_enter() {
	outputdata.blink_hours = 0;
	outputdata.blink_minutes = 0;
}

stateid_t control_def() {
	return STATE_TIMEMODE;
}

stateid_t control_event_h(event_t e) {
	return STATE_TIMEMODE;
}

extended_state control = STATE_DECL(STATE_CONTROL, STATE_INVALID, control_enter, NULL, NULL, EVENT_TIME, control_event_h, false, control_def);

void timecount_enter() {
	localdata.hours = 0;
	localdata.minutes = 0;
	localdata.seconds = 0;
	localdata.tenths = 0;
	localdata.s_hours = 0;
	localdata.s_minutes = 0;
	localdata.s_seconds = 0;
	localdata.s_tenths = 0;
	localdata.s_running = 0;
}

stateid_t timecount_event_h(event_t e) {
	if(localdata.s_running == 1) {
		localdata.s_tenths = (localdata.s_tenths + 1) % 10;
		if(localdata.s_tenths == 0) {
			localdata.s_seconds = (localdata.s_seconds + 1) % 60;
			if(localdata.s_seconds == 0) {
				localdata.s_minutes = (localdata.s_minutes + 1) % 60;
				if(localdata.s_minutes == 0) {
					localdata.s_hours = (localdata.s_hours + 1) % 24;
				}
			}
		}
	}
	
	localdata.tenths = (localdata.tenths + 1) % 10;
	if(localdata.tenths == 0) {
		localdata.seconds = (localdata.seconds + 1) % 60;
		if(localdata.seconds == 0) {
			localdata.minutes = (localdata.minutes + 1) % 60;
			if(localdata.minutes == 0) {
				localdata.hours = (localdata.hours + 1) % 24;
			}
		}
	}
	
	return STATE_TIMECOUNT;
}

simple_state timecount = STATE_DECL(STATE_TIMECOUNT, STATE_INVALID, timecount_enter, NULL, NULL, EVENT_TIMER_TICK, timecount_event_h, true);

void alarmmanage_enter() {
	localdata.alarm_hours = 0;
	localdata.alarm_minutes = 0;
	outputdata.is_alarm_active = 0;
	outputdata.alarm_ringing = 0;
}

stateid_t alarmmanage_def() {
	return STATE_ALARMOFF;
}

extended_state alarmmanage = STATE_DECL(STATE_ALARMMANAGE, STATE_INVALID, alarmmanage_enter, NULL, NULL, EVENT_NONE, NULL, false, alarmmanage_def);

void timemode_enter() {
	outputdata.dmode = MODE_TIME;
}

void timemode_during() {
	outputdata.dhours = localdata.hours;
	outputdata.dminutes = localdata.minutes;
	outputdata.dseconds = localdata.seconds;
	outputdata.dtenths = localdata.tenths;
}

stateid_t timemode_event_h(event_t e) {
	if(e & EVENT_TIMESET)
		return STATE_TIMESETMODE;
	if(e & EVENT_STOPWATCH)
		return STATE_STOPWATCHMODE;
	if(e & EVENT_ALARM)
		return STATE_ALARMMODE;
	
	return STATE_INVALID; // never happens
}

simple_state timemode = STATE_DECL(STATE_TIMEMODE, STATE_CONTROL, timemode_enter, timemode_during, NULL, EVENT_TIMESET | EVENT_STOPWATCH | EVENT_ALARM, timemode_event_h, true);


void timesetmode_enter() {
	outputdata.dmode = MODE_TIMESET;
	outputdata.dhours = localdata.hours;
	outputdata.dminutes = localdata.minutes;
}

void timesetmode_exit() {
	localdata.hours = outputdata.dhours;
	localdata.minutes = outputdata.dminutes;
}

stateid_t timesetmode_def() {
	return STATE_SETHOURS;
}

stateid_t timesetmode_event_h(event_t e) {
	if(e & EVENT_ALARM)
		return STATE_ALARMMODE;
	if(e & EVENT_STOPWATCH)
		return STATE_STOPWATCHMODE;

	return STATE_INVALID; // never happens
}

extended_state timesetmode = STATE_DECL(STATE_TIMESETMODE, STATE_CONTROL, timesetmode_enter, NULL, timesetmode_exit, EVENT_ALARM | EVENT_TIME | EVENT_STOPWATCH, timesetmode_event_h, false, timesetmode_def);



// TODO: tutto il resto

void alarmmode_enter() {
	outputdata.dmode = MODE_ALARM;
	outputdata.dhours = localdata.alarm_hours;
	outputdata.dminutes = localdata.alarm_minutes;
}

void alarmmode_during() {
	outputdata.dhours = localdata.alarm_hours;
	outputdata.dminutes = localdata.alarm_minutes;
}

stateid_t alarmmode_event_h(event_t e) {
	if(e & EVENT_TIMESET)
		return STATE_TIMESETMODE;
	if(e & EVENT_STOPWATCH)
		return STATE_STOPWATCHMODE;

	return STATE_INVALID; // never happens
}

stateid_t alarmmode_def() {
	return STATE_SETALARMHOURS;
}

extended_state alarmmode = STATE_DECL(STATE_ALARMMODE, STATE_CONTROL, alarmmode_enter, alarmmode_during, NULL, EVENT_STOPWATCH | EVENT_TIMESET, alarmmode_event_h, false, alarmmode_def);


void stopwatchmode_enter() {
	outputdata.dmode = MODE_STOPWATCH;
}

stateid_t stopwatchmode_def() {
	return STATE_STOPWATCHOFF;
}

stateid_t stopwatchmode_event_h(event_t e) {
	if(e & EVENT_TIMESET)
		return STATE_TIMESETMODE;
	if(e & EVENT_ALARM)
		return STATE_ALARMMODE;
	if(e & EVENT_STOPWATCH)
		return STATE_STOPWATCHOFF;

	return STATE_INVALID; // never happens
}

extended_state stopwatchmode = STATE_DECL(STATE_STOPWATCHMODE, STATE_CONTROL, stopwatchmode_enter, NULL, NULL, EVENT_TIMESET | EVENT_ALARM | EVENT_STOPWATCH, stopwatchmode_event_h, false, stopwatchmode_def);

void sethours_enter() {
	outputdata.blink_hours = true;
}

void sethours_exit() {
	outputdata.blink_hours = false;
}

stateid_t sethours_event_h(event_t e) {
	if(e & EVENT_BPLUS) {
		outputdata.dhours = (outputdata.dhours + 1) % 24;
		return STATE_SETHOURS;
	}
	
	if(e & EVENT_BMINUS) {
		outputdata.dhours = (outputdata.dhours == 0) ? 23 : outputdata.dhours - 1;
		return STATE_SETHOURS;
	}
	
	if(e & EVENT_TIMESET) {
		return STATE_SETMINUTES;
	}
	
	return STATE_INVALID;	
}

simple_state sethours = STATE_DECL(STATE_SETHOURS, STATE_TIMESETMODE, sethours_enter, NULL, sethours_exit, EVENT_BPLUS | EVENT_BMINUS | EVENT_TIMESET, sethours_event_h, true);


void setminutes_enter() {
	outputdata.blink_minutes = true;
}

void setminutes_exit() {
	outputdata.blink_minutes = false;
}

stateid_t setminutes_event_h(event_t e) {
	if(e & EVENT_BPLUS) {
		outputdata.dminutes = (outputdata.dminutes + 1) % 24;
		return STATE_SETMINUTES;
	}
	
	if(e & EVENT_BMINUS) {
		outputdata.dminutes = (outputdata.dminutes == 0) ? 23 : outputdata.dminutes - 1;
		return STATE_SETMINUTES;
	}
	
	if(e & EVENT_TIMESET) {
		return STATE_SETHOURS;
	}
	
	return STATE_INVALID;
}

simple_state setminutes = STATE_DECL(STATE_SETMINUTES, STATE_TIMESETMODE, setminutes_enter, NULL, setminutes_exit, EVENT_BPLUS | EVENT_BMINUS | EVENT_TIMESET, setminutes_event_h, true);

/* ----- */

// TODO: optimization later
void setalarmhours_enter() {
	outputdata.blink_hours = true;
}

void setalarmhours_exit() {
	outputdata.blink_hours = false;
}

stateid_t setalarmhours_event_h(event_t e) {
	if(e & EVENT_BPLUS) {
		localdata.alarm_hours = (localdata.alarm_hours + 1) % 24;
		return STATE_SETALARMHOURS;
	}
	
	if(e & EVENT_BMINUS) {
		localdata.alarm_hours = (localdata.alarm_hours == 0) ? 23 : localdata.alarm_hours - 1;
		return STATE_SETALARMHOURS;
	}
	
	if(e & EVENT_ALARM) {
		return STATE_SETALARMMINUTES;
	}
	
	return STATE_INVALID;
}

simple_state setalarmhours = STATE_DECL(STATE_SETALARMHOURS, STATE_ALARMMODE, setalarmhours_enter, NULL, setalarmhours_exit, EVENT_BPLUS | EVENT_BMINUS | EVENT_ALARM, setalarmhours_event_h, true);


void setalarmminutes_enter() {
	outputdata.blink_minutes = true;
}

void setalarmminutes_exit() {
	outputdata.blink_minutes = false;
}

stateid_t setalarmminutes_event_h(event_t e) {
	if(e & EVENT_BPLUS) {
		localdata.alarm_minutes = (localdata.alarm_minutes + 1) % 24;
		return STATE_SETALARMMINUTES;
	}
	
	if(e & EVENT_BMINUS) {
		localdata.alarm_minutes = (localdata.alarm_minutes == 0) ? 23 : localdata.alarm_minutes - 1;
		return STATE_SETALARMMINUTES;
	}
	
	if(e & EVENT_ALARM) {
		return STATE_SETALARMHOURS;
	}
	
	return STATE_INVALID;
}

simple_state setalarmminutes = STATE_DECL(STATE_SETALARMMINUTES, STATE_ALARMMODE, setalarmminutes_enter, NULL, setalarmminutes_exit, EVENT_BPLUS | EVENT_BMINUS | EVENT_ALARM, setalarmminutes_event_h, true);














void stopwatchoff_enter() {
	outputdata.dhours = localdata.s_hours = 0;
	outputdata.dminutes = localdata.s_minutes = 0;
	outputdata.dseconds = localdata.s_seconds = 0;
	outputdata.dtenths = localdata.s_tenths = 0;
}

stateid_t stopwatchoff_event_h(event_t e) {
	return STATE_STOPWATCHRUN;
}

simple_state stopwatchoff = STATE_DECL(STATE_STOPWATCHOFF, STATE_STOPWATCHMODE, stopwatchoff_enter, NULL, NULL, EVENT_BPLUS, stopwatchoff_event_h, true);




void stopwatchrun_enter() {
	localdata.s_running = true;
}

void stopwatchrun_exit() {
	localdata.s_running = false;
}

stateid_t stopwatchrun_event_h(event_t e) {
	return STATE_STOPWATCHPAUSED;
}

stateid_t stopwatchrun_def() {
	return STATE_RUNNING;
}

extended_state stopwatchrun = STATE_DECL(STATE_STOPWATCHRUN, STATE_STOPWATCHMODE, stopwatchrun_enter, NULL, stopwatchrun_exit, EVENT_BPLUS, stopwatchrun_event_h, false, stopwatchrun_def);







void stopwatchpaused_enter() {
	outputdata.dhours = localdata.s_hours;
	outputdata.dminutes = localdata.s_minutes;
	outputdata.dseconds = localdata.s_seconds;
	outputdata.dtenths = localdata.s_tenths;
}

// TODO: optimization

stateid_t stopwatchpaused_event_h(event_t e) {
	return STATE_STOPWATCHRUN;
}

simple_state stopwatchpaused = STATE_DECL(STATE_STOPWATCHPAUSED, STATE_STOPWATCHMODE, stopwatchpaused_enter, NULL, NULL, EVENT_BPLUS, stopwatchpaused_event_h, true);


void running_during() {
	outputdata.dtenths = localdata.s_tenths;
	outputdata.dseconds = localdata.s_seconds;
	outputdata.dminutes = localdata.s_minutes;
	outputdata.dhours = localdata.s_hours;
}

stateid_t running_event_h(event_t e) {
	return STATE_SHOWLAP;
}

simple_state running = STATE_DECL(STATE_RUNNING, STATE_STOPWATCHRUN, NULL, running_during, NULL, EVENT_BMINUS, running_event_h, true);


stateid_t showlap_event_h(event_t e) {
	return STATE_RUNNING;
}

simple_state showlap = STATE_DECL(STATE_SHOWLAP, STATE_STOPWATCHRUN, NULL, NULL, NULL, EVENT_BMINUS, showlap_event_h, true);

void alarmoff_enter() {
	outputdata.is_alarm_active = false;
}

stateid_t alarmoff_event_h(event_t e) {
	return STATE_ALARMON;
}

simple_state alarmoff = STATE_DECL(STATE_ALARMOFF, STATE_ALARMMANAGE, alarmoff_enter, NULL, NULL, EVENT_ALARM_SWITCH, alarmoff_event_h, true);


boolean_t is_alarm_time() {
	return localdata.alarm_hours == localdata.hours &&
		localdata.alarm_minutes == localdata.minutes;
}


void alarmon_enter() {
	outputdata.is_alarm_active = true;
}

stateid_t alarmon_event_h(event_t e) {
	return STATE_ALARMOFF;
}

stateid_t alarmon_def() {
	if(is_alarm_time())
		return STATE_RINGING;
	return STATE_QUIET;
}

extended_state alarmon = STATE_DECL(STATE_ALARMON, STATE_ALARMMANAGE, alarmon_enter, NULL, NULL, EVENT_ALARM_SWITCH, alarmon_event_h, false, alarmon_def);

// TODO: optimization

stateid_t quiet_event_h(event_t e) {
	if(is_alarm_time())
		return STATE_RINGING;
	return STATE_QUIET;
}

simple_state quiet = STATE_DECL(STATE_QUIET, STATE_ALARMON, NULL, NULL, NULL, EVENT_TIMER_TICK, quiet_event_h, true);




void ringing_enter() {
	outputdata.alarm_ringing = true;
}

void ringing_exit() {
	outputdata.alarm_ringing = false;
}

stateid_t ringing_event_h(event_t e) {
	if(e & EVENT_ALARM)
		return STATE_WAITING_NEXT_ACT;
	
	if(e & EVENT_TIMER_TICK) {
		if(is_alarm_time())
			return STATE_RINGING;
		return STATE_QUIET;
	}
	
	return STATE_INVALID;
}

simple_state ringing = STATE_DECL(STATE_RINGING, STATE_ALARMON, ringing_enter, NULL, ringing_exit, EVENT_TIMER_TICK | EVENT_ALARM, ringing_event_h, true);


stateid_t waitingnextact_event_h(event_t e) {
	if(is_alarm_time())
		return STATE_WAITING_NEXT_ACT;
	return STATE_QUIET;
}

simple_state waitingnextact = STATE_DECL(STATE_WAITING_NEXT_ACT, STATE_ALARMON, NULL, NULL, NULL, EVENT_TIMER_TICK, waitingnextact_event_h, true);


#define GET_SP(s) ((state_p) & s)

state_p stopwatch_states[STATE_NUM] = {
	GET_SP(control),
	GET_SP(timecount),
	GET_SP(alarmmanage),
	GET_SP(timemode),
	GET_SP(timesetmode),
	GET_SP(alarmmode),
	GET_SP(stopwatchmode),
	GET_SP(sethours),
	GET_SP(setminutes),
	GET_SP(setalarmhours),
	GET_SP(setalarmminutes),
	GET_SP(stopwatchoff),
	GET_SP(stopwatchrun),
	GET_SP(stopwatchpaused),
	GET_SP(running),
	GET_SP(showlap),
	GET_SP(alarmoff),
	GET_SP(alarmon),
	GET_SP(quiet),
	GET_SP(ringing),
	GET_SP(waitingnextact)
};

state_machine stopwatch_machine;

void stopwatch_init(uint8_t* dmode, uint8_t* dhours, uint8_t* dminutes,
	uint8_t* dseconds, uint8_t* dtenths, uint8_t* blink_hours,
	uint8_t* blink_minutes, uint8_t* is_alarm_active, uint8_t* alarm_ringing) {
	
	stateid_t roots[3] = {STATE_CONTROL, STATE_TIMECOUNT, STATE_ALARMMANAGE};
	
	state_machine_init(&stopwatch_machine, stopwatch_states, roots, 3);
	
	*dhours = outputdata.dhours = 0;
	*dminutes = outputdata.dminutes = 0;
	*dseconds = outputdata.dseconds = 0;
	*dtenths = outputdata.dtenths = 0;
	*dmode = outputdata.dmode = 0;
	*blink_hours = outputdata.blink_hours = 0;
	*blink_minutes = outputdata.blink_minutes = 0;
	*is_alarm_active = outputdata.is_alarm_active = 0;
	*alarm_ringing = outputdata.alarm_ringing = 0;
	
	localdata = newdata;
}

void stopwatch_step(event_t events, uint8_t* dmode, uint8_t* dhours, uint8_t* dminutes, uint8_t* dseconds,
	uint8_t* dtenths, uint8_t* blink_hours, uint8_t* blink_minutes,
	uint8_t* is_alarm_active, uint8_t* alarm_ringing) {
	
	state_machine_step(&stopwatch_machine, events);
	
	*dhours = outputdata.dhours;
	*dminutes = outputdata.dminutes;
	*dseconds = outputdata.dseconds;
	*dtenths = outputdata.dtenths;
	*dmode = outputdata.dmode;
	*blink_hours = outputdata.blink_hours;
	*blink_minutes = outputdata.blink_minutes;
	*is_alarm_active = outputdata.is_alarm_active;
	*alarm_ringing = outputdata.alarm_ringing;
}
