/*
 * dc_motor.c
 *
 *      Author: nader essam ali
 */

#include "dc_motor.h"
#include "gpio.h"
#include "commen_macros.h"
#include "avr/io.h"

/*
 * Description:
 * The Function responsible for setup the direction for the one motor pins through the GPIO driver.
 * */
void DcMotor_Init(){
	GPIO_setupPinDirection(MOTOR_PORT,MOTER_INPUT1,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT,MOTER_INPUT2,PIN_OUTPUT);
	GPIO_writePin(MOTOR_PORT,MOTER_INPUT1,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT,MOTER_INPUT2,LOGIC_LOW);
}
/*
 * Description:
 * rotate motor as required
 */
void DCMotor_Rotate(DcMotor_State state){
	if(state == CW)
	{
		/* Rotates the Motor CW */
		GPIO_writePin(MOTOR_PORT,MOTER_INPUT1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT,MOTER_INPUT2,LOGIC_HIGH);


	}
	else if(state == A_CW)
	{
		/* Rotates the Motor A-CW */
		GPIO_writePin(MOTOR_PORT,MOTER_INPUT1,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT,MOTER_INPUT2,LOGIC_LOW);


	}
	else if(state == Stop)
	{
		/* Stop the Motor */
		GPIO_writePin(MOTOR_PORT,MOTER_INPUT1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT,MOTER_INPUT2,LOGIC_LOW);


	}
	else
	{
		/* Invalid Input State - Do Nothing */
	}
}
