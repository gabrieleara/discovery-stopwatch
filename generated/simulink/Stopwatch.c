/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Stopwatch.c
 *
 * Code generated for Simulink model 'Stopwatch'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 8.11 (R2016b) 25-Aug-2016
 * C/C++ source code generated on : Sat Dec 17 12:28:18 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Stopwatch.h"
#include "Stopwatch_private.h"

/* Named constants for Chart: '<S1>/Stopwatch' */
#define Stop_IN_waiting_next_activation ((uint8_T)3U)
#define Stopwatch_IN_NO_ACTIVE_CHILD   ((uint8_T)0U)
#define Stopwatch_IN_alarmOff          ((uint8_T)1U)
#define Stopwatch_IN_alarmOn           ((uint8_T)2U)
#define Stopwatch_IN_alarmmode         ((uint8_T)1U)
#define Stopwatch_IN_quiet             ((uint8_T)1U)
#define Stopwatch_IN_ringing           ((uint8_T)2U)
#define Stopwatch_IN_running           ((uint8_T)1U)
#define Stopwatch_IN_setAlarmHours     ((uint8_T)1U)
#define Stopwatch_IN_setAlarmMinutes   ((uint8_T)2U)
#define Stopwatch_IN_setHours          ((uint8_T)1U)
#define Stopwatch_IN_setMinutes        ((uint8_T)2U)
#define Stopwatch_IN_showLap           ((uint8_T)2U)
#define Stopwatch_IN_stopwatchOff      ((uint8_T)1U)
#define Stopwatch_IN_stopwatchPaused   ((uint8_T)2U)
#define Stopwatch_IN_stopwatchRunning  ((uint8_T)3U)
#define Stopwatch_IN_stopwatchmode     ((uint8_T)2U)
#define Stopwatch_IN_timemode          ((uint8_T)3U)
#define Stopwatch_IN_timesetmode       ((uint8_T)4U)
#define Stopwatch_event_alarm          (5)
#define Stopwatch_event_alarm_switch   (7)
#define Stopwatch_event_bminus         (2)
#define Stopwatch_event_bplus          (1)
#define Stopwatch_event_stopwatch      (6)
#define Stopwatch_event_time           (3)
#define Stopwatch_event_timer_tick     (0)
#define Stopwatch_event_timeset        (4)

/* Forward declaration for local functions */
static void Stopwatch_stopwatchmode(uint8_T *Stopwatch_Y_hours, uint8_T
  *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T
  *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, DW_Stopwatch_T *Stopwatch_DW);
static void Stopwatch_timemode(uint8_T *Stopwatch_Y_hours, uint8_T
  *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T
  *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, DW_Stopwatch_T *Stopwatch_DW);
static void Stopwatch_exit_internal_Control(uint8_T *Stopwatch_Y_hours, uint8_T *
  Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_blink_hours, uint8_T
  *Stopwatch_Y_blink_minutes, DW_Stopwatch_T *Stopwatch_DW);
static void Stopwatch_Control(uint8_T *Stopwatch_Y_hours, uint8_T
  *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T
  *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, uint8_T *Stopwatch_Y_blink_minutes, DW_Stopwatch_T
  *Stopwatch_DW);
static void Stopwatc_chartstep_c3_Stopwatch(uint8_T *Stopwatch_Y_hours, uint8_T *
  Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T *Stopwatch_Y_tenths,
  uint8_T *Stopwatch_Y_mode, uint8_T *Stopwatch_Y_blink_hours, uint8_T
  *Stopwatch_Y_blink_minutes, uint8_T *Stopwatch_Y_is_alarm_active, uint8_T
  *Stopwatch_Y_alarm_ringing, DW_Stopwatch_T *Stopwatch_DW);

/* Function for Chart: '<S1>/Stopwatch' */
static void Stopwatch_stopwatchmode(uint8_T *Stopwatch_Y_hours, uint8_T
  *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T
  *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, DW_Stopwatch_T *Stopwatch_DW)
{
  /* During 'stopwatchmode': '<S2>:7' */
  /* '<S2>:38:1' sf_internal_predicateOutput = ... */
  /* '<S2>:38:1' timeset; */
  switch (Stopwatch_DW->sfEvent) {
   case Stopwatch_event_timeset:
    /* Transition: '<S2>:38' */
    /* Exit Internal 'stopwatchmode': '<S2>:7' */
    if (Stopwatch_DW->is_stopwatchmode == Stopwatch_IN_stopwatchRunning) {
      /* Exit Internal 'stopwatchRunning': '<S2>:134' */
      Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_NO_ACTIVE_CHILD;

      /* Exit 'stopwatchRunning': '<S2>:134' */
      /* '<S2>:134:1' s_running = uint8(0); */
      Stopwatch_DW->s_running = 0U;
      Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    } else {
      Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    }

    Stopwatch_DW->is_Control = Stopwatch_IN_timesetmode;

    /* Entry 'timesetmode': '<S2>:5' */
    /* '<S2>:5:1' dmode = uint8(1); */
    *Stopwatch_Y_mode = 1U;

    /* '<S2>:5:1' dhours = hours; */
    *Stopwatch_Y_hours = Stopwatch_DW->hours;

    /* '<S2>:5:1' dminutes = minutes; */
    *Stopwatch_Y_minutes = Stopwatch_DW->minutes;

    /* Entry Internal 'timesetmode': '<S2>:5' */
    /* Transition: '<S2>:84' */
    Stopwatch_DW->is_timesetmode = Stopwatch_IN_setHours;

    /* Entry 'setHours': '<S2>:71' */
    /* '<S2>:71:1' blink_hours = uint8(1); */
    *Stopwatch_Y_blink_hours = 1U;
    break;

   case Stopwatch_event_alarm:
    /* '<S2>:41:1' sf_internal_predicateOutput = ... */
    /* '<S2>:41:1' alarm; */
    /* Transition: '<S2>:41' */
    /* Exit Internal 'stopwatchmode': '<S2>:7' */
    if (Stopwatch_DW->is_stopwatchmode == Stopwatch_IN_stopwatchRunning) {
      /* Exit Internal 'stopwatchRunning': '<S2>:134' */
      Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_NO_ACTIVE_CHILD;

      /* Exit 'stopwatchRunning': '<S2>:134' */
      /* '<S2>:134:1' s_running = uint8(0); */
      Stopwatch_DW->s_running = 0U;
      Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    } else {
      Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    }

    Stopwatch_DW->is_Control = Stopwatch_IN_alarmmode;

    /* Entry 'alarmmode': '<S2>:6' */
    /* '<S2>:6:1' dmode = uint8(2); */
    *Stopwatch_Y_mode = 2U;

    /* '<S2>:6:1' dhours = alarm_hours; */
    *Stopwatch_Y_hours = Stopwatch_DW->alarm_hours;

    /* '<S2>:6:2' dminutes = alarm_minutes; */
    *Stopwatch_Y_minutes = Stopwatch_DW->alarm_minutes;

    /* Entry Internal 'alarmmode': '<S2>:6' */
    /* Transition: '<S2>:96' */
    Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmHours;

    /* Entry 'setAlarmHours': '<S2>:93' */
    /* '<S2>:93:1' blink_hours = uint8(1); */
    *Stopwatch_Y_blink_hours = 1U;
    break;

   case Stopwatch_event_stopwatch:
    /* '<S2>:137:1' sf_internal_predicateOutput = ... */
    /* '<S2>:137:1' stopwatch; */
    /* Transition: '<S2>:137' */
    /* Exit Internal 'stopwatchmode': '<S2>:7' */
    if (Stopwatch_DW->is_stopwatchmode == Stopwatch_IN_stopwatchRunning) {
      /* Exit Internal 'stopwatchRunning': '<S2>:134' */
      Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_NO_ACTIVE_CHILD;

      /* Exit 'stopwatchRunning': '<S2>:134' */
      /* '<S2>:134:1' s_running = uint8(0); */
      Stopwatch_DW->s_running = 0U;
      Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    } else {
      Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    }

    Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_stopwatchOff;

    /* Entry 'stopwatchOff': '<S2>:133' */
    /* '<S2>:133:1' s_hours = uint8(0); */
    Stopwatch_DW->s_hours = 0U;

    /* '<S2>:133:1' s_minutes = uint8(0); */
    Stopwatch_DW->s_minutes = 0U;

    /* '<S2>:133:2' s_seconds = uint8(0); */
    Stopwatch_DW->s_seconds = 0U;

    /* '<S2>:133:2' s_tenths = uint8(0); */
    Stopwatch_DW->s_tenths = 0U;

    /* '<S2>:133:2' dtenths = s_tenths; */
    *Stopwatch_Y_tenths = Stopwatch_DW->s_tenths;

    /* '<S2>:133:2' dseconds = s_seconds; */
    *Stopwatch_Y_seconds = Stopwatch_DW->s_seconds;

    /* '<S2>:133:2' dminutes = s_minutes; */
    *Stopwatch_Y_minutes = Stopwatch_DW->s_minutes;

    /* '<S2>:133:2' dhours = s_hours; */
    *Stopwatch_Y_hours = Stopwatch_DW->s_hours;
    break;

   default:
    switch (Stopwatch_DW->is_stopwatchmode) {
     case Stopwatch_IN_stopwatchOff:
      /* During 'stopwatchOff': '<S2>:133' */
      /* '<S2>:136:1' sf_internal_predicateOutput = ... */
      /* '<S2>:136:1' bplus; */
      if (Stopwatch_DW->sfEvent == Stopwatch_event_bplus) {
        /* Transition: '<S2>:136' */
        Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_stopwatchRunning;

        /* Entry 'stopwatchRunning': '<S2>:134' */
        /* '<S2>:134:1' s_running = uint8(1); */
        Stopwatch_DW->s_running = 1U;

        /* Entry Internal 'stopwatchRunning': '<S2>:134' */
        /* Transition: '<S2>:141' */
        Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_running;
      }
      break;

     case Stopwatch_IN_stopwatchPaused:
      /* During 'stopwatchPaused': '<S2>:226' */
      /* '<S2>:227:1' sf_internal_predicateOutput = ... */
      /* '<S2>:227:1' bplus; */
      if (Stopwatch_DW->sfEvent == Stopwatch_event_bplus) {
        /* Transition: '<S2>:227' */
        Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_stopwatchRunning;

        /* Entry 'stopwatchRunning': '<S2>:134' */
        /* '<S2>:134:1' s_running = uint8(1); */
        Stopwatch_DW->s_running = 1U;

        /* Entry Internal 'stopwatchRunning': '<S2>:134' */
        /* Transition: '<S2>:141' */
        Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_running;
      }
      break;

     default:
      /* During 'stopwatchRunning': '<S2>:134' */
      /* '<S2>:225:1' sf_internal_predicateOutput = ... */
      /* '<S2>:225:1' bplus; */
      if (Stopwatch_DW->sfEvent == Stopwatch_event_bplus) {
        /* Transition: '<S2>:225' */
        /* Exit Internal 'stopwatchRunning': '<S2>:134' */
        Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_NO_ACTIVE_CHILD;

        /* Exit 'stopwatchRunning': '<S2>:134' */
        /* '<S2>:134:1' s_running = uint8(0); */
        Stopwatch_DW->s_running = 0U;
        Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_stopwatchPaused;

        /* Entry 'stopwatchPaused': '<S2>:226' */
        /* '<S2>:226:1' dtenths = s_tenths; */
        *Stopwatch_Y_tenths = Stopwatch_DW->s_tenths;

        /* '<S2>:226:1' dseconds = s_seconds; */
        *Stopwatch_Y_seconds = Stopwatch_DW->s_seconds;

        /* '<S2>:226:2' dminutes = s_minutes; */
        *Stopwatch_Y_minutes = Stopwatch_DW->s_minutes;

        /* '<S2>:226:2' dhours = s_hours; */
        *Stopwatch_Y_hours = Stopwatch_DW->s_hours;
      } else if (Stopwatch_DW->is_stopwatchRunning == Stopwatch_IN_running) {
        /* During 'running': '<S2>:138' */
        /* '<S2>:222:1' sf_internal_predicateOutput = ... */
        /* '<S2>:222:1' bminus; */
        if (Stopwatch_DW->sfEvent == Stopwatch_event_bminus) {
          /* Transition: '<S2>:222' */
          Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_showLap;
        } else {
          /* '<S2>:138:1' dtenths = s_tenths; */
          *Stopwatch_Y_tenths = Stopwatch_DW->s_tenths;

          /* '<S2>:138:1' dseconds = s_seconds; */
          *Stopwatch_Y_seconds = Stopwatch_DW->s_seconds;

          /* '<S2>:138:2' dminutes = s_minutes; */
          *Stopwatch_Y_minutes = Stopwatch_DW->s_minutes;

          /* '<S2>:138:2' dhours = s_hours; */
          *Stopwatch_Y_hours = Stopwatch_DW->s_hours;
        }
      } else {
        /* During 'showLap': '<S2>:223' */
        /* '<S2>:224:1' sf_internal_predicateOutput = ... */
        /* '<S2>:224:1' bminus; */
        if (Stopwatch_DW->sfEvent == Stopwatch_event_bminus) {
          /* Transition: '<S2>:224' */
          Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_running;
        }
      }
      break;
    }
    break;
  }
}

