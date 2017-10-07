/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

#include "ee.h"
#include "ee_irq.h"
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "stm32f4xx.h"

#include "res/pictures.h"

#include "screen/debug.h"

#include "touch/Widget.h"
#include "touch/WidgetConfig.h"
#include "touch/Touch.h"
#include "touch/Event.h"
#include "touch/STMPE811QTR.h"


#include "simulink/Stopwatch.h"

#include "UI_Handler.h"

#define FALSE 0
#define TRUE 1


// ---------------------------------------------------------- //
//                         Data                               //
//                      Definition                            //
// ---------------------------------------------------------- //

#define ARA_BUTTON_PLUS			0
#define ARA_BUTTON_MINUS		1
#define ARA_BUTTON_TIME			2
#define ARA_BUTTON_TIMESET		3
#define ARA_BUTTON_ALARM		4
#define ARA_BUTTON_STOPWATCH	5
#define ARA_BUTTON_SWITCH		6

#define ARA_BUTTON_NUM			7

RT_MODEL_Stopwatch_T Stopwatch_M;

char_T *errorStatus;

PrevZCX_Stopwatch_T prevZCSigState;
DW_Stopwatch_T dwork;

boolean_T timer_tick;
boolean_T buttons[7];
uint8_T time[4];
uint8_T mode;
uint8_T blink[2];
uint8_T is_alarm_active;
uint8_T is_alarm_ringing;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/*
 * TASK LCD
 */
TASK(TaskLCD)
{
	unsigned int px, py;
	TPoint p;
	if (GetTouch_SC_Async(&px, &py)) {
		p.x = px;
		p.y = py;
		OnTouch(MyWatchScr, &p);
	}
}


TASK(TaskClock)
{
	unsigned char i;
	static int oldmode=8;
	static unsigned char oh=99, om=99, os=99, ot=99;
	char tstr[3];

	// timer_tick = !timer_tick & 0x01;

	if (timer_tick==FALSE) timer_tick=TRUE; else timer_tick=FALSE;

	if (IsEvent(EVT_TIMEMODE)) buttons[ARA_BUTTON_TIME]=1;
	if (IsEvent(EVT_TIMESETMODE)) buttons[ARA_BUTTON_TIMESET]=1;
	if (IsEvent(EVT_ALARMMODE)) buttons[ARA_BUTTON_ALARM]=1;
	if (IsEvent(EVT_SWATCHMODE)) buttons[ARA_BUTTON_STOPWATCH]=1;
	if (IsEvent(EVT_PLUS)) buttons[ARA_BUTTON_PLUS]=1;
	if (IsEvent(EVT_MINUS)) buttons[ARA_BUTTON_MINUS]=1;
	if (IsEvent(EVT_SWITCH)) buttons[ARA_BUTTON_SWITCH]=1;

	Stopwatch_step(
		&Stopwatch_M,
		timer_tick,
		buttons[0],
		buttons[1],
		buttons[2],
		buttons[3],
		buttons[4],
		buttons[5],
		buttons[6],
		&time[0],
		&time[1],
		&time[2],
		&time[3],
		&mode,
		&blink[0],
		&blink[1],
		&is_alarm_active,
		&is_alarm_ringing);

	/* seconds = seconds+1; */

	ClearEvents();

	for (i=0;i < ARA_BUTTON_NUM; i++)
		buttons[i]=0;

	update_interface(mode, time, blink, is_alarm_active, is_alarm_ringing);
}

/*
 * MAIN TASK
 */
int main(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;

	SystemInit();
  /*Initializes Erika related stuffs*/
	EE_system_init();

	Stopwatch_M.prevZCSigState = &prevZCSigState;
	Stopwatch_M.dwork = &dwork;
	Stopwatch_M.errorStatus = &errorStatus;

  /* init state machine */
    Stopwatch_initialize(
		&Stopwatch_M,
		&timer_tick,
		buttons,
		buttons+1,
		buttons+2,
		buttons+3,
		buttons+4,
		buttons+5,
		buttons+6,
		time,
		time+1,
		time+2,
		time+3,
		&mode,
		blink,
		blink+1,
		&is_alarm_active,
		&is_alarm_ringing);

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	/* Initializes LCD and touchscreen */
	IOE_Config();
	/* Initialize the LCD */
	STM32f4_Discovery_LCD_Init();

	InitTouch(-0.09, 0.0656, -353, 10);

	/* Draw the background */
	init_interface();


	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmTaskLCD, 10, 50);
	SetRelAlarm(AlarmTaskClock, 10, 100);

  /* Forever loop: background activities (if any) should go here */
	for (;;) { 
	}

}


