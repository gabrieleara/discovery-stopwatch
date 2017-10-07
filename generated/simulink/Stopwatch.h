/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Stopwatch.h
 *
 * Code generated for Simulink model 'Stopwatch'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Sat Oct  7 17:35:39 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Stopwatch_h_
#define RTW_HEADER_Stopwatch_h_
#include <string.h>
#ifndef Stopwatch_COMMON_INCLUDES_
# define Stopwatch_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* Stopwatch_COMMON_INCLUDES_ */

#include "Stopwatch_types.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  int32_T sfEvent;                     /* '<S1>/Stopwatch' */
  uint8_T is_Control;                  /* '<S1>/Stopwatch' */
  uint8_T is_timesetmode;              /* '<S1>/Stopwatch' */
  uint8_T is_alarmmode;                /* '<S1>/Stopwatch' */
  uint8_T is_stopwatchmode;            /* '<S1>/Stopwatch' */
  uint8_T is_stopwatchRunning;         /* '<S1>/Stopwatch' */
  uint8_T is_Alarmmanage;              /* '<S1>/Stopwatch' */
  uint8_T is_alarmOn;                  /* '<S1>/Stopwatch' */
  uint8_T hours;                       /* '<S1>/Stopwatch' */
  uint8_T minutes;                     /* '<S1>/Stopwatch' */
  uint8_T seconds;                     /* '<S1>/Stopwatch' */
  uint8_T tenths;                      /* '<S1>/Stopwatch' */
  uint8_T alarm_hours;                 /* '<S1>/Stopwatch' */
  uint8_T alarm_minutes;               /* '<S1>/Stopwatch' */
  uint8_T s_tenths;                    /* '<S1>/Stopwatch' */
  uint8_T s_seconds;                   /* '<S1>/Stopwatch' */
  uint8_T s_minutes;                   /* '<S1>/Stopwatch' */
  uint8_T s_hours;                     /* '<S1>/Stopwatch' */
  uint8_T s_running;                   /* '<S1>/Stopwatch' */
} DW_Stopwatch_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Stopwatch_Trig_ZCE[8];    /* '<S1>/Stopwatch' */
} PrevZCX_Stopwatch_T;

/* Real-time Model Data Structure */
struct tag_RTM_Stopwatch_T {
  const char_T * volatile errorStatus;
  PrevZCX_Stopwatch_T *prevZCSigState;
  DW_Stopwatch_T *dwork;
};

/* Model entry point functions */
extern void Stopwatch_initialize(RT_MODEL_Stopwatch_T *const Stopwatch_M,
  boolean_T *Stopwatch_U_timer_tick, boolean_T *Stopwatch_U_plus, boolean_T
  *Stopwatch_U_minus, boolean_T *Stopwatch_U_time, boolean_T
  *Stopwatch_U_timeset, boolean_T *Stopwatch_U_alarm, boolean_T
  *Stopwatch_U_stopwatch, boolean_T *Stopwatch_U_alarm_switch, uint8_T
  *Stopwatch_Y_hours, uint8_T *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds,
  uint8_T *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, uint8_T *Stopwatch_Y_blink_minutes, uint8_T
  *Stopwatch_Y_is_alarm_active, uint8_T *Stopwatch_Y_alarm_ringing);
extern void Stopwatch_step(RT_MODEL_Stopwatch_T *const Stopwatch_M, boolean_T
  Stopwatch_U_timer_tick, boolean_T Stopwatch_U_plus, boolean_T
  Stopwatch_U_minus, boolean_T Stopwatch_U_time, boolean_T Stopwatch_U_timeset,
  boolean_T Stopwatch_U_alarm, boolean_T Stopwatch_U_stopwatch, boolean_T
  Stopwatch_U_alarm_switch, uint8_T *Stopwatch_Y_hours, uint8_T
  *Stopwatch_Y_minutes, uint8_T *Stopwatch_Y_seconds, uint8_T
  *Stopwatch_Y_tenths, uint8_T *Stopwatch_Y_mode, uint8_T
  *Stopwatch_Y_blink_hours, uint8_T *Stopwatch_Y_blink_minutes, uint8_T
  *Stopwatch_Y_is_alarm_active, uint8_T *Stopwatch_Y_alarm_ringing);
extern void Stopwatch_terminate(RT_MODEL_Stopwatch_T *const Stopwatch_M);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('StopwatchAra2016/Stopwatch')    - opens subsystem StopwatchAra2016/Stopwatch
 * hilite_system('StopwatchAra2016/Stopwatch/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'StopwatchAra2016'
 * '<S1>'   : 'StopwatchAra2016/Stopwatch'
 * '<S2>'   : 'StopwatchAra2016/Stopwatch/Stopwatch'
 */
#endif                                 /* RTW_HEADER_Stopwatch_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