/* Function for Chart: '<S1>/Stopwatch' */
static void Stopwatch_timemode(uint8_T *Stopwatch_Y_hours, uint8_T
  *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T
  *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, DW_Stopwatch_T *Stopwatch_DW)
{
  /* During 'timemode': '<S2>:60' */
  /* '<S2>:36:1' sf_internal_predicateOutput = ... */
  /* '<S2>:36:1' timeset; */
  switch (Stopwatch_DW->sfEvent) {
   case Stopwatch_event_timeset:
    /* Transition: '<S2>:36' */
    Stopwatch_DW->is_Control = Stopwatch_IN_timesetmode;

    /* Entry 'timesetmode': '<S2>:5' */
    /* '<S2>:5:1' dmode = uint8(1); */
    *Stopwatch_Y_mode = 1U;

    /* '<S2>:5:1' dhours = hours; */
    *Stopwatch_Y_hours = Stopwatch_DW->hours;

    /* '<S2>:5:1' dminutes = minutes; */
    *Stopwatch_Y_minutes = Stopwatch_DW->minutes;

    /* Entry Internal 'timesetmode': '<S2>:5' */
    /* Transition: '<S2>:84' */
    Stopwatch_DW->is_timesetmode = Stopwatch_IN_setHours;

    /* Entry 'setHours': '<S2>:71' */
    /* '<S2>:71:1' blink_hours = uint8(1); */
    *Stopwatch_Y_blink_hours = 1U;
    break;

   case Stopwatch_event_stopwatch:
    /* '<S2>:237:1' sf_internal_predicateOutput = ... */
    /* '<S2>:237:1' stopwatch; */
    /* Transition: '<S2>:237' */
    Stopwatch_DW->is_Control = Stopwatch_IN_stopwatchmode;

    /* Entry 'stopwatchmode': '<S2>:7' */
    /* '<S2>:7:1' dmode = uint8(3); */
    *Stopwatch_Y_mode = 3U;

    /* Entry Internal 'stopwatchmode': '<S2>:7' */
    /* Transition: '<S2>:135' */
    Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_stopwatchOff;

    /* Entry 'stopwatchOff': '<S2>:133' */
    /* '<S2>:133:1' s_hours = uint8(0); */
    Stopwatch_DW->s_hours = 0U;

    /* '<S2>:133:1' s_minutes = uint8(0); */
    Stopwatch_DW->s_minutes = 0U;

    /* '<S2>:133:2' s_seconds = uint8(0); */
    Stopwatch_DW->s_seconds = 0U;

    /* '<S2>:133:2' s_tenths = uint8(0); */
    Stopwatch_DW->s_tenths = 0U;

    /* '<S2>:133:2' dtenths = s_tenths; */
    *Stopwatch_Y_tenths = Stopwatch_DW->s_tenths;

    /* '<S2>:133:2' dseconds = s_seconds; */
    *Stopwatch_Y_seconds = Stopwatch_DW->s_seconds;

    /* '<S2>:133:2' dminutes = s_minutes; */
    *Stopwatch_Y_minutes = Stopwatch_DW->s_minutes;

    /* '<S2>:133:2' dhours = s_hours; */
    *Stopwatch_Y_hours = Stopwatch_DW->s_hours;
    break;

   case Stopwatch_event_alarm:
    /* '<S2>:40:1' sf_internal_predicateOutput = ... */
    /* '<S2>:40:1' alarm; */
    /* Transition: '<S2>:40' */
    Stopwatch_DW->is_Control = Stopwatch_IN_alarmmode;

    /* Entry 'alarmmode': '<S2>:6' */
    /* '<S2>:6:1' dmode = uint8(2); */
    *Stopwatch_Y_mode = 2U;

    /* '<S2>:6:1' dhours = alarm_hours; */
    *Stopwatch_Y_hours = Stopwatch_DW->alarm_hours;

    /* '<S2>:6:2' dminutes = alarm_minutes; */
    *Stopwatch_Y_minutes = Stopwatch_DW->alarm_minutes;

    /* Entry Internal 'alarmmode': '<S2>:6' */
    /* Transition: '<S2>:96' */
    Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmHours;

    /* Entry 'setAlarmHours': '<S2>:93' */
    /* '<S2>:93:1' blink_hours = uint8(1); */
    *Stopwatch_Y_blink_hours = 1U;
    break;

   default:
    /* '<S2>:60:1' dhours = hours; */
    *Stopwatch_Y_hours = Stopwatch_DW->hours;

    /* '<S2>:60:1' dminutes = minutes; */
    *Stopwatch_Y_minutes = Stopwatch_DW->minutes;

    /* '<S2>:60:2' dseconds = seconds; */
    *Stopwatch_Y_seconds = Stopwatch_DW->seconds;

    /* '<S2>:60:2' dtenths = tenths; */
    *Stopwatch_Y_tenths = Stopwatch_DW->tenths;
    break;
  }
}

