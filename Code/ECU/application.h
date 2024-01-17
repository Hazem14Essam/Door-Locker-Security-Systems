 /******************************************************************************
 *
 * Module: Function of the System
 *
 * File Name: function.h
 *
 * Description: Header file  for function of the system
 *
 * Author: nader essam ali
 *
 *******************************************************************************/

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include "external_eeprom.h"
#include "uart.h"
#include "util/delay.h"
//#include "lcd.h"
#include "std_types.h"
#include "buzzer.h"
#include "timer.h"
#include "dc_motor.h"
#include "avr/io.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASSWORD_NUMBER 5
#define MC1_READY 0x10
/*******************************************************************************
 *                      Functions Prototypes                                   *
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
uint8 chech_match_password(uint8 *pass1,uint8 *pass2);
/*
 * Description:
 * function to turn on motor
 */
void open_door(void);
/*
 * Description:
 * function to turn on BUZZER
 */
void BUZZER_turnOn();

#endif /* FUNCTION_H_ */
