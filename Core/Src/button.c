/*
 * button.c
 *
 *  Created on: Oct 26, 2022
 *      Author: Duc Original
 */
#include "button.h"
//button 1
int button1_flag = 0;
int KeyReg0_B1 = NORMAL_STATE;
int KeyReg1_B1 = NORMAL_STATE;
int KeyReg2_B1 = NORMAL_STATE;
int KeyReg3_B1 = NORMAL_STATE;
int TimerForKeyPress_B1 = 300;

//button 2
int button2_flag = 0;
int KeyReg0_B2 = NORMAL_STATE;
int KeyReg1_B2 = NORMAL_STATE;
int KeyReg2_B2 = NORMAL_STATE;
int KeyReg3_B2 = NORMAL_STATE;
int TimerForKeyPress_B2 = 300;
int TimerAfter1s_B2 = 300;
int runningFlag2 = 0;
int TimerRunFlag2 = 200;

//button 3
int button3_flag = 0;
int KeyReg0_B3 = NORMAL_STATE;
int KeyReg1_B3 = NORMAL_STATE;
int KeyReg2_B3 = NORMAL_STATE;
int KeyReg3_B3 = NORMAL_STATE;
int TimerForKeyPress_B3 = 300;
int TimerAfter1s_B3 = 300;
int runningFlag3 = 0;
int TimerRunFlag3 = 200;


int isButton1Pressed()
{
	if(button1_flag == 1)
	{
		button1_flag = 0;
		return 1;
	}
	return 0;
}

int isButton2Pressed()
{
	if(button2_flag == 1)
	{
		button2_flag = 0;
		return 1;
	}
	return 0;
}

int isButton3Pressed()
{
	if(button3_flag == 1)
	{
		button3_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess_B1()	{ button1_flag = 1;}
void subKeyProcess_B2() { button2_flag = 1;}
void subKeyProcess_B3() { button3_flag = 1;}

void getKeyInput_B1()
{
	KeyReg0_B1 = KeyReg1_B1;
	KeyReg1_B1 = KeyReg2_B1;
	KeyReg2_B1 = HAL_GPIO_ReadPin(RESET_GPIO_Port, RESET_Pin);
	if((KeyReg0_B1 == KeyReg1_B1) && (KeyReg1_B1 == KeyReg2_B1))
	{
		if(KeyReg3_B1 != KeyReg2_B1) //press and release
		{
			KeyReg3_B1 = KeyReg2_B1; //update state KeyReg3
			if(KeyReg2_B1 == PRESSED_STATE)
			{
				subKeyProcess_B1(); //set flag
				TimerForKeyPress_B1 = 200;
			}
		}
		else // press and hold. If hold a button, KeyReg3 =  KeyReg2, do not enter if statement
		{
			TimerForKeyPress_B1--;
			if(TimerForKeyPress_B1 == 0)
			{
				KeyReg3_B1 = NORMAL_STATE;
			}
		}
	}
}

void getKeyInput_B2()
{
	KeyReg0_B2 = KeyReg1_B2;
	KeyReg1_B2 = KeyReg2_B2;
	KeyReg2_B2 = HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin);
	if((KeyReg0_B2 == KeyReg1_B2) && (KeyReg1_B2 == KeyReg2_B2))
	{
		//Press a button, it will change LED's state. However, if hold the button, after 3s, it will change LED's state.
		if(KeyReg3_B2 != KeyReg2_B2) //press and release
		{
			KeyReg3_B2 = KeyReg2_B2; //update state KeyReg3
			if(KeyReg2_B2 == PRESSED_STATE)
			{
				subKeyProcess_B2(); //set flag
				//Initially, set up TimerAfter1s_B2 = 300.
				TimerForKeyPress_B2 = TimerAfter1s_B2;
				TimerRunFlag2 = 200;
			}
		}
		else // press and hold. If hold a button, KeyReg3 =  KeyReg2, do enter else statement
		{	 // Count down 3s then change LED's state. If keep holding, repeat to count down 1s until release the button.
			TimerForKeyPress_B2--;
			if(TimerForKeyPress_B2 == 0)
			{
				KeyReg3_B2 = NORMAL_STATE;
				TimerAfter1s_B2 = 100;
			}
			// Handle the idle. If after 2s do nothing, run count down the LED segment.
			if(KeyReg2_B2 == NORMAL_STATE && KeyReg3_B2 == KeyReg2_B2)
			{
				TimerRunFlag2--;
				if(TimerRunFlag2 == 0)
				{
					runningFlag2 = 1;
				}
			}
		}
	}
}

void getKeyInput_B3()
{
	KeyReg0_B3 = KeyReg1_B3;
	KeyReg1_B3 = KeyReg2_B3;
	KeyReg2_B3 = HAL_GPIO_ReadPin(DEC_GPIO_Port, DEC_Pin);
	if((KeyReg0_B3 == KeyReg1_B3) && (KeyReg1_B3 == KeyReg2_B3))
	{
		//Press a button, it will change LED's state. However, if hold the button, after 2s, it will change LED's state.
		if(KeyReg3_B3 != KeyReg2_B3) //press and release
		{
			KeyReg3_B3 = KeyReg2_B3; //update state KeyReg3
			if(KeyReg2_B3 == PRESSED_STATE)
			{
				subKeyProcess_B3(); //set flag
				TimerForKeyPress_B3 = TimerAfter1s_B3;
				TimerRunFlag3 = 200;
			}
		}
		else // press and hold. If hold a button, KeyReg3 =  KeyReg2, do not enter if statement
		{	 // Count down 2s then change LED's state
			TimerForKeyPress_B3--;
			if(TimerForKeyPress_B3 == 0)
			{
				KeyReg3_B3 = NORMAL_STATE;
				TimerAfter1s_B3 = 100;
				TimerRunFlag3 = 200;

			}
			if(KeyReg2_B3 == NORMAL_STATE && KeyReg3_B3 == KeyReg2_B3)
			{
				TimerRunFlag3--;
				if(TimerRunFlag3 == 0)
				{
					runningFlag3 = 1;
				}
			}
		}
	}

}

