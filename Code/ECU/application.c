
/******************************************************************************
 *
 * Module: Function of the System
 *
 * File Name: function.c
 *
 * Description: Source file for function of the system
 *
 * Author: nader essam ali
 *
 *******************************************************************************/

#include "application.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 g_tick=0;/*to count number of interrupt*/
uint8 holed_system=0;/*using this variable to holed the system*/
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description:
 * this function compare between two password
 * first password which store in EEPROM
 * second password which enter by the user
 * result of compare is
 * '1':the two password is equal
 * '0':the two password is not equal
 */
uint8 chech_match_password(uint8 *pass1,uint8 *pass2){
	uint8 res=1,count;/*local variable*/
	/*compare between two password*/
	for(count=0 ; count<5;count++){
		if(pass1[count]!=pass2[count]){
			res=0;/*in case of two password not equal*/
		}
	}
	/*return the result*/
	return res;
}
/*
 * Description:
 * function to turn on motor
 */
void open_door(void){
	g_tick++;/*increment every 1 second*/

	if(g_tick>=0 &&g_tick < 15){
		/*Rotate the motor --> clock wise for 15 second*/
		DCMotor_Rotate(CW);
	}else if(g_tick>=15&&g_tick<18){
		/*turn off motor for 3 second*/
		DCMotor_Rotate(Stop);
	}else if(g_tick>=18&&g_tick<33){
		/*Rotate the motor --> anti-clock wise for 15 second*/
		DCMotor_Rotate(A_CW);
	}else if(g_tick==33){
		/*turn off motor*/
		DCMotor_Rotate(Stop);
		/*deInit timer 1*/
		Timer_deInit(Timer_1);
		/*clear g_tick*/
		g_tick=0;
		/*set holed_system*/
		holed_system=1;
	}

}
/*
 * Description:
 * function to turn on BUZZER
 */
void BUZZER_turnOn(){
	g_tick++;/*increment every 1 second*/
	if(g_tick>=0 &&g_tick < 60){
		/*turn on buzzer for 60 second*/
		BUZZER_on();
	}else if(g_tick==60){/*after 60 second*/
		/*turn off buzzer*/
		BUZZER_off();
		/*deInit timer 1*/
		Timer_deInit(Timer_1);
		/*clear g_tick*/
		g_tick=0;
		/*set holed_system*/
		holed_system=1;
	}
}


