/*
 * WidgetConfig.h
 *
 *  Created on: 22/ott/2015
 *      Author: admim
 */

#ifndef WIDGETCONFIG_H_
#define WIDGETCONFIG_H_

#define NUMWIDGETS 15

#define WID_BACKGROUND	0
#define WID_TIME		1
#define WID_TIMESET		2
#define WID_ALARM		3
#define WID_STOPWATCH	4
#define WID_PLUS		5
#define WID_MINUS		6
#define WID_SWITCH		7
#define WID_TIME_HOURS	8
#define WID_TIME_MINS	9
#define WID_TIME_SECS	10
#define WID_TIME_TENTHS	11
#define WID_SEP_HH_MM	12
#define WID_SEP_MM_SS	13
#define WID_SEP_SS_T	14

#define EVT_TIMEMODE	0x01
#define EVT_TIMESETMODE 0x02
#define EVT_ALARMMODE	0x04
#define EVT_SWATCHMODE	0x08
#define EVT_PLUS		0x10
#define EVT_MINUS		0x20
#define EVT_SWITCH		0x40

extern const Widget MyWatchScr[NUMWIDGETS];

#endif /* WIDGETCONFIG_H_ */
