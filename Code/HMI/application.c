/******************************************************************************
 *
 * Module: Function of the System
 *
 * File Name: function.c
 *
 * Description: Source file for function of the system
 *
 * Author: Hazem essam ali
 *
 *******************************************************************************/


#include "application.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint16 g_tick=0;/*to count number of interrupt*/
uint8 holed_system=0;/*using this variable to holed the system*/
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*Description:
 * function to take one option from user
 * '+':to open door
 * '-':to change password
 */
uint8 select_option(void){
	uint8 option;
	LCD_clearScreen();
	LCD_displayString("+: open door");
	LCD_moveCursor(1,0);
	LCD_displayString("-: change pass");
	/*take the option from user*/
	while(option!='+' && option!='-'){
		/* Get the pressed button from keypad */
		option=KEYPAD_getPressedKey();
	}
	_delay_ms(500);
	LCD_clearScreen();/*clear screen*/
	return option;/*return the choise*/
}
/*
 * Description:function to set password for the system
 * take two pointer ,to ask user to enter password for two time
 * and compare two password , so return the result
 * 0: for mismatch
 * 1:for match
 */
uint8 first_login_password_enter(uint8 *pass1,uint8 *pass2){
	uint8 count ,res=1; /*local variable*/
	LCD_clearScreen();/*clear screen*/
	LCD_displayString("enter password");
	/*take first password form user*/
	for(count =0;count<5 ;count++){
		/*move cursor as required*/
		LCD_moveCursor(1,count);
		/* Get the pressed button from keypad and store it in array*/
		pass1[count] = KEYPAD_getPressedKey();

		/*display the password as '*****' */
		LCD_displayCharacter('*');
		/*delay to take anther pressed button from keypad  */
		_delay_ms(500);

	}
	/*after enter password click '=' to move to second password*/
	while( ( KEYPAD_getPressedKey() )!= '='){}
	/*delay to take anther pressed button from keypad  */
	_delay_ms(500);
	LCD_clearScreen();/*clear screen*/
	LCD_displayString("confirm password");
	/*take second password form user*/
	for(count =0;count<5 ;count++){
		/*move cursor as required*/
		LCD_moveCursor(1,count);
		/* Get the pressed button from keypad and store it in array*/
		pass2[count] = KEYPAD_getPressedKey();
		/*display the password as '*****' */
		LCD_displayCharacter('*');
		/*delay to take anther pressed button from keypad  */
		_delay_ms(500);

	}
	/*after enter password click '=' to move to compare two password*/
	while( ( KEYPAD_getPressedKey() )!= '='){}
	/*delay to take anther pressed button from keypad  */
	_delay_ms(500);
	LCD_clearScreen();

	/*compare two password*/
	for(count=0 ; count<5;count++){
		if(pass1[count]!=pass2[count]){
			res=0;/*in case two password not equal*/
		}
	}
	/*return :
	 * 0 :in case two password not equal
	 * 1 :in case two password equal
	 */
	return res;
}
/*Description:
 * take password from user to open door or to change password
 */
void enter_password(uint8 *pass){
	uint8 count;/*local variable*/
	LCD_clearScreen();
	LCD_displayString("enter password");
	/*second password form user*/
	for(count =0;count<5 ;count++){
		/*move cursor as required*/
		LCD_moveCursor(1,count);
		/* Get the pressed button from keypad and store it in array*/
		pass[count] = KEYPAD_getPressedKey();

		/*display the password as '*****' */
		LCD_displayCharacter('*');
		/*delay to take anther pressed button from keypad  */
		_delay_ms(500);

	}
	/*after enter password click '=' to move to other instruction*/
	while( ( KEYPAD_getPressedKey() )!= '='){}
	/*delay to take anther pressed button from keypad  */
	_delay_ms(500);
	LCD_clearScreen();
}
/*
 * Description:
 * Display on screen during door is open or close
 *
 */
void Display(void){
	g_tick++;/*increment every 1 second*/
	if(g_tick>=0 &&g_tick < 18){
		/*display for 18 second */
		LCD_displayStringRowColumn(0,0,"Door is Opening");

	}else if(g_tick>=18&&g_tick<33){
		/*display for 15 second */
		LCD_displayStringRowColumn(0,0,"Door is Closing  ");

	}
	else if(g_tick==33){
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
 * if user enter password 3 time error ,display on screen
 */
void error_3_password(void){
	g_tick++;/*increment every 1 second*/
	if(g_tick>=0 && g_tick < 60){
		/*display for 60 second */
		LCD_displayStringRowColumn(0,0,"EMSK HARAMY !!!");
	}else if(g_tick==60){
		/*deInit timer 1*/
		Timer_deInit(Timer_1);
		/*clear g_tick*/
		g_tick=0;
		/*set holed_system*/
		holed_system=1;
	}
}