/* Function for Chart: '<S1>/Stopwatch' */
static void Stopwatch_exit_internal_Control(uint8_T *Stopwatch_Y_hours, uint8_T *
  Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_blink_hours, uint8_T
  *Stopwatch_Y_blink_minutes, DW_Stopwatch_T *Stopwatch_DW)
{
  /* Exit Internal 'Control': '<S2>:1' */
  switch (Stopwatch_DW->is_Control) {
   case Stopwatch_IN_alarmmode:
    /* Exit Internal 'alarmmode': '<S2>:6' */
    switch (Stopwatch_DW->is_alarmmode) {
     case Stopwatch_IN_setAlarmHours:
      /* Exit 'setAlarmHours': '<S2>:93' */
      /* '<S2>:93:1' blink_hours = uint8(0); */
      *Stopwatch_Y_blink_hours = 0U;
      Stopwatch_DW->is_alarmmode = Stopwatch_IN_NO_ACTIVE_CHILD;
      break;

     case Stopwatch_IN_setAlarmMinutes:
      /* Exit 'setAlarmMinutes': '<S2>:99' */
      /* '<S2>:99:1' blink_minutes = uint8(0); */
      *Stopwatch_Y_blink_minutes = 0U;
      Stopwatch_DW->is_alarmmode = Stopwatch_IN_NO_ACTIVE_CHILD;
      break;
    }

    Stopwatch_DW->is_Control = Stopwatch_IN_NO_ACTIVE_CHILD;
    break;

   case Stopwatch_IN_stopwatchmode:
    /* Exit Internal 'stopwatchmode': '<S2>:7' */
    if (Stopwatch_DW->is_stopwatchmode == Stopwatch_IN_stopwatchRunning) {
      /* Exit Internal 'stopwatchRunning': '<S2>:134' */
      Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_NO_ACTIVE_CHILD;

      /* Exit 'stopwatchRunning': '<S2>:134' */
      /* '<S2>:134:1' s_running = uint8(0); */
      Stopwatch_DW->s_running = 0U;
      Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    } else {
      Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    }

    Stopwatch_DW->is_Control = Stopwatch_IN_NO_ACTIVE_CHILD;
    break;

   case Stopwatch_IN_timesetmode:
    /* Exit Internal 'timesetmode': '<S2>:5' */
    switch (Stopwatch_DW->is_timesetmode) {
     case Stopwatch_IN_setHours:
      /* Exit 'setHours': '<S2>:71' */
      /* '<S2>:71:1' blink_hours = uint8(0); */
      *Stopwatch_Y_blink_hours = 0U;
      Stopwatch_DW->is_timesetmode = Stopwatch_IN_NO_ACTIVE_CHILD;
      break;

     case Stopwatch_IN_setMinutes:
      /* Exit 'setMinutes': '<S2>:78' */
      /* '<S2>:78:1' blink_minutes = uint8(0); */
      *Stopwatch_Y_blink_minutes = 0U;
      Stopwatch_DW->is_timesetmode = Stopwatch_IN_NO_ACTIVE_CHILD;
      break;
    }

    /* Exit 'timesetmode': '<S2>:5' */
    /* '<S2>:5:2' hours = dhours; */
    Stopwatch_DW->hours = *Stopwatch_Y_hours;

    /* '<S2>:5:2' minutes = dminutes; */
    Stopwatch_DW->minutes = *Stopwatch_Y_minutes;
    Stopwatch_DW->is_Control = Stopwatch_IN_NO_ACTIVE_CHILD;
    break;

   default:
    Stopwatch_DW->is_Control = Stopwatch_IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<S1>/Stopwatch' */
static void Stopwatch_Control(uint8_T *Stopwatch_Y_hours, uint8_T
  *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T
  *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, uint8_T *Stopwatch_Y_blink_minutes, DW_Stopwatch_T
  *Stopwatch_DW)
{
  int32_T tmp;
  uint32_T qY;

  /* During 'Control': '<S2>:1' */
  /* '<S2>:62:1' sf_internal_predicateOutput = ... */
  /* '<S2>:62:1' time; */
  if (Stopwatch_DW->sfEvent == Stopwatch_event_time) {
    /* Transition: '<S2>:62' */
    Stopwatch_exit_internal_Control(Stopwatch_Y_hours, Stopwatch_Y_minutes,
      Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes, Stopwatch_DW);
    Stopwatch_DW->is_Control = Stopwatch_IN_timemode;

    /* Entry 'timemode': '<S2>:60' */
    /* '<S2>:60:1' dmode = uint8(0); */
    *Stopwatch_Y_mode = 0U;
  } else {
    switch (Stopwatch_DW->is_Control) {
     case Stopwatch_IN_alarmmode:
      /* During 'alarmmode': '<S2>:6' */
      /* '<S2>:39:1' sf_internal_predicateOutput = ... */
      /* '<S2>:39:1' timeset; */
      switch (Stopwatch_DW->sfEvent) {
       case Stopwatch_event_timeset:
        /* Transition: '<S2>:39' */
        /* Exit Internal 'alarmmode': '<S2>:6' */
        switch (Stopwatch_DW->is_alarmmode) {
         case Stopwatch_IN_setAlarmHours:
          /* Exit 'setAlarmHours': '<S2>:93' */
          /* '<S2>:93:1' blink_hours = uint8(0); */
          *Stopwatch_Y_blink_hours = 0U;
          Stopwatch_DW->is_alarmmode = Stopwatch_IN_NO_ACTIVE_CHILD;
          break;

         case Stopwatch_IN_setAlarmMinutes:
          /* Exit 'setAlarmMinutes': '<S2>:99' */
          /* '<S2>:99:1' blink_minutes = uint8(0); */
          *Stopwatch_Y_blink_minutes = 0U;
          Stopwatch_DW->is_alarmmode = Stopwatch_IN_NO_ACTIVE_CHILD;
          break;
        }

        Stopwatch_DW->is_Control = Stopwatch_IN_timesetmode;

        /* Entry 'timesetmode': '<S2>:5' */
        /* '<S2>:5:1' dmode = uint8(1); */
        *Stopwatch_Y_mode = 1U;

        /* '<S2>:5:1' dhours = hours; */
        *Stopwatch_Y_hours = Stopwatch_DW->hours;

        /* '<S2>:5:1' dminutes = minutes; */
        *Stopwatch_Y_minutes = Stopwatch_DW->minutes;

        /* Entry Internal 'timesetmode': '<S2>:5' */
        /* Transition: '<S2>:84' */
        Stopwatch_DW->is_timesetmode = Stopwatch_IN_setHours;

        /* Entry 'setHours': '<S2>:71' */
        /* '<S2>:71:1' blink_hours = uint8(1); */
        *Stopwatch_Y_blink_hours = 1U;
        break;

       case Stopwatch_event_stopwatch:
        /* '<S2>:236:1' sf_internal_predicateOutput = ... */
        /* '<S2>:236:1' stopwatch; */
        /* Transition: '<S2>:236' */
        /* Exit Internal 'alarmmode': '<S2>:6' */
        switch (Stopwatch_DW->is_alarmmode) {
         case Stopwatch_IN_setAlarmHours:
          /* Exit 'setAlarmHours': '<S2>:93' */
          /* '<S2>:93:1' blink_hours = uint8(0); */
          *Stopwatch_Y_blink_hours = 0U;
          Stopwatch_DW->is_alarmmode = Stopwatch_IN_NO_ACTIVE_CHILD;
          break;

         case Stopwatch_IN_setAlarmMinutes:
          /* Exit 'setAlarmMinutes': '<S2>:99' */
          /* '<S2>:99:1' blink_minutes = uint8(0); */
          *Stopwatch_Y_blink_minutes = 0U;
          Stopwatch_DW->is_alarmmode = Stopwatch_IN_NO_ACTIVE_CHILD;
          break;
        }

        Stopwatch_DW->is_Control = Stopwatch_IN_stopwatchmode;

        /* Entry 'stopwatchmode': '<S2>:7' */
        /* '<S2>:7:1' dmode = uint8(3); */
        *Stopwatch_Y_mode = 3U;

        /* Entry Internal 'stopwatchmode': '<S2>:7' */
        /* Transition: '<S2>:135' */
        Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_stopwatchOff;

        /* Entry 'stopwatchOff': '<S2>:133' */
        /* '<S2>:133:1' s_hours = uint8(0); */
        Stopwatch_DW->s_hours = 0U;

        /* '<S2>:133:1' s_minutes = uint8(0); */
        Stopwatch_DW->s_minutes = 0U;

        /* '<S2>:133:2' s_seconds = uint8(0); */
        Stopwatch_DW->s_seconds = 0U;

        /* '<S2>:133:2' s_tenths = uint8(0); */
        Stopwatch_DW->s_tenths = 0U;

        /* '<S2>:133:2' dtenths = s_tenths; */
        *Stopwatch_Y_tenths = Stopwatch_DW->s_tenths;

        /* '<S2>:133:2' dseconds = s_seconds; */
        *Stopwatch_Y_seconds = Stopwatch_DW->s_seconds;

        /* '<S2>:133:2' dminutes = s_minutes; */
        *Stopwatch_Y_minutes = Stopwatch_DW->s_minutes;

        /* '<S2>:133:2' dhours = s_hours; */
        *Stopwatch_Y_hours = Stopwatch_DW->s_hours;
        break;

       default:
        /* '<S2>:6:2' dhours = alarm_hours; */
        *Stopwatch_Y_hours = Stopwatch_DW->alarm_hours;

        /* '<S2>:6:2' dminutes = alarm_minutes; */
        *Stopwatch_Y_minutes = Stopwatch_DW->alarm_minutes;
        if (Stopwatch_DW->is_alarmmode == Stopwatch_IN_setAlarmHours) {
          /* During 'setAlarmHours': '<S2>:93' */
          /* '<S2>:98:1' sf_internal_predicateOutput = ... */
          /* '<S2>:98:1' bplus; */
          if (Stopwatch_DW->sfEvent == Stopwatch_event_bplus) {
            /* Transition: '<S2>:98' */
            /* '<S2>:98:1' alarm_hours = mod(alarm_hours + 1, 24) */
            tmp = (int32_T)(Stopwatch_DW->alarm_hours + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            Stopwatch_DW->alarm_hours = (uint8_T)((uint32_T)(uint8_T)tmp -
              (uint8_T)((uint8_T)tmp / 24U * 24U));

            /* Exit 'setAlarmHours': '<S2>:93' */
            /* '<S2>:93:1' blink_hours = uint8(0); */
            Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmHours;

            /* Entry 'setAlarmHours': '<S2>:93' */
            /* '<S2>:93:1' blink_hours = uint8(1); */
            *Stopwatch_Y_blink_hours = 1U;
          } else {
            /* '<S2>:97:1' sf_internal_predicateOutput = ... */
            /* '<S2>:97:1' (bminus) && (alarm_hours == 0); */
            if ((Stopwatch_DW->sfEvent == Stopwatch_event_bminus) &&
                (Stopwatch_DW->alarm_hours == 0)) {
              /* Transition: '<S2>:97' */
              /* '<S2>:97:1' alarm_hours = uint8(23) */
              Stopwatch_DW->alarm_hours = 23U;

              /* Exit 'setAlarmHours': '<S2>:93' */
              /* '<S2>:93:1' blink_hours = uint8(0); */
              Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmHours;

              /* Entry 'setAlarmHours': '<S2>:93' */
              /* '<S2>:93:1' blink_hours = uint8(1); */
              *Stopwatch_Y_blink_hours = 1U;
            } else {
              /* '<S2>:103:1' sf_internal_predicateOutput = ... */
              /* '<S2>:103:1' bminus; */
              switch (Stopwatch_DW->sfEvent) {
               case Stopwatch_event_bminus:
                /* Transition: '<S2>:103' */
                /* '<S2>:103:1' alarm_hours = alarm_hours - 1 */
                qY = Stopwatch_DW->alarm_hours - /*MW:OvSatOk*/ 1U;
                if (qY > Stopwatch_DW->alarm_hours) {
                  qY = 0U;
                }

                Stopwatch_DW->alarm_hours = (uint8_T)qY;

                /* Exit 'setAlarmHours': '<S2>:93' */
                /* '<S2>:93:1' blink_hours = uint8(0); */
                Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmHours;

                /* Entry 'setAlarmHours': '<S2>:93' */
                /* '<S2>:93:1' blink_hours = uint8(1); */
                *Stopwatch_Y_blink_hours = 1U;
                break;

               case Stopwatch_event_alarm:
                /* '<S2>:101:1' sf_internal_predicateOutput = ... */
                /* '<S2>:101:1' alarm; */
                /* Transition: '<S2>:101' */
                /* Exit 'setAlarmHours': '<S2>:93' */
                /* '<S2>:93:1' blink_hours = uint8(0); */
                *Stopwatch_Y_blink_hours = 0U;
                Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmMinutes;

                /* Entry 'setAlarmMinutes': '<S2>:99' */
                /* '<S2>:99:1' blink_minutes = uint8(1); */
                *Stopwatch_Y_blink_minutes = 1U;
                break;
              }
            }
          }
        } else {
          /* During 'setAlarmMinutes': '<S2>:99' */
          /* '<S2>:100:1' sf_internal_predicateOutput = ... */
          /* '<S2>:100:1' bplus; */
          if (Stopwatch_DW->sfEvent == Stopwatch_event_bplus) {
            /* Transition: '<S2>:100' */
            /* '<S2>:100:1' alarm_minutes = mod(alarm_minutes + 1, 60) */
            tmp = (int32_T)(Stopwatch_DW->alarm_minutes + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            Stopwatch_DW->alarm_minutes = (uint8_T)((uint32_T)(uint8_T)tmp -
              (uint8_T)((uint8_T)tmp / 60U * 60U));

            /* Exit 'setAlarmMinutes': '<S2>:99' */
            /* '<S2>:99:1' blink_minutes = uint8(0); */
            Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmMinutes;

            /* Entry 'setAlarmMinutes': '<S2>:99' */
            /* '<S2>:99:1' blink_minutes = uint8(1); */
            *Stopwatch_Y_blink_minutes = 1U;
          } else {
            /* '<S2>:95:1' sf_internal_predicateOutput = ... */
            /* '<S2>:95:1' (bminus) && (alarm_minutes == 0); */
            if ((Stopwatch_DW->sfEvent == Stopwatch_event_bminus) &&
                (Stopwatch_DW->alarm_minutes == 0)) {
              /* Transition: '<S2>:95' */
              /* '<S2>:95:1' alarm_minutes = uint8(59) */
              Stopwatch_DW->alarm_minutes = 59U;

              /* Exit 'setAlarmMinutes': '<S2>:99' */
              /* '<S2>:99:1' blink_minutes = uint8(0); */
              Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmMinutes;

              /* Entry 'setAlarmMinutes': '<S2>:99' */
              /* '<S2>:99:1' blink_minutes = uint8(1); */
              *Stopwatch_Y_blink_minutes = 1U;
            } else {
              /* '<S2>:94:1' sf_internal_predicateOutput = ... */
              /* '<S2>:94:1' bminus; */
              switch (Stopwatch_DW->sfEvent) {
               case Stopwatch_event_bminus:
                /* Transition: '<S2>:94' */
                /* '<S2>:94:1' alarm_minutes = alarm_minutes - 1 */
                qY = Stopwatch_DW->alarm_minutes - /*MW:OvSatOk*/ 1U;
                if (qY > Stopwatch_DW->alarm_minutes) {
                  qY = 0U;
                }

                Stopwatch_DW->alarm_minutes = (uint8_T)qY;

                /* Exit 'setAlarmMinutes': '<S2>:99' */
                /* '<S2>:99:1' blink_minutes = uint8(0); */
                Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmMinutes;

                /* Entry 'setAlarmMinutes': '<S2>:99' */
                /* '<S2>:99:1' blink_minutes = uint8(1); */
                *Stopwatch_Y_blink_minutes = 1U;
                break;

               case Stopwatch_event_alarm:
                /* '<S2>:102:1' sf_internal_predicateOutput = ... */
                /* '<S2>:102:1' alarm; */
                /* Transition: '<S2>:102' */
                /* Exit 'setAlarmMinutes': '<S2>:99' */
                /* '<S2>:99:1' blink_minutes = uint8(0); */
                *Stopwatch_Y_blink_minutes = 0U;
                Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmHours;

                /* Entry 'setAlarmHours': '<S2>:93' */
                /* '<S2>:93:1' blink_hours = uint8(1); */
                *Stopwatch_Y_blink_hours = 1U;
                break;
              }
            }
          }
        }
        break;
      }
      break;

     case Stopwatch_IN_stopwatchmode:
      Stopwatch_stopwatchmode(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_DW);
      break;

     case Stopwatch_IN_timemode:
      Stopwatch_timemode(Stopwatch_Y_hours, Stopwatch_Y_minutes,
                         Stopwatch_Y_seconds, Stopwatch_Y_tenths,
                         Stopwatch_Y_mode, Stopwatch_Y_blink_hours, Stopwatch_DW);
      break;

     default:
      /* During 'timesetmode': '<S2>:5' */
      /* '<S2>:35:1' sf_internal_predicateOutput = ... */
      /* '<S2>:35:1' alarm; */
      switch (Stopwatch_DW->sfEvent) {
       case Stopwatch_event_alarm:
        /* Transition: '<S2>:35' */
        /* Exit Internal 'timesetmode': '<S2>:5' */
        switch (Stopwatch_DW->is_timesetmode) {
         case Stopwatch_IN_setHours:
          /* Exit 'setHours': '<S2>:71' */
          /* '<S2>:71:1' blink_hours = uint8(0); */
          *Stopwatch_Y_blink_hours = 0U;
          Stopwatch_DW->is_timesetmode = Stopwatch_IN_NO_ACTIVE_CHILD;
          break;

         case Stopwatch_IN_setMinutes:
          /* Exit 'setMinutes': '<S2>:78' */
          /* '<S2>:78:1' blink_minutes = uint8(0); */
          *Stopwatch_Y_blink_minutes = 0U;
          Stopwatch_DW->is_timesetmode = Stopwatch_IN_NO_ACTIVE_CHILD;
          break;
        }

        /* Exit 'timesetmode': '<S2>:5' */
        /* '<S2>:5:2' hours = dhours; */
        Stopwatch_DW->hours = *Stopwatch_Y_hours;

        /* '<S2>:5:2' minutes = dminutes; */
        Stopwatch_DW->minutes = *Stopwatch_Y_minutes;
        Stopwatch_DW->is_Control = Stopwatch_IN_alarmmode;

        /* Entry 'alarmmode': '<S2>:6' */
        /* '<S2>:6:1' dmode = uint8(2); */
        *Stopwatch_Y_mode = 2U;

        /* '<S2>:6:1' dhours = alarm_hours; */
        *Stopwatch_Y_hours = Stopwatch_DW->alarm_hours;

        /* '<S2>:6:2' dminutes = alarm_minutes; */
        *Stopwatch_Y_minutes = Stopwatch_DW->alarm_minutes;

        /* Entry Internal 'alarmmode': '<S2>:6' */
        /* Transition: '<S2>:96' */
        Stopwatch_DW->is_alarmmode = Stopwatch_IN_setAlarmHours;

        /* Entry 'setAlarmHours': '<S2>:93' */
        /* '<S2>:93:1' blink_hours = uint8(1); */
        *Stopwatch_Y_blink_hours = 1U;
        break;

       case Stopwatch_event_stopwatch:
        /* '<S2>:37:1' sf_internal_predicateOutput = ... */
        /* '<S2>:37:1' stopwatch; */
        /* Transition: '<S2>:37' */
        /* Exit Internal 'timesetmode': '<S2>:5' */
        switch (Stopwatch_DW->is_timesetmode) {
         case Stopwatch_IN_setHours:
          /* Exit 'setHours': '<S2>:71' */
          /* '<S2>:71:1' blink_hours = uint8(0); */
          *Stopwatch_Y_blink_hours = 0U;
          Stopwatch_DW->is_timesetmode = Stopwatch_IN_NO_ACTIVE_CHILD;
          break;

         case Stopwatch_IN_setMinutes:
          /* Exit 'setMinutes': '<S2>:78' */
          /* '<S2>:78:1' blink_minutes = uint8(0); */
          *Stopwatch_Y_blink_minutes = 0U;
          Stopwatch_DW->is_timesetmode = Stopwatch_IN_NO_ACTIVE_CHILD;
          break;
        }

        /* Exit 'timesetmode': '<S2>:5' */
        /* '<S2>:5:2' hours = dhours; */
        Stopwatch_DW->hours = *Stopwatch_Y_hours;

        /* '<S2>:5:2' minutes = dminutes; */
        Stopwatch_DW->minutes = *Stopwatch_Y_minutes;
        Stopwatch_DW->is_Control = Stopwatch_IN_stopwatchmode;

        /* Entry 'stopwatchmode': '<S2>:7' */
        /* '<S2>:7:1' dmode = uint8(3); */
        *Stopwatch_Y_mode = 3U;

        /* Entry Internal 'stopwatchmode': '<S2>:7' */
        /* Transition: '<S2>:135' */
        Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_stopwatchOff;

        /* Entry 'stopwatchOff': '<S2>:133' */
        /* '<S2>:133:1' s_hours = uint8(0); */
        Stopwatch_DW->s_hours = 0U;

        /* '<S2>:133:1' s_minutes = uint8(0); */
        Stopwatch_DW->s_minutes = 0U;

        /* '<S2>:133:2' s_seconds = uint8(0); */
        Stopwatch_DW->s_seconds = 0U;

        /* '<S2>:133:2' s_tenths = uint8(0); */
        Stopwatch_DW->s_tenths = 0U;

        /* '<S2>:133:2' dtenths = s_tenths; */
        *Stopwatch_Y_tenths = Stopwatch_DW->s_tenths;

        /* '<S2>:133:2' dseconds = s_seconds; */
        *Stopwatch_Y_seconds = Stopwatch_DW->s_seconds;

        /* '<S2>:133:2' dminutes = s_minutes; */
        *Stopwatch_Y_minutes = Stopwatch_DW->s_minutes;

        /* '<S2>:133:2' dhours = s_hours; */
        *Stopwatch_Y_hours = Stopwatch_DW->s_hours;
        break;

       default:
        if (Stopwatch_DW->is_timesetmode == Stopwatch_IN_setHours) {
          /* During 'setHours': '<S2>:71' */
          /* '<S2>:75:1' sf_internal_predicateOutput = ... */
          /* '<S2>:75:1' bplus; */
          if (Stopwatch_DW->sfEvent == Stopwatch_event_bplus) {
            /* Transition: '<S2>:75' */
            /* '<S2>:75:1' dhours = mod(dhours + 1, 24) */
            tmp = (int32_T)(*Stopwatch_Y_hours + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            *Stopwatch_Y_hours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
              ((uint8_T)tmp / 24U * 24U));

            /* Exit 'setHours': '<S2>:71' */
            /* '<S2>:71:1' blink_hours = uint8(0); */
            Stopwatch_DW->is_timesetmode = Stopwatch_IN_setHours;

            /* Entry 'setHours': '<S2>:71' */
            /* '<S2>:71:1' blink_hours = uint8(1); */
            *Stopwatch_Y_blink_hours = 1U;
          } else {
            /* '<S2>:76:1' sf_internal_predicateOutput = ... */
            /* '<S2>:76:1' (bminus) && (dhours == 0); */
            if ((Stopwatch_DW->sfEvent == Stopwatch_event_bminus) &&
                (*Stopwatch_Y_hours == 0)) {
              /* Transition: '<S2>:76' */
              /* '<S2>:76:1' dhours = uint8(23) */
              *Stopwatch_Y_hours = 23U;

              /* Exit 'setHours': '<S2>:71' */
              /* '<S2>:71:1' blink_hours = uint8(0); */
              Stopwatch_DW->is_timesetmode = Stopwatch_IN_setHours;

              /* Entry 'setHours': '<S2>:71' */
              /* '<S2>:71:1' blink_hours = uint8(1); */
              *Stopwatch_Y_blink_hours = 1U;
            } else {
              /* '<S2>:90:1' sf_internal_predicateOutput = ... */
              /* '<S2>:90:1' bminus; */
              switch (Stopwatch_DW->sfEvent) {
               case Stopwatch_event_bminus:
                /* Transition: '<S2>:90' */
                /* '<S2>:90:1' dhours = dhours - 1 */
                qY = *Stopwatch_Y_hours - /*MW:OvSatOk*/ 1U;
                if (qY > *Stopwatch_Y_hours) {
                  qY = 0U;
                }

                *Stopwatch_Y_hours = (uint8_T)qY;

                /* Exit 'setHours': '<S2>:71' */
                /* '<S2>:71:1' blink_hours = uint8(0); */
                Stopwatch_DW->is_timesetmode = Stopwatch_IN_setHours;

                /* Entry 'setHours': '<S2>:71' */
                /* '<S2>:71:1' blink_hours = uint8(1); */
                *Stopwatch_Y_blink_hours = 1U;
                break;

               case Stopwatch_event_timeset:
                /* '<S2>:82:1' sf_internal_predicateOutput = ... */
                /* '<S2>:82:1' timeset; */
                /* Transition: '<S2>:82' */
                /* Exit 'setHours': '<S2>:71' */
                /* '<S2>:71:1' blink_hours = uint8(0); */
                *Stopwatch_Y_blink_hours = 0U;
                Stopwatch_DW->is_timesetmode = Stopwatch_IN_setMinutes;

                /* Entry 'setMinutes': '<S2>:78' */
                /* '<S2>:78:1' blink_minutes = uint8(1); */
                *Stopwatch_Y_blink_minutes = 1U;
                break;
              }
            }
          }
        } else {
          /* During 'setMinutes': '<S2>:78' */
          /* '<S2>:80:1' sf_internal_predicateOutput = ... */
          /* '<S2>:80:1' bplus; */
          if (Stopwatch_DW->sfEvent == Stopwatch_event_bplus) {
            /* Transition: '<S2>:80' */
            /* '<S2>:80:1' dminutes = mod(dminutes + 1, 60) */
            tmp = (int32_T)(*Stopwatch_Y_minutes + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            *Stopwatch_Y_minutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
              ((uint8_T)tmp / 60U * 60U));

            /* Exit 'setMinutes': '<S2>:78' */
            /* '<S2>:78:1' blink_minutes = uint8(0); */
            Stopwatch_DW->is_timesetmode = Stopwatch_IN_setMinutes;

            /* Entry 'setMinutes': '<S2>:78' */
            /* '<S2>:78:1' blink_minutes = uint8(1); */
            *Stopwatch_Y_blink_minutes = 1U;
          } else {
            /* '<S2>:91:1' sf_internal_predicateOutput = ... */
            /* '<S2>:91:1' (bminus) && (dminutes == 0); */
            if ((Stopwatch_DW->sfEvent == Stopwatch_event_bminus) &&
                (*Stopwatch_Y_minutes == 0)) {
              /* Transition: '<S2>:91' */
              /* '<S2>:91:1' dminutes = uint8(59) */
              *Stopwatch_Y_minutes = 59U;

              /* Exit 'setMinutes': '<S2>:78' */
              /* '<S2>:78:1' blink_minutes = uint8(0); */
              Stopwatch_DW->is_timesetmode = Stopwatch_IN_setMinutes;

              /* Entry 'setMinutes': '<S2>:78' */
              /* '<S2>:78:1' blink_minutes = uint8(1); */
              *Stopwatch_Y_blink_minutes = 1U;
            } else {
              /* '<S2>:92:1' sf_internal_predicateOutput = ... */
              /* '<S2>:92:1' bminus; */
              switch (Stopwatch_DW->sfEvent) {
               case Stopwatch_event_bminus:
                /* Transition: '<S2>:92' */
                /* '<S2>:92:1' dminutes = dminutes - 1 */
                qY = *Stopwatch_Y_minutes - /*MW:OvSatOk*/ 1U;
                if (qY > *Stopwatch_Y_minutes) {
                  qY = 0U;
                }

                *Stopwatch_Y_minutes = (uint8_T)qY;

                /* Exit 'setMinutes': '<S2>:78' */
                /* '<S2>:78:1' blink_minutes = uint8(0); */
                Stopwatch_DW->is_timesetmode = Stopwatch_IN_setMinutes;

                /* Entry 'setMinutes': '<S2>:78' */
                /* '<S2>:78:1' blink_minutes = uint8(1); */
                *Stopwatch_Y_blink_minutes = 1U;
                break;

               case Stopwatch_event_timeset:
                /* '<S2>:81:1' sf_internal_predicateOutput = ... */
                /* '<S2>:81:1' timeset; */
                /* Transition: '<S2>:81' */
                /* Exit 'setMinutes': '<S2>:78' */
                /* '<S2>:78:1' blink_minutes = uint8(0); */
                *Stopwatch_Y_blink_minutes = 0U;
                Stopwatch_DW->is_timesetmode = Stopwatch_IN_setHours;

                /* Entry 'setHours': '<S2>:71' */
                /* '<S2>:71:1' blink_hours = uint8(1); */
                *Stopwatch_Y_blink_hours = 1U;
                break;
              }
            }
          }
        }
        break;
      }
      break;
    }
  }
}

/* Function for Chart: '<S1>/Stopwatch' */
static void Stopwatc_chartstep_c3_Stopwatch(uint8_T *Stopwatch_Y_hours, uint8_T *
  Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T *Stopwatch_Y_tenths,
  uint8_T *Stopwatch_Y_mode, uint8_T *Stopwatch_Y_blink_hours, uint8_T
  *Stopwatch_Y_blink_minutes, uint8_T *Stopwatch_Y_is_alarm_active, uint8_T
  *Stopwatch_Y_alarm_ringing, DW_Stopwatch_T *Stopwatch_DW)
{
  int32_T tmp;

  /* During: Stopwatch/Stopwatch */
  Stopwatch_Control(Stopwatch_Y_hours, Stopwatch_Y_minutes, Stopwatch_Y_seconds,
                    Stopwatch_Y_tenths, Stopwatch_Y_mode,
                    Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
                    Stopwatch_DW);

  /* During 'Timecount': '<S2>:2' */
  /* '<S2>:175:1' sf_internal_predicateOutput = ... */
  /* '<S2>:175:1' timer_tick; */
  if (Stopwatch_DW->sfEvent == Stopwatch_event_timer_tick) {
    /* Transition: '<S2>:175' */
    /* '<S2>:182:1' sf_internal_predicateOutput = ... */
    /* '<S2>:182:1' s_running == 1; */
    if (Stopwatch_DW->s_running == 1) {
      /* Transition: '<S2>:182' */
      /* Transition: '<S2>:202' */
      /* '<S2>:202:1' s_tenths = mod(s_tenths+1, 10) */
      tmp = (int32_T)(Stopwatch_DW->s_tenths + 1U);
      if ((uint32_T)tmp > 255U) {
        tmp = 255;
      }

      Stopwatch_DW->s_tenths = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
        ((uint8_T)tmp / 10U * 10U));

      /* '<S2>:198:1' sf_internal_predicateOutput = ... */
      /* '<S2>:198:1' s_tenths == 0; */
      if (Stopwatch_DW->s_tenths == 0) {
        /* Transition: '<S2>:198' */
        /* '<S2>:198:1' s_seconds = mod(s_seconds+1, 60) */
        tmp = (int32_T)(Stopwatch_DW->s_seconds + 1U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        Stopwatch_DW->s_seconds = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
          ((uint8_T)tmp / 60U * 60U));

        /* '<S2>:204:1' sf_internal_predicateOutput = ... */
        /* '<S2>:204:1' s_seconds == 0; */
        if (Stopwatch_DW->s_seconds == 0) {
          /* Transition: '<S2>:204' */
          /* '<S2>:204:1' s_minutes = mod(s_minutes+1, 60) */
          tmp = (int32_T)(Stopwatch_DW->s_minutes + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          Stopwatch_DW->s_minutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
            ((uint8_T)tmp / 60U * 60U));

          /* '<S2>:205:1' sf_internal_predicateOutput = ... */
          /* '<S2>:205:1' s_minutes == 0; */
          if (Stopwatch_DW->s_minutes == 0) {
            /* Transition: '<S2>:205' */
            /* '<S2>:205:1' s_hours = mod(s_hours+1, 24) */
            tmp = (int32_T)(Stopwatch_DW->s_hours + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            Stopwatch_DW->s_hours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
              ((uint8_T)tmp / 24U * 24U));

            /* Transition: '<S2>:219' */
          } else {
            /* Transition: '<S2>:220' */
          }

          /* Transition: '<S2>:217' */
        } else {
          /* Transition: '<S2>:221' */
        }

        /* Transition: '<S2>:216' */
      } else {
        /* Transition: '<S2>:215' */
      }

      /* Transition: '<S2>:214' */
    } else {
      /* Transition: '<S2>:177' */
    }

    /* Transition: '<S2>:67' */
    /* '<S2>:67:1' tenths = mod(tenths+1, 10) */
    tmp = (int32_T)(Stopwatch_DW->tenths + 1U);
    if ((uint32_T)tmp > 255U) {
      tmp = 255;
    }

    Stopwatch_DW->tenths = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)((uint8_T)
      tmp / 10U * 10U));

    /* '<S2>:68:1' sf_internal_predicateOutput = ... */
    /* '<S2>:68:1' tenths == 0; */
    if (Stopwatch_DW->tenths == 0) {
      /* Transition: '<S2>:68' */
      /* '<S2>:68:1' seconds = mod(seconds+1, 60) */
      tmp = (int32_T)(Stopwatch_DW->seconds + 1U);
      if ((uint32_T)tmp > 255U) {
        tmp = 255;
      }

      Stopwatch_DW->seconds = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
        ((uint8_T)tmp / 60U * 60U));

      /* '<S2>:69:1' sf_internal_predicateOutput = ... */
      /* '<S2>:69:1' seconds == 0; */
      if (Stopwatch_DW->seconds == 0) {
        /* Transition: '<S2>:69' */
        /* '<S2>:69:1' minutes = mod(minutes+1, 60) */
        tmp = (int32_T)(Stopwatch_DW->minutes + 1U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        Stopwatch_DW->minutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
          ((uint8_T)tmp / 60U * 60U));

        /* '<S2>:70:1' sf_internal_predicateOutput = ... */
        /* '<S2>:70:1' minutes == 0; */
        if (Stopwatch_DW->minutes == 0) {
          /* Transition: '<S2>:70' */
          /* '<S2>:70:1' hours = mod(hours+1, 24) */
          tmp = (int32_T)(Stopwatch_DW->hours + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          Stopwatch_DW->hours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
            ((uint8_T)tmp / 24U * 24U));

          /* Transition: '<S2>:231' */
        } else {
          /* Transition: '<S2>:230' */
        }
      } else {
        /* Transition: '<S2>:229' */
      }
    } else {
      /* Transition: '<S2>:228' */
    }
  }

  /* During 'Alarmmanage': '<S2>:3' */
  if (Stopwatch_DW->is_Alarmmanage == Stopwatch_IN_alarmOff) {
    /* During 'alarmOff': '<S2>:104' */
    /* '<S2>:117:1' sf_internal_predicateOutput = ... */
    /* '<S2>:117:1' alarm_switch; */
    if (Stopwatch_DW->sfEvent == Stopwatch_event_alarm_switch) {
      /* Transition: '<S2>:117' */
      Stopwatch_DW->is_Alarmmanage = Stopwatch_IN_alarmOn;

      /* Entry 'alarmOn': '<S2>:119' */
      /* '<S2>:119:1' is_alarm_active = uint8(1); */
      *Stopwatch_Y_is_alarm_active = 1U;

      /* Entry Internal 'alarmOn': '<S2>:119' */
      /* Transition: '<S2>:132' */
      /* '<S2>:130:1' sf_internal_predicateOutput = ... */
      /* '<S2>:130:1' alarm_hours == hours && alarm_minutes == minutes; */
      if ((Stopwatch_DW->alarm_hours == Stopwatch_DW->hours) &&
          (Stopwatch_DW->alarm_minutes == Stopwatch_DW->minutes)) {
        /* Transition: '<S2>:130' */
        Stopwatch_DW->is_alarmOn = Stopwatch_IN_ringing;

        /* Entry 'ringing': '<S2>:126' */
        /* '<S2>:126:1' alarm_ringing = uint8(1); */
        *Stopwatch_Y_alarm_ringing = 1U;
      } else {
        /* Transition: '<S2>:129' */
        Stopwatch_DW->is_alarmOn = Stopwatch_IN_quiet;
      }
    }
  } else {
    /* During 'alarmOn': '<S2>:119' */
    /* '<S2>:128:1' sf_internal_predicateOutput = ... */
    /* '<S2>:128:1' alarm_switch; */
    if (Stopwatch_DW->sfEvent == Stopwatch_event_alarm_switch) {
      /* Transition: '<S2>:128' */
      /* Exit Internal 'alarmOn': '<S2>:119' */
      if (Stopwatch_DW->is_alarmOn == Stopwatch_IN_ringing) {
        /* Exit 'ringing': '<S2>:126' */
        /* '<S2>:126:1' alarm_ringing = uint8(0); */
        *Stopwatch_Y_alarm_ringing = 0U;
        Stopwatch_DW->is_alarmOn = Stopwatch_IN_NO_ACTIVE_CHILD;
      } else {
        Stopwatch_DW->is_alarmOn = Stopwatch_IN_NO_ACTIVE_CHILD;
      }

      Stopwatch_DW->is_Alarmmanage = Stopwatch_IN_alarmOff;

      /* Entry 'alarmOff': '<S2>:104' */
      /* '<S2>:104:1' is_alarm_active = uint8(0); */
      *Stopwatch_Y_is_alarm_active = 0U;
    } else {
      switch (Stopwatch_DW->is_alarmOn) {
       case Stopwatch_IN_quiet:
        /* During 'quiet': '<S2>:120' */
        /* '<S2>:123:1' sf_internal_predicateOutput = ... */
        /* '<S2>:123:1' (timer_tick) && (alarm_hours == hours && alarm_minutes == minutes); */
        if ((Stopwatch_DW->sfEvent == Stopwatch_event_timer_tick) &&
            (Stopwatch_DW->alarm_hours == Stopwatch_DW->hours) &&
            (Stopwatch_DW->alarm_minutes == Stopwatch_DW->minutes)) {
          /* Transition: '<S2>:123' */
          Stopwatch_DW->is_alarmOn = Stopwatch_IN_ringing;

          /* Entry 'ringing': '<S2>:126' */
          /* '<S2>:126:1' alarm_ringing = uint8(1); */
          *Stopwatch_Y_alarm_ringing = 1U;
        }
        break;

       case Stopwatch_IN_ringing:
        /* During 'ringing': '<S2>:126' */
        /* '<S2>:233:1' sf_internal_predicateOutput = ... */
        /* '<S2>:233:1' alarm; */
        if (Stopwatch_DW->sfEvent == Stopwatch_event_alarm) {
          /* Transition: '<S2>:233' */
          /* Exit 'ringing': '<S2>:126' */
          /* '<S2>:126:1' alarm_ringing = uint8(0); */
          *Stopwatch_Y_alarm_ringing = 0U;
          Stopwatch_DW->is_alarmOn = Stop_IN_waiting_next_activation;
        } else {
          /* '<S2>:122:1' sf_internal_predicateOutput = ... */
          /* '<S2>:122:1' (timer_tick) && (alarm_hours ~= hours || alarm_minutes ~= minutes); */
          if ((Stopwatch_DW->sfEvent == Stopwatch_event_timer_tick) &&
              ((Stopwatch_DW->alarm_hours != Stopwatch_DW->hours) ||
               (Stopwatch_DW->alarm_minutes != Stopwatch_DW->minutes))) {
            /* Transition: '<S2>:122' */
            /* Exit 'ringing': '<S2>:126' */
            /* '<S2>:126:1' alarm_ringing = uint8(0); */
            *Stopwatch_Y_alarm_ringing = 0U;
            Stopwatch_DW->is_alarmOn = Stopwatch_IN_quiet;
          }
        }
        break;

       default:
        /* During 'waiting_next_activation': '<S2>:234' */
        /* '<S2>:235:1' sf_internal_predicateOutput = ... */
        /* '<S2>:235:1' (timer_tick) && (alarm_hours ~= hours || alarm_minutes ~= minutes); */
        if ((Stopwatch_DW->sfEvent == Stopwatch_event_timer_tick) &&
            ((Stopwatch_DW->alarm_hours != Stopwatch_DW->hours) ||
             (Stopwatch_DW->alarm_minutes != Stopwatch_DW->minutes))) {
          /* Transition: '<S2>:235' */
          Stopwatch_DW->is_alarmOn = Stopwatch_IN_quiet;
        }
        break;
      }
    }
  }
}

