/*
 * fsm_mode.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Duc Original
 */

#include "fsm_mode.h"

void fsm_simple_buttons_run()
{
	switch(status)
	{
		case RESETT:
//			value = 0;
//			display7SEG(value);

			if(timer1_flag == 1)
			{
				value = 0;
				display7SEG(value);
			}

			if(isButton1Pressed() == 1)
			{
				value = 0;
				display7SEG(value);
			}

			if(isButton2Pressed() == 1)
			{
				value++;
				if(value > 9) value = 0;
				display7SEG(value);
				status = INCREASE;
				setTimer1(30);
			}

			if(isButton3Pressed() == 1)
			{
				value--;
				if(value < 0) value = 9;
				display7SEG(value);
				status = DECREASE;
				setTimer1(30);
			}

			break;
		case INCREASE:
			if(isButton2Pressed() == 1)
			{	value++;
				if(value > 9) value = 0;

				if(timer1_flag == 1)
				{
					display7SEG(value);
					setTimer1(30);
				}
			}

			if(runningFlag2 == 1)
			{
				value--;
				if(value < 0)
				{
					status = RESETT;
				//	runningFlag2 = 0;
				}
				else
				{
					status = RUN;
					setTimer1(100);
				}
			}
			if(isButton1Pressed() == 1)
			{
				status = RESETT;
				setTimer1(30);
			}
			else if(isButton3Pressed() == 1)
			{
				value--;
				if(value < 0) value = 9;
				display7SEG(value);
				status = DECREASE;
				setTimer1(30);
			}

			break;
		case DECREASE:
			if(isButton3Pressed() == 1)
			{	value--;
				if(value < 0) value = 9;
				if(timer1_flag == 1)
				{
					display7SEG(value);
					setTimer1(30);
				}
			}
			if(runningFlag3 == 1)
			{

				value--;
				if(value < 0)
				{
					status = RESETT;
				//	runningFlag3 = 0;
				}
				else
				{
					status = RUN;
					setTimer1(100);
				}

			}
			if(isButton1Pressed() == 1)
			{
				status = RESETT;
				setTimer1(30);
			}
			else if(isButton2Pressed() == 1)
			{
				value++;
				if(value > 9) value = 0;
				display7SEG(value);
				status = INCREASE;
				setTimer1(30);
			}
			break;
		case RUN:

			if(timer1_flag == 1)
			{
				display7SEG(value);
				value--;
				if(value < 0) status = RESETT;
				else
					setTimer1(100);
			}
			break;


	}
}
