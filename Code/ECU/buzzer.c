 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the BUZZER driver
 *
 * Author:nader essam ali
 *
 *******************************************************************************/
#include "buzzer.h"
#include "commen_macros.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * initialize BUZZER pin
 */
void BUZZER_intit(void){
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT); /*initialize required pin as output*/
}
/*
 * Description:
 * function to turn ON BUZZER
 */
void BUZZER_on(void){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);/*set required pin as HIGH*/
}
/*
 * Description:
 * function to turn OFF BUZZER
 */
void BUZZER_off(void){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);/*set required pin as LOW*/
}
