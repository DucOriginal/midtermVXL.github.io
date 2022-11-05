/*
 * button.h
 *
 *  Created on: Oct 26, 2022
 *      Author: Duc Original
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

int runningFlag2;
int runningFlag3;

int isButton1Pressed();
void getKeyInput_B1();

int isButton2Pressed();
void getKeyInput_B2();

int isButton3Pressed();
void getKeyInput_B3();

#endif /* INC_BUTTON_H_ */
