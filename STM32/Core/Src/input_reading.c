/*
 * input_reading.c
 *
 *  Created on: Oct 29, 2022
 *      Author: tuanb
 */

#include "input_reading.h"

int button_flag[N0_OF_BUTTONS] = {0,0,0};

int KeyReg0[N0_OF_BUTTONS] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg1[N0_OF_BUTTONS] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg2[N0_OF_BUTTONS] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg3[N0_OF_BUTTONS] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};

//int TimerForKeyPress = 200;

int isButtonPressed(int index){
	if (button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index){
	button_flag[index] = 1;
}

void getKeyInput(){
	for (int i = 0; i < N0_OF_BUTTONS; i++){
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		if(i == 0)
			KeyReg2[i] = HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin);
		if(i==1)
			KeyReg2[i] = HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin);
		if(i==2)
			KeyReg2[i] = HAL_GPIO_ReadPin(B3_GPIO_Port,B3_Pin);
		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg3[i] != KeyReg2[i]){
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE){
					subKeyProcess(i);
				}
			}
		}
	}
}


