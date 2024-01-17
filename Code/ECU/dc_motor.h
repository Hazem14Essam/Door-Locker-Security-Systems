/*
 * dc_motor.h
 *      Author: nader essam ali
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"
#include "gpio.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_PORT PORTD_ID
#define MOTER_INPUT1 PIN3_ID
#define MOTER_INPUT2 PIN4_ID
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	Stop,CW,A_CW
}DcMotor_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 * The Function responsible for setup the direction for the one motor pins through the GPIO driver.
 */
void DcMotor_Init();
/*
 * Description:
 * rotate motor as required
 */
void DCMotor_Rotate(DcMotor_State state);


#endif /* DC_MOTOR_H_ */
