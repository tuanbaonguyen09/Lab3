/*
 * led_display.c
 *
 *  Created on: Oct 29, 2022
 *      Author: tuanb
 */

#include "input_reading.h"

int state1 = 0;
int state2 = 0;

int timer[3] = {5, 2, 3};

int red_timer = 5;
int yellow_timer = 2;
int green_timer = 3;

int count = 0;
int count_ex = 0;

int index_led = 0;

void display7SEG(int num){
	HAL_GPIO_WritePin (GPIOB,a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin, GPIO_PIN_SET) ;
	switch(num){
	case 0:
		HAL_GPIO_TogglePin (GPIOB,a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin) ;
		break;
	case 1:
		HAL_GPIO_TogglePin (GPIOB ,b_Pin|c_Pin) ;
		break;
	case 2:
		HAL_GPIO_TogglePin (GPIOB,a_Pin|b_Pin|g_Pin|d_Pin|e_Pin) ;
		break;
	case 3:
		HAL_GPIO_TogglePin (GPIOB,a_Pin|b_Pin|g_Pin|c_Pin|d_Pin) ;
		break;
	case 4:
		HAL_GPIO_TogglePin (GPIOB,f_Pin|g_Pin|b_Pin|c_Pin) ;
		break;
	case 5:
		HAL_GPIO_TogglePin (GPIOB,a_Pin|f_Pin|g_Pin|c_Pin|d_Pin) ;
		break;
	case 6 :
		HAL_GPIO_TogglePin (GPIOB,a_Pin|f_Pin|g_Pin|e_Pin|c_Pin|d_Pin) ;
		break;
	case 7 :
		HAL_GPIO_TogglePin (GPIOB ,a_Pin|b_Pin|c_Pin ) ;
		break;
	case 8:
		HAL_GPIO_TogglePin (GPIOB,a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin) ;
		break;
	case 9:
		HAL_GPIO_TogglePin (GPIOB,a_Pin|b_Pin|c_Pin|d_Pin|f_Pin|g_Pin) ;
		break;
	}
}

void update7SEG(int mode){
	switch(index_led){
	case 0:
		 HAL_GPIO_WritePin (en0_GPIO_Port,en0_Pin, GPIO_PIN_RESET ) ;
		 HAL_GPIO_WritePin (GPIOA,en1_Pin|en2_Pin|en3_Pin, SET) ;
		 switch(mode){
			 case 0:
				 display7SEG((count%100)/10);
				 break;
			 case 1:
				 display7SEG(0);
				 break;
			 case 2:
				 display7SEG(0);
				 break;
			 case 3:
				 display7SEG(0);
				 break;
		 }
		 if(timer2_flag == 1){
			 index_led = 1;
			 setTimer2(260);
		 }
		break ;
	case 1:
		 HAL_GPIO_WritePin (en1_GPIO_Port,en1_Pin, GPIO_PIN_RESET ) ;
		 HAL_GPIO_WritePin (GPIOA,en0_Pin|en2_Pin|en3_Pin, SET) ;
		 switch(mode){
			 case 0:
				 display7SEG(count%10);
				 break;
			 case 1:
				 display7SEG(2);
				 break;
			 case 2:
				 display7SEG(3);
				 break;
			 case 3:
				 display7SEG(4);
				 break;
		 }
		 if(timer2_flag == 1){
			 index_led = 2;
			 setTimer2(260);
		 }
		break ;
	case 2:
		 HAL_GPIO_WritePin (en2_GPIO_Port,en2_Pin, GPIO_PIN_RESET ) ;
		 HAL_GPIO_WritePin (GPIOA,en0_Pin|en1_Pin|en3_Pin, SET) ;
		 switch(mode){
			 case 0:
				 display7SEG((count_ex%100)/10);
				 break;
			 case 1:
				 display7SEG( (red_timer%100)/10);
				 break;
			 case 2:
				 display7SEG( (yellow_timer%100)/10);
				 break;
			 case 3:
				 display7SEG( (green_timer%100)/10);
				 break;
		 }
		 if(timer2_flag == 1){
			 index_led = 3;
			 setTimer2(260);
		 }

		break ;
	case 3:
		 HAL_GPIO_WritePin (en3_GPIO_Port,en3_Pin, GPIO_PIN_RESET ) ;
		 HAL_GPIO_WritePin (GPIOA,en0_Pin|en1_Pin|en2_Pin, SET) ;
		 switch(mode){
			 case 0:
				 display7SEG(count_ex%10);
				 break;
			 case 1:
				 display7SEG( red_timer%10);
				 break;
			 case 2:
				 display7SEG( yellow_timer%10);
				 break;
			 case 3:
				 display7SEG( green_timer%10);
				 break;
		 }
		 if(timer2_flag == 1){
			 index_led = 0;
			 setTimer2(260);
		 }
		break ;
	}
}

void fsm_for_trafficled_normal(void){
		switch (state1){
		case 0:
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);

			setTimer0(timer[0]*1000);
			count = timer[0];
			state1 = 1;
			break;
		case 1:
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);
			if(timer4_flag == 1){
				count--;
				setTimer4(1000);
			}
			if(timer0_flag == 1){
				state1 = 3;
				count = timer[2];
				setTimer0(timer[2]*1000);
			}
			break;
		case 2:
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_RESET);

			if(timer4_flag == 1){
				count--;
				setTimer4(1000);
			}
			if(timer0_flag == 1){
				state1 = 1;
				count = timer[0];
				setTimer0(timer[0]*1000);
			}
			break;
		case 3:
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, GPIO_PIN_SET);

			if(timer4_flag == 1){
				count--;
				setTimer4(1000);
			}

			if(timer0_flag == 1){
				state1 = 2;
				count = timer[1];
				setTimer0(timer[1]*1000);
			}

			break;
		}
}

void fsm_for_trafficled_normal_ex(void){
		switch (state2){
		case 0:
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);

			setTimer3(timer[2]*1000);
			count_ex = timer[2];
			state2 = 1;
			break;
		case 1:
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_RESET);

			if(timer3_flag == 1){
				state2 = 2;
				count_ex = timer[1];
				setTimer3(timer[1]*1000);
			}
			if(timer5_flag == 1){
				count_ex--;
				setTimer5(1000);
			}
			break;
		case 2:
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);

			if(timer3_flag == 1){
				state2 = 3;
				count_ex = timer[0];
				setTimer3(timer[0]*1000);
			}
			if(timer5_flag == 1){
				count_ex--;
				setTimer5(1000);
			}
			break;
		case 3:
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);

			if(timer3_flag == 1){
				state2 = 1;
				count_ex = timer[2];
				setTimer3(timer[2]*1000);
			}
			if(timer5_flag == 1){
				count_ex--;
				setTimer5(1000);
			}
			break;
		}
}

