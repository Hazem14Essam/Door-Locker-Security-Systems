 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the TIMER AVR driver
 *
 * Author:nader essam ali
 *******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_
#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	Timer_0,Timer_1,Timer_2
}Timer_Type;
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_CLOCK_8,F_CPU_CLOCK_64,F_CPU_CLOCK_256,F_CPU_CLOCK_1024
}Timer_Prescaler;

typedef enum{
	Overflow,Compare
}Timer_Mode;

typedef struct{
	uint32 Intial_value;
	uint32 Comare_value;
	Timer_Type timer_type;
	Timer_Prescaler timer_clock;
	Timer_Mode timer_mode;
}Timer_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:Function to initialize timer driver
 * 1.set required timer type (timer0,timer1,timer2)
 * 2. set required timer mode (overflow or compare )
 * 3. Set the required clock.
 * 4. set required Intial value.
 */
void Timer_intit(const Timer_ConfigType * Config_Ptr);
/*
 * Description: Function to set the Call Back function address.
 */
void Timer_setCallBack(void(*a_ptr)(void),Timer_Type timer_Type);

/*Description:Function to DeInit the timer */
void Timer_deInit(Timer_Type timer_Type);

#endif /* TIMER0_H_ */
