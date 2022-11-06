/*
 * input_processing.c
 *
 *  Created on: Oct 29, 2022
 *      Author: tuanb
 */
#include "input_processing.h"

enum ButtonState {MODE_NORMAL, MODE_SET_RED, MODE_SET_YELLOW, MODE_SET_GREEN};
enum ButtonState buttonState = MODE_NORMAL ;


void fsm_for_changer_duration(int status){
	switch (status){
		case 1:
			if(timer1_flag == 1){
				HAL_GPIO_TogglePin(GPIOA, RED1_Pin | RED2_Pin);
				HAL_GPIO_WritePin(GPIOA, GREEN2_Pin |GREEN1_Pin|YELLOW1_Pin|YELLOW2_Pin, GPIO_PIN_SET);
				setTimer1(500);
			}

			break;
		case 2:
			if(timer1_flag == 1){
				HAL_GPIO_TogglePin(GPIOA, YELLOW1_Pin | YELLOW2_Pin);
				HAL_GPIO_WritePin(GPIOA, GREEN2_Pin |GREEN1_Pin|RED1_Pin|RED2_Pin, GPIO_PIN_SET);
				setTimer1(500);
			}
			break;
		case 3:
			if(timer1_flag == 1){
				HAL_GPIO_TogglePin(GPIOA, GREEN1_Pin | GREEN2_Pin);
				HAL_GPIO_WritePin(GPIOA, RED2_Pin|RED1_Pin|YELLOW2_Pin|YELLOW1_Pin, GPIO_PIN_SET);
				setTimer1(500);
			}
			break;
	}
}
void fsm_for_input_processing (void){
	switch (buttonState){
		case MODE_NORMAL :
				fsm_for_trafficled_normal();
				fsm_for_trafficled_normal_ex();
				update7SEG(0);
			if(isButtonPressed(0)){
				HAL_GPIO_WritePin(GPIOA, RED1_Pin|YELLOW1_Pin|GREEN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, RED2_Pin|YELLOW2_Pin|GREEN2_Pin, GPIO_PIN_SET);
				buttonState = MODE_SET_RED;
				clearTimer0(); state1 = 0;
				clearTimer3(); state2 = 0;
			}
			break;
		case MODE_SET_RED :
			fsm_for_changer_duration(1);
			update7SEG(1);
			if(isButtonPressed(0)){
				buttonState = MODE_SET_YELLOW ;
			}
			if(isButtonPressed(1)){
				red_timer += 1;
				if(red_timer > 99) red_timer= 1;
			}
			if (isButtonPressed(2)){
				timer[0] = red_timer;
			}
			break;
		case MODE_SET_YELLOW :
			fsm_for_changer_duration(2);
			update7SEG(2);
			if(isButtonPressed(1)){
				yellow_timer += 1;
				if(yellow_timer > 99) yellow_timer = 1;
			}
			if (isButtonPressed(2)){
				timer[1] = yellow_timer;
			}
			if(isButtonPressed(0)){
				buttonState = MODE_SET_GREEN ;
			}
			break;
		case MODE_SET_GREEN :
			fsm_for_changer_duration(3);
			update7SEG(3);
			if(isButtonPressed(1)){
				green_timer += 1;
				if(green_timer > 99) green_timer= 1;
			}
			if (isButtonPressed(2)){
				timer[2] = green_timer;
			}
			if(isButtonPressed(0)){
				buttonState = MODE_NORMAL ;
			}
			break;
	}
}