/* Model step function */
void Stopwatch_step(RT_MODEL_Stopwatch_T *const Stopwatch_M, boolean_T
                    Stopwatch_U_timer_tick, boolean_T Stopwatch_U_plus,
                    boolean_T Stopwatch_U_minus, boolean_T Stopwatch_U_time,
                    boolean_T Stopwatch_U_timeset, boolean_T Stopwatch_U_alarm,
                    boolean_T Stopwatch_U_stopwatch, boolean_T
                    Stopwatch_U_alarm_switch, uint8_T *Stopwatch_Y_hours,
                    uint8_T *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds,
                    uint8_T *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode,
                    uint8_T *Stopwatch_Y_blink_hours, uint8_T
                    *Stopwatch_Y_blink_minutes, uint8_T
                    *Stopwatch_Y_is_alarm_active, uint8_T
                    *Stopwatch_Y_alarm_ringing)
{
  DW_Stopwatch_T *Stopwatch_DW = ((DW_Stopwatch_T *) Stopwatch_M->dwork);
  PrevZCX_Stopwatch_T *Stopwatch_PrevZCX = ((PrevZCX_Stopwatch_T *)
    Stopwatch_M->prevZCSigState);
  boolean_T zcEvent[8];
  boolean_T tmp;
  int32_T i;

  /* Chart: '<S1>/Stopwatch' incorporates:
   *  TriggerPort: '<S2>/input events'
   */
  /* Inport: '<Root>/timer_tick' */
  zcEvent[0] = (((Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[0] == POS_ZCSIG) !=
                 (int32_T)Stopwatch_U_timer_tick) &&
                (Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[0] != UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/plus' */
  zcEvent[1] = (((Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[1] == POS_ZCSIG) !=
                 (int32_T)Stopwatch_U_plus) &&
                (Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[1] != UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/minus' */
  zcEvent[2] = (((Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[2] == POS_ZCSIG) !=
                 (int32_T)Stopwatch_U_minus) &&
                (Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[2] != UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/time' */
  zcEvent[3] = (((Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[3] == POS_ZCSIG) !=
                 (int32_T)Stopwatch_U_time) &&
                (Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[3] != UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/timeset' */
  zcEvent[4] = (((Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[4] == POS_ZCSIG) !=
                 (int32_T)Stopwatch_U_timeset) &&
                (Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[4] != UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/alarm' */
  zcEvent[5] = (((Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[5] == POS_ZCSIG) !=
                 (int32_T)Stopwatch_U_alarm) &&
                (Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[5] != UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/stopwatch' */
  zcEvent[6] = (((Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[6] == POS_ZCSIG) !=
                 (int32_T)Stopwatch_U_stopwatch) &&
                (Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[6] != UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/alarm_switch' */
  zcEvent[7] = (((Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[7] == POS_ZCSIG) !=
                 (int32_T)Stopwatch_U_alarm_switch) &&
                (Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[7] != UNINITIALIZED_ZCSIG));
  tmp = false;
  for (i = 0; i < 8; i++) {
    tmp = (tmp || zcEvent[i]);
  }

  if (tmp) {
    /* Inport: '<Root>/timer_tick' */
    /* Gateway: Stopwatch/Stopwatch */
    if ((int8_T)(zcEvent[0] ? Stopwatch_U_timer_tick ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) != 0) {
      /* Event: '<S2>:23' */
      Stopwatch_DW->sfEvent = Stopwatch_event_timer_tick;
      Stopwatc_chartstep_c3_Stopwatch(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
        Stopwatch_Y_is_alarm_active, Stopwatch_Y_alarm_ringing, Stopwatch_DW);
    }

    /* Inport: '<Root>/plus' */
    if ((int8_T)(zcEvent[1] ? Stopwatch_U_plus ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S2>:9' */
      Stopwatch_DW->sfEvent = Stopwatch_event_bplus;
      Stopwatc_chartstep_c3_Stopwatch(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
        Stopwatch_Y_is_alarm_active, Stopwatch_Y_alarm_ringing, Stopwatch_DW);
    }

    /* Inport: '<Root>/minus' */
    if ((int8_T)(zcEvent[2] ? Stopwatch_U_minus ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S2>:10' */
      Stopwatch_DW->sfEvent = Stopwatch_event_bminus;
      Stopwatc_chartstep_c3_Stopwatch(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
        Stopwatch_Y_is_alarm_active, Stopwatch_Y_alarm_ringing, Stopwatch_DW);
    }

    /* Inport: '<Root>/time' */
    if ((int8_T)(zcEvent[3] ? Stopwatch_U_time ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S2>:15' */
      Stopwatch_DW->sfEvent = Stopwatch_event_time;
      Stopwatc_chartstep_c3_Stopwatch(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
        Stopwatch_Y_is_alarm_active, Stopwatch_Y_alarm_ringing, Stopwatch_DW);
    }

    /* Inport: '<Root>/timeset' */
    if ((int8_T)(zcEvent[4] ? Stopwatch_U_timeset ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S2>:20' */
      Stopwatch_DW->sfEvent = Stopwatch_event_timeset;
      Stopwatc_chartstep_c3_Stopwatch(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
        Stopwatch_Y_is_alarm_active, Stopwatch_Y_alarm_ringing, Stopwatch_DW);
    }

    /* Inport: '<Root>/alarm' */
    if ((int8_T)(zcEvent[5] ? Stopwatch_U_alarm ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S2>:21' */
      Stopwatch_DW->sfEvent = Stopwatch_event_alarm;
      Stopwatc_chartstep_c3_Stopwatch(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
        Stopwatch_Y_is_alarm_active, Stopwatch_Y_alarm_ringing, Stopwatch_DW);
    }

    /* Inport: '<Root>/stopwatch' */
    if ((int8_T)(zcEvent[6] ? Stopwatch_U_stopwatch ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S2>:22' */
      Stopwatch_DW->sfEvent = Stopwatch_event_stopwatch;
      Stopwatc_chartstep_c3_Stopwatch(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
        Stopwatch_Y_is_alarm_active, Stopwatch_Y_alarm_ringing, Stopwatch_DW);
    }

    /* Inport: '<Root>/alarm_switch' */
    if ((int8_T)(zcEvent[7] ? Stopwatch_U_alarm_switch ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S2>:107' */
      Stopwatch_DW->sfEvent = Stopwatch_event_alarm_switch;
      Stopwatc_chartstep_c3_Stopwatch(Stopwatch_Y_hours, Stopwatch_Y_minutes,
        Stopwatch_Y_seconds, Stopwatch_Y_tenths, Stopwatch_Y_mode,
        Stopwatch_Y_blink_hours, Stopwatch_Y_blink_minutes,
        Stopwatch_Y_is_alarm_active, Stopwatch_Y_alarm_ringing, Stopwatch_DW);
    }
  }

  /* Inport: '<Root>/timer_tick' */
  Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[0] = Stopwatch_U_timer_tick;

  /* Inport: '<Root>/plus' */
  Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[1] = Stopwatch_U_plus;

  /* Inport: '<Root>/minus' */
  Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[2] = Stopwatch_U_minus;

  /* Inport: '<Root>/time' */
  Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[3] = Stopwatch_U_time;

  /* Inport: '<Root>/timeset' */
  Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[4] = Stopwatch_U_timeset;

  /* Inport: '<Root>/alarm' */
  Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[5] = Stopwatch_U_alarm;

  /* Inport: '<Root>/stopwatch' */
  Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[6] = Stopwatch_U_stopwatch;

  /* Inport: '<Root>/alarm_switch' */
  Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[7] = Stopwatch_U_alarm_switch;
}

/* Model initialize function */
void Stopwatch_initialize(RT_MODEL_Stopwatch_T *const Stopwatch_M, boolean_T
  *Stopwatch_U_timer_tick, boolean_T *Stopwatch_U_plus, boolean_T
  *Stopwatch_U_minus, boolean_T *Stopwatch_U_time, boolean_T
  *Stopwatch_U_timeset, boolean_T *Stopwatch_U_alarm, boolean_T
  *Stopwatch_U_stopwatch, boolean_T *Stopwatch_U_alarm_switch, uint8_T
  *Stopwatch_Y_hours, uint8_T *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds,
  uint8_T *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, uint8_T *Stopwatch_Y_blink_minutes, uint8_T
  *Stopwatch_Y_is_alarm_active, uint8_T *Stopwatch_Y_alarm_ringing)
{
  DW_Stopwatch_T *Stopwatch_DW = ((DW_Stopwatch_T *) Stopwatch_M->dwork);
  PrevZCX_Stopwatch_T *Stopwatch_PrevZCX = ((PrevZCX_Stopwatch_T *)
    Stopwatch_M->prevZCSigState);

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)Stopwatch_DW, 0,
                sizeof(DW_Stopwatch_T));

  /* external inputs */
  *Stopwatch_U_timer_tick = false;
  *Stopwatch_U_plus = false;
  *Stopwatch_U_minus = false;
  *Stopwatch_U_time = false;
  *Stopwatch_U_timeset = false;
  *Stopwatch_U_alarm = false;
  *Stopwatch_U_stopwatch = false;
  *Stopwatch_U_alarm_switch = false;

  /* external outputs */
  (*Stopwatch_Y_hours) = 0U;
  (*Stopwatch_Y_minutes) = 0U;
  (*Stopwatch_Y_seconds) = 0U;
  (*Stopwatch_Y_tenths) = 0U;
  (*Stopwatch_Y_mode) = 0U;
  (*Stopwatch_Y_blink_hours) = 0U;
  (*Stopwatch_Y_blink_minutes) = 0U;
  (*Stopwatch_Y_is_alarm_active) = 0U;
  (*Stopwatch_Y_alarm_ringing) = 0U;

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Stopwatch_PrevZCX->Stopwatch_Trig_ZCE[i] = UNINITIALIZED_ZCSIG;
    }

    /* SystemInitialize for Chart: '<S1>/Stopwatch' */
    Stopwatch_DW->is_alarmOn = Stopwatch_IN_NO_ACTIVE_CHILD;
    Stopwatch_DW->is_alarmmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    Stopwatch_DW->is_stopwatchmode = Stopwatch_IN_NO_ACTIVE_CHILD;
    Stopwatch_DW->is_stopwatchRunning = Stopwatch_IN_NO_ACTIVE_CHILD;
    Stopwatch_DW->is_timesetmode = Stopwatch_IN_NO_ACTIVE_CHILD;

    /* SystemInitialize for Outport: '<Root>/blink_hours' incorporates:
     *  SystemInitialize for Chart: '<S1>/Stopwatch'
     */
    /* Entry: Stopwatch/Stopwatch */
    /* Entry Internal: Stopwatch/Stopwatch */
    /* Entry 'Control': '<S2>:1' */
    /* '<S2>:1:1' blink_hours = uint8(0); */
    *Stopwatch_Y_blink_hours = 0U;

    /* SystemInitialize for Outport: '<Root>/blink_minutes' incorporates:
     *  SystemInitialize for Chart: '<S1>/Stopwatch'
     */
    /* '<S2>:1:1' blink_minutes = uint8(0); */
    *Stopwatch_Y_blink_minutes = 0U;

    /* SystemInitialize for Chart: '<S1>/Stopwatch' */
    /* Entry Internal 'Control': '<S2>:1' */
    /* Transition: '<S2>:61' */
    Stopwatch_DW->is_Control = Stopwatch_IN_timemode;

    /* SystemInitialize for Outport: '<Root>/mode' incorporates:
     *  SystemInitialize for Chart: '<S1>/Stopwatch'
     */
    /* Entry 'timemode': '<S2>:60' */
    /* '<S2>:60:1' dmode = uint8(0); */
    *Stopwatch_Y_mode = 0U;

    /* SystemInitialize for Chart: '<S1>/Stopwatch' */
    /* Entry 'Timecount': '<S2>:2' */
    /* '<S2>:2:1' hours = uint8(0); */
    Stopwatch_DW->hours = 0U;

    /* '<S2>:2:1' minutes = uint8(0); */
    Stopwatch_DW->minutes = 0U;

    /* '<S2>:2:2' seconds = uint8(0); */
    Stopwatch_DW->seconds = 0U;

    /* '<S2>:2:2' tenths = uint8(0); */
    Stopwatch_DW->tenths = 0U;

    /* '<S2>:2:2' s_hours = uint8(0); */
    Stopwatch_DW->s_hours = 0U;

    /* '<S2>:2:2' s_minutes = uint8(0); */
    Stopwatch_DW->s_minutes = 0U;

    /* '<S2>:2:2' s_seconds = uint8(0); */
    Stopwatch_DW->s_seconds = 0U;

    /* '<S2>:2:2' s_tenths = uint8(0); */
    Stopwatch_DW->s_tenths = 0U;

    /* '<S2>:2:2' s_running = uint8(0); */
    Stopwatch_DW->s_running = 0U;

    /* Entry 'Alarmmanage': '<S2>:3' */
    /* '<S2>:3:1' alarm_hours = uint8(0); */
    Stopwatch_DW->alarm_hours = 0U;

    /* '<S2>:3:1' alarm_minutes = uint8(0); */
    Stopwatch_DW->alarm_minutes = 0U;

    /* SystemInitialize for Outport: '<Root>/alarm_ringing' incorporates:
     *  SystemInitialize for Chart: '<S1>/Stopwatch'
     */
    /* '<S2>:3:2' is_alarm_active = uint8(0); */
    /* '<S2>:3:2' alarm_ringing = uint8(0); */
    *Stopwatch_Y_alarm_ringing = 0U;

    /* SystemInitialize for Chart: '<S1>/Stopwatch' */
    /* Entry Internal 'Alarmmanage': '<S2>:3' */
    /* Transition: '<S2>:105' */
    Stopwatch_DW->is_Alarmmanage = Stopwatch_IN_alarmOff;

    /* SystemInitialize for Outport: '<Root>/is_alarm_active' incorporates:
     *  SystemInitialize for Chart: '<S1>/Stopwatch'
     */
    /* Entry 'alarmOff': '<S2>:104' */
    /* '<S2>:104:1' is_alarm_active = uint8(0); */
    *Stopwatch_Y_is_alarm_active = 0U;
  }
}

/* Model terminate function */
void Stopwatch_terminate(RT_MODEL_Stopwatch_T *const Stopwatch_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(Stopwatch_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
