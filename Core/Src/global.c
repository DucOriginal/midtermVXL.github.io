/*
 * global.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Duc Original
 */


#include "global.h"

int status = 0;
int value = 0;

uint8_t segmentNumber[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void display7SEG(int num) //display time on x-axis (include 2 7-segment LEDs)
{
	uint8_t number = segmentNumber[num];
	//Check a nth bit by shifting n times to the right, then bitwise AND it:
	HAL_GPIO_WritePin(GPIOB, SEG0_Pin, ((number>>0)&0x01));
	HAL_GPIO_WritePin(GPIOB, SEG1_Pin, ((number>>1)&0x01));
	HAL_GPIO_WritePin(GPIOB, SEG2_Pin, ((number>>2)&0x01));
	HAL_GPIO_WritePin(GPIOB, SEG3_Pin, ((number>>3)&0x01));
	HAL_GPIO_WritePin(GPIOB, SEG4_Pin, ((number>>4)&0x01));
	HAL_GPIO_WritePin(GPIOB, SEG5_Pin, ((number>>5)&0x01));
	HAL_GPIO_WritePin(GPIOB, SEG6_Pin, ((number>>6)&0x01));
}
