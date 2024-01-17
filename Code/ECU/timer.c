/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the TIMER AVR driver
 *
 * Author: nader essam ali
 *
 *******************************************************************************/

#include "timer.h"
#include "avr/io.h"
#include <avr/interrupt.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr_Timer0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr_Timer1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr_Timer2)(void) = NULL_PTR;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect){

	if(g_callBackPtr_Timer0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after overflow occur*/
		(*g_callBackPtr_Timer0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}

ISR(TIMER0_COMP_vect){

	if(g_callBackPtr_Timer0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after overflow occur*/
		(*g_callBackPtr_Timer0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}
ISR(TIMER1_OVF_vect){

	if(g_callBackPtr_Timer1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after overflow occur*/
		(*g_callBackPtr_Timer1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}

ISR(TIMER1_COMPA_vect){

	if(g_callBackPtr_Timer1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after overflow occur*/
		(*g_callBackPtr_Timer1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}
ISR(TIMER2_OVF_vect){

	if(g_callBackPtr_Timer2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after overflow occur*/
		(*g_callBackPtr_Timer2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}

ISR(TIMER2_COMP_vect){

	if(g_callBackPtr_Timer2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after overflow occur*/
		(*g_callBackPtr_Timer2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description:Function to initialize timer driver
 * 1.set required timer type (timer0,timer1,timer2)
 * 2. set required timer mode (overflow or compare )
 * 3. Set the required clock.
 * 4. set required Intial value.
 */
void Timer_intit(const Timer_ConfigType * Config_Ptr){
	switch(Config_Ptr->timer_type){
	case 0:
		/*choosing required timer0 mode*/
		switch(Config_Ptr->timer_mode){
		case 0: /*Overflow mode initialization*/
			/* Configure the timer control register
			 * 1. Non PWM mode FOC0=1
			 * 2. Normal Mode WGM01=0 & WGM00=0
			 * 3. clock as required
			 */
			TCCR0 =(1<<FOC0);
			TCCR0 =(TCCR0 & 0xf8) | (Config_Ptr->timer_clock);
			/*Set Timer0 initial value as required*/
			TCNT0=Config_Ptr->Intial_value;
			/*Enable Timer0 Overflow Interrupt*/
			TIMSK=(1<<TOIE0);
			break;
		case 1:/*Compare mode initialization*/
			/* Configure the timer control register
			 * 1. Non PWM mode FOC0=1
			 * 2. CTC Mode WGM01=1 & WGM00=0
			 * 3. clock as required
			 */
			TCCR0 =(1<<FOC0)|(1<<WGM01);
			TCCR0 =(TCCR0 & 0xf8) | (Config_Ptr->timer_clock);
			/*Set Timer0 initial value as required*/
			TCNT0=Config_Ptr->Intial_value;
			/*Set Timer0 Compare match as required*/
			OCR0=Config_Ptr->Comare_value;
			/*Enable Timer0 Compare match Interrupt*/
			TIMSK=(1<<OCIE0);
			break;
		}
		break;
		case 1:
			/*choosing required timer0 mode*/
			switch(Config_Ptr->timer_mode){
			case 0: /*Overflow mode initialization*/

				/* Configure the timer control register TCCR1A
				 * 1. Non PWM mode FOC1A=1 & FOC1B=1
				 * 2. Normal Mode WGM10=0 & WGM11=0
				 */
				TCCR1A=(1<<FOC1A) |(1<<FOC1B);
				/*Configure the timer control register TCCR1B
				 * 1. Normal Mode WGM12=0 & WGM13=0
				 * 2. clock as required CS12,CS11,CS10
				 */
				TCCR1B=(TCCR1B&0xf8)|(Config_Ptr->timer_clock);
				/*Set Timer2 initial value as required*/
				TCNT1=Config_Ptr->Intial_value;

				/*Enable Timer1 Overflow Interrupt*/
				TIMSK=(1<<TOIE1);
				break;
			case 1:/*Compare mode initialization*/
				/* Configure the timer control register TCCR1A
				 * 1. Non PWM mode FOC1A=1 & FOC1B=1
				 * 2. CTC Mode WGM10=0 & WGM11=0
				 */
				TCCR1A=(1<<FOC1A) |(1<<FOC1B);
				/*Configure the timer control register TCCR1B
				 * 1. CTC Mode WGM12=1 & WGM13=0
				 * 2. clock as required CS12,CS11,CS10
				 */
				TCCR1B=(1<<WGM12);
				TCCR1B=(TCCR1B&0xf8)|(Config_Ptr->timer_clock);
				/*Set Timer1 initial value as required*/
				TCNT1=Config_Ptr->Intial_value;
				/*Set Timer1 Compare match as required*/
				OCR1A=Config_Ptr->Comare_value;
				/*Enable Timer1 Compare match Interrupt*/
				TIMSK=(1<<OCIE1A);
				break;
			}
			break;
			case 2:
				/*choosing required timer2 mode*/
				switch(Config_Ptr->timer_mode){
				case 0:/*Overflow mode initialization*/
					/* Configure the timer control register TCCR2
					 * 1. Non PWM mode FOC2=1
					 * 2. Normal Mode WGM20=0 & WGM21=0
					 * 3. clock as required CS20,CS21,CS22
					 */
					TCCR2=(1<<FOC2);
					TCCR2=(TCCR0 & 0xf8) | (Config_Ptr->timer_clock);
					/*Set Timer2 initial value as required*/
					TCNT2=Config_Ptr->Intial_value;
					/*Enable Timer1 Overflow Interrupt*/
					TIMSK=(1<<TOIE2);
					break;
				case 1:/*Compare mode initialization*/
					/* Configure the timer control register TCCR2
					 * 1. Non PWM mode FOC2=1
					 * 2. CTC Mode WGM20=0 & WGM21=1
					 * 3. clock as required CS20,CS21,CS22
					 */
					TCCR2=(1<<FOC2)|(1<<WGM21);
					TCCR2=(TCCR0 & 0xf8) | (Config_Ptr->timer_clock);
					/*Set Timer2 initial value as required*/
					TCNT2=Config_Ptr->Intial_value;
					/*Set Timer2 Compare match as required*/
					OCR2=Config_Ptr->Comare_value;
					/*Enable Timer2 Compare match Interrupt*/
					TIMSK=(1<<OCIE2);
					break;
				}
				break;
	}
}
/*
 * Description: Function to set the Call Back function address.
 */
void Timer_setCallBack(void(*a_ptr)(void),Timer_Type timer_Type){
	switch(timer_Type){
	case 0:/*timer 0*/
		g_callBackPtr_Timer0=a_ptr;
		break;
	case 1:/*timer 1*/
		g_callBackPtr_Timer1=a_ptr;
		break;
	case 2:/*timer 2*/
		g_callBackPtr_Timer2=a_ptr;
		break;
	}
}
/*Description:Function to DeInit the timer */
void Timer_deInit(Timer_Type timer_Type){
	switch(timer_Type){
	case 0:/*timer 0*/
		/* Clear All Timer0 Registers */
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0=0;
		ICR1 = 0;

		/* Disable the Timer0 interrupt */
		TIMSK &=~(1<<TOIE0)&~(1<<OCIE0);
		break;
	case 1:/*timer 1*/
		/* Clear All Timer1Registers */
		TCNT1=0;
		TCCR1A=0;
		TCCR1B=0;
		OCR1A=0;
		/* Disable the Timer1 interrupt */
		TIMSK &=~(1<<TOIE1)&~(1<<OCIE1A);
		break;
	case 2:/*timer 2*/
		/* Clear All Timer2 Registers */
		TCCR2=0;
		TCNT2 = 0;
		OCR0=0;
		/* Disable the Timer2 interrupt */
		TIMSK&=~(1<<TOIE2) &~(1<<OCIE2);
		break;
	}
}
