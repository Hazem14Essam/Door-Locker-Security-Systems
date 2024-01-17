/*
 * main_MC1.c
 *      Author:Hazem Essam Ali ElSayed
 */

#include "application.h"

uint8 pass[PASSWORD_NUMBER];/*array of 5 element ,use to store send password to store in EEPROM*/
uint8 pass_comp[PASSWORD_NUMBER];/*array of 5 element ,use as a compare password with stored in EEPROM*/

extern uint8 holed_system;

int main(void)
{
	uint8 recieve_byte,match_login=0,count,slec_option,res_match,error=0;
	/* Enable Global Interrupt I-Bit */
	SREG=(1<<7);
	/* Initialize the LCD Driver */
	LCD_init();

	/* Create configuration structure for timer0 driver */
	Timer_ConfigType config_time={0,7813,Timer_1,F_CPU_CLOCK_1024,Compare};

	/* Create configuration structure for URT driver */
	Uart_ConfigType config={STOP_BIT_1,BIT_8,DISABLED};

	/* Initialize the URT Driver */
	UART_init(&config);

	/* Send MC2_READY byte to MC2 to ask it to send the Byte */
	UART_sendByte(MC1_READY);

	/* Receive Byte from MC1 through UART */
	recieve_byte=UART_recieveByte();

	/*if recieve_byte =0 ,is the first time to login,and ask user to enter password to store it  */
	if(recieve_byte==0xff){
		LCD_displayString("Hello !!");
		_delay_ms(2000);
		/*while match_loin=0 , the two password is not match and ask user again*/
		while(match_login!=1){
			match_login=first_login_password_enter(pass,pass_comp);
			if(match_login==0){/*in case two password not match*/
				LCD_displayStringRowColumn(0,0,"Not Match");
				LCD_displayStringRowColumn(1,0,"Enter Again");
				_delay_ms(2000);
			}
		}
		/*clear match_login ,so using again*/
		match_login=0;

		/*send password to MC1 to store in EEPROM*/
		for(count=0 ;count<PASSWORD_NUMBER;count++){
			/* Wait until MC2 is ready to receive the Byte */
			while(UART_recieveByte() != MC1_READY){}
			/* Send the required Byte to MC2 through UART */
			UART_sendByte(pass[count]);
			_delay_ms(60);
		}

	}




	while(1)
	{

		/*select_option() return '+' or '-'
		 * '+':to open door
		 * '-':to change password
		 */
		slec_option=select_option();
		/*clear res_match as default ,
		 * when res_match = 1 ,the enter password from user is equal the password in EEPROM
		 * when res_match = 0 ,the enter password from user is not equal the password in EEPROM
		 */
		res_match=0;
		if(slec_option=='+'){/*user select open door*/
			/* Wait until MC2 is ready to receive the Byte */
			while(UART_recieveByte() != MC1_READY){}
			/* Send the required Byte to MC2 through UART */
			UART_sendByte(slec_option);
			/*looping until enter correct password,only 3 time enter*/
			while(error<3 && res_match==0){
				/*function to take password from user to open door*/
				enter_password(pass);
				/* Wait until MC2 is ready to receive the Byte */
				while(UART_recieveByte() != MC1_READY){}
				/*send password to MC2 ,to check match this password with password stored in EEPROM*/
				for(count=0 ;count<PASSWORD_NUMBER;count++){
					/* Send the required Byte to MC2 through UART */
					UART_sendByte(pass[count]);
					_delay_ms(60);
				}
				/*
				 * after sending password to MC2 to check match with the password in EEPROM
				 * Recieve the result with the UART
				 */
				/* Send MC2_READY byte to MC2 to ask it to send the Byte */
				UART_sendByte(MC1_READY);
				/* Receive Byte from MC1 through UART */
				res_match = UART_recieveByte();
				/*if check_match =0 ,password  incorrect , if check_match=1 ,password correct */
				if(res_match==0){/*password  incorrect*/
					LCD_clearScreen();
					error++;
					if(error<3){

						LCD_displayStringRowColumn(0,0,"error password");
						LCD_displayStringRowColumn(1,0,"enter again");
						_delay_ms(1000);
					}else if(error==3){

						/* Set the Call back function pointer in the timer0 driver */
						Timer_setCallBack(&error_3_password,Timer_1);
						/* Initialize the timer0 Driver */
						Timer_intit(&config_time);
						/*holed system until finish call back function*/
						while(holed_system==0 ){}
						/*clear holed_system for using again*/
						holed_system=0;

					}
				}else if(res_match==1){/*password correct*/
					/* Set the Call back function pointer in the timer0 driver */
					Timer_setCallBack(&Display,Timer_1);
					/* Initialize the timer0 Driver */
					Timer_intit(&config_time);
					/*holed system until finish call back function*/
					while(holed_system==0 ){}
					/*clear holed_system for using again*/
					holed_system=0;
				}
			}
			error=0;
			slec_option=0;
		}
		else if(slec_option=='-'){/*user select change password*/
			/* Wait until MC2 is ready to receive the Byte */
			while(UART_recieveByte() != MC1_READY){}
			/* Send the required Byte to MC2 through UART */
			UART_sendByte(slec_option);
			/*looping until enter correct password,only 3 time enter*/
			while(error<3 && res_match==0){
				/*function to take password from user to open door*/
				enter_password(pass);
				/* Wait until MC2 is ready to receive the Byte */
				while(UART_recieveByte() != MC1_READY){}
				/*send password to MC2 ,to check match this password with password stored in EEPROM*/

				for(count=0 ;count<5;count++){
					/* Send the required Byte to MC2 through UART */
					UART_sendByte(pass[count]);
					_delay_ms(60);
				}

				/* Send MC2_READY byte to MC2 to ask it to send the Byte */
				UART_sendByte(MC1_READY);
				/* Receive Byte from MC1 through UART */
				res_match=UART_recieveByte();

				/*if check_match =0 ,password incorrect , if check_match=1 ,password correct */

				if(res_match==0){/*password incorrect*/
					LCD_clearScreen();
					error++;
					if(error<3){
						LCD_displayStringRowColumn(0,0,"error password");
						LCD_displayStringRowColumn(1,0,"enter again");
						_delay_ms(1000);
					}else if(error==3){
						/* Set the Call back function pointer in the timer0 driver */
						Timer_setCallBack(&error_3_password,Timer_1);
						/* Initialize the timer0 Driver */
						Timer_intit(&config_time);
						/*holed system until finish call back function*/
						while(holed_system==0 ){}
						/*clear holed_system for using again*/
						holed_system=0;

					}
				}else if(res_match==1){/*password correct*/
					LCD_displayString("correct password");
					LCD_displayStringRowColumn(1,0,"enter new password");
					_delay_ms(1000);

					/*while match_loin=0 , the two password is not match and ask user again*/
					while(match_login!=1){
						match_login=first_login_password_enter(pass,pass_comp);
						if(match_login==0){/*in case two password not match*/
							LCD_displayStringRowColumn(0,0,"Enter Again");
						}
					}
					/*clear match_login ,so using again*/
					match_login=0;
					/*send password to MC1 to store in EEPROM*/
					for(count=0 ;count<PASSWORD_NUMBER;count++){
						/* Wait until MC2 is ready to receive the Byte */
						while(UART_recieveByte() != MC1_READY){}
						/* Send the required Byte to MC2 through UART */
						UART_sendByte(pass[count]);
						_delay_ms(60);
					}
				}
			}
			error=0;
			slec_option=0;
		}

	}

}
