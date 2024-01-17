 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the BUZZER driver
 *
 * Author: Hazem Essam Ali ElSayed
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT PORTC_ID
#define BUZZER_PIN  PIN4_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description:
 * initialize BUZZER pin
 */
void BUZZER_intit(void);
/*
 * Description:
 * function to turn ON BUZZER
 */
void BUZZER_on(void);
/*
 * Description:
 * function to turn OFF BUZZER
 */
void BUZZER_off(void);


#endif /* BUZZER_H_ */
