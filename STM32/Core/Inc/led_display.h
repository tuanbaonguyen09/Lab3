/*
 * led_display.h
 *
 *  Created on: Oct 29, 2022
 *      Author: tuanb
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "global.h"

extern int state1;
extern int state2;

extern int red_timer;
extern int green_timer;
extern int yellow_timer;


extern int timer[3];
extern int count;
extern int count_ex;

extern int index_led;

void fsm_for_trafficled_normal(void);
void fsm_for_trafficled_normal_ex(void);

void update7SEG( int);
void display7SEG(int);
void get_count(void);

#endif /* INC_LED_DISPLAY_H_ */
