/*
 * input_reading.h
 *
 *  Created on: Oct 29, 2022
 *      Author: tuanb
 */


#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_


#include "global.h"

#define N0_OF_BUTTONS 3

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

extern int button_flag[N0_OF_BUTTONS];

int isButtonPressed(int);

void subKeyProcess(int);
void getKeyInput(void);

#endif /* INC_INPUT_READING_H_ */
