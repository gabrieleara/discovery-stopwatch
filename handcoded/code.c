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

#include "STMPE811QTR.h"
#include "pictures.h"
#include "Widget.h"
#include "WidgetConfig.h"
#include "Touch.h"
#include "Event.h"
#include "stopwatch.h"
#include "lcd_add.h"
#include "fonts.h"
#include "debug.h"
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
#define ARA_BUTTON_ALARM_SWITCH	6

#define ARA_BUTTON_NUM			7

#define ARA_TIME_HOURS			0
#define ARA_TIME_MINUTES		1
#define ARA_TIME_SECONDS		2
#define ARA_TIME_TENTHS			3

#define ARA_BLINK_HOURS			0
#define ARA_BLINK_MINUTES		1

#include "simple_types.h"

uint8_t time[4];
uint8_t mode;
uint8_t blink[2];
uint8_t is_alarm_active;
uint8_t is_alarm_ringing;

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
	static unsigned char oh=99, om=99, os=99;
	char tstr[3];

	// static unsigned char counter = 0;

	// timer_tick = !timer_tick & 0x01;

	event_t event = EVENT_TIMER_TICK;

	if (IsEvent(EVT_TIMEMODE)) event |= EVENT_TIME;
	if (IsEvent(EVT_TIMESETMODE)) event |= EVENT_TIMESET;
	if (IsEvent(EVT_ALARMMODE)) event |= EVENT_ALARM;
	if (IsEvent(EVT_SWATCHMODE)) event |= EVENT_STOPWATCH;
	if (IsEvent(EVT_PLUS)) event |= EVENT_BPLUS;
	if (IsEvent(EVT_MINUS)) event |= EVENT_BMINUS;
	if (IsEvent(EVT_SWITCH)) event |= EVENT_ALARM_SWITCH;

	stopwatch_step(
		event,
		&mode,
		&time[ARA_TIME_HOURS],
		&time[ARA_TIME_MINUTES],
		&time[ARA_TIME_SECONDS],
		&time[ARA_TIME_TENTHS],
		&blink[ARA_BLINK_HOURS],
		&blink[ARA_BLINK_MINUTES],
		&is_alarm_active,
		&is_alarm_ringing);

	/* seconds = seconds+1; */

	ClearEvents();

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

  /* init state machine */
	stopwatch_init(
		&mode,
		&time[ARA_TIME_HOURS],
		&time[ARA_TIME_MINUTES],
		&time[ARA_TIME_SECONDS],
		&time[ARA_TIME_TENTHS],
		&blink[ARA_BLINK_HOURS],
		&blink[ARA_BLINK_MINUTES],
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


