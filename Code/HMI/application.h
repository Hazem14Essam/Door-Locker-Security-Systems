 /******************************************************************************
 *
 * Module: Function of the System
 *
 * File Name: function.h
 *
 * Description: Header file  for function of the system
 *
 * Author:Hazem Essam  Ali El-Sayed
 *
 *******************************************************************************/

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include "std_types.h"
#include "uart.h"
#include "timer.h"
#include "lcd.h"
#include"keypad.h"
#include "avr/io.h" /* To use the SREG register */
#include "util/delay.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASSWORD_NUMBER 5
#define MC1_READY 0x10
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Description:
 * function to take one option from user
 * '+':to open door
 * '-':to change password
 */
uint8 select_option(void);
/*
 * Description:function to set password for the system
 * take two pointer ,to ask user to enter password for two time
 * and compare two password , so return the result
 * 0: for mismatch
 * 1:for match
 */
uint8 first_login_password_enter(uint8 *pass1,uint8 *pass2);
/*
 * Description:
 * take password from user to open door or to change password
 */
void enter_password(uint8 *pass);
/*
 * Description:
 * if user enter password 3 time error ,display on screen
 */
void error_3_password(void);
/*
 * Description:
 * Display on screen during door is open or close
 *
 */
void Display(void);
#endif /* FUNCTION_H_ */
