/*
 * main_MC2.c
 *      Author:nader essam ali
 */

#include "application.h"

uint8 pass[PASSWORD_NUMBER];/*array of 5 element ,use to store password in EEPROM*/
uint8 pass_comp[PASSWORD_NUMBER];/*array of 5 element ,use as a compare password with stored in EEPROM*/
extern uint8 holed_system;

int main(void){

	/*local variable*/
	uint8 count,option,res_match,error=0;
	uint8 condition;
	/* Enable Global Interrupt I-Bit */
	SREG=(1<<7);

	/* Initialize the EEPROM Driver */
	EEPROM_intit();
	/*
	 * Create configuration structure for timer1 driver
	 * this configuration make interrupt every 1 second
	 */
	Timer_ConfigType config_time={0,7813,Timer_1,F_CPU_CLOCK_1024,Compare};
	/* Initialize the BUZZER Driver */
	BUZZER_intit();
	/* Initialize the DcMotor Driver */
	DcMotor_Init();
	/* Create configuration structure for URT driver */
	Uart_ConfigType config={STOP_BIT_1,BIT_8,DISABLED};
	/* Initialize the URT Driver */
	UART_init(&config);

/*
    //write on first address 0xff
	EEPROM_writeByte(0x0000, 0xff);
	_delay_ms(50);
*/
	/*read first address on EEPROM*/
	EEPROM_readByte(0x0000, &condition);

	/* Wait until MC2 is ready to receive the Byte */
	while(UART_recieveByte() != MC1_READY){}
	/* Send the required Byte to MC2 through UART */
	UART_sendByte(condition);

	/*at first ,check if 0xff store in EEPROM ,so no password store in EEPROM
 and ask user to enter password for system */
	if(condition==0xff){/*no password store in EEPROM*/
		/*Recieve password from MC1 ,and store password in EEPROM*/
		for(count=0 ;count<PASSWORD_NUMBER;count++){
			/* Send MC2_READY byte to MC2 to ask it to send the Byte */
			UART_sendByte(MC1_READY);
			/* Receive Byte from MC1 through UART*/
			pass[count]=UART_recieveByte();
			/*store Byte Byte in EEPROM*/
			EEPROM_writeByte(0x0000|count, pass[count]);
			/*delay for store anthor Byte*/
			_delay_ms(60);
		}
	}

	while(1){

		/* Send MC2_READY byte to MC2 to ask it to send the Byte */
		UART_sendByte(MC1_READY);
		/* Receive Byte from MC1 through UA*/
		option=UART_recieveByte();
		/*option must be = '+' or '-'
		 * '+':open door
		 * '-':change password
		 */
		/*clear res_match as default ,
		 * when res_match = 1 ,the enter password from user is equal the password in EEPROM
		 * when res_match = 0 ,the enter password from user is not equal the password in EEPROM
		 */
		res_match=0;
		if(option=='+'){/*open door*/
			/*looping until enter correct password,only 3 time enter*/
			while(error<3&&res_match==0){
				/* Send MC2_READY byte to MC2 to ask it to send the Byte */
				UART_sendByte(MC1_READY);
				/*recieve password from MC1*/
				for(count=0 ;count<PASSWORD_NUMBER;count++){
					/* Receive Byte from MC1 through UA*/
					/*store Byte first at array (pass_comp)*/
					pass_comp[count]=UART_recieveByte();
					_delay_ms(60);
				}
				/*read from EEPROM the store password ,and store it at array (pass)*/
				for(count=0;count<PASSWORD_NUMBER;count++){
					/*Recieve password from EEPROM*/
					EEPROM_readByte(0x0000|count, &pass[count]);
					_delay_ms(60);
				}
				/*compare two password and send result to MC1
				 * if res_match =0 the two password not equal
				 * if res_match =1 the two password equal
				 */
				res_match=chech_match_password(pass,pass_comp);
				/* Wait until MC2 is ready to receive the Byte */
				while(UART_recieveByte() != MC1_READY){}
				/* Send the required Byte to MC2 through UART */
				UART_sendByte(res_match);
				if(res_match==0){/*if  password in correct*/
					error++;
					if(error<3){
						/*Do Nothing*/
					}else if(error==3){
						/* Set the Call back function pointer in the timer0 driver */
						Timer_setCallBack(&BUZZER_turnOn,Timer_1);
						/* Initialize the timer0 Driver */
						Timer_intit(&config_time);
						/*holed system until finish call back function*/
						while(holed_system==0){}
						/*clear holed_system for using again*/
						holed_system=0;
					}

				}else if(res_match==1){/*password correct*/

					/* Set the Call back function pointer in the timer0 driver */
					Timer_setCallBack(&open_door,Timer_1);
					/* Initialize the timer0 Driver */
					Timer_intit(&config_time);
					/*holed system until finish call back function*/
					while(holed_system==0){}
					/*clear holed_system for using again*/
					holed_system=0;
				}
			}
			error=0;
		}
		else if(option=='-'){/*change password*/
			/*looping until enter correct password,only 3 time enter*/
			while(error<3&&res_match==0){
				/* Send MC2_READY byte to MC2 to ask it to send the Byte */
				UART_sendByte(MC1_READY);
				/*Recieve password from MC1*/
				for(count=0 ;count<PASSWORD_NUMBER;count++){
					/* Receive Byte from MC1 through UA*/
					/*store Byte first at array (pass_comp)*/
					pass_comp[count]=UART_recieveByte();
					_delay_ms(60);
				}
				/*read from EEPROM the store password ,and store it at array (pass)*/
				for(count=0;count<PASSWORD_NUMBER;count++){
					/*Recieve password from EEPROM*/
					EEPROM_readByte(0x0000|count, &pass[count]);
					_delay_ms(60);
				}
				/*compare two password and send result to MC1
				 * if res_match =0 the two password not equal
				 * if res_match =1 the two password equal
				 */
				res_match=chech_match_password(pass,pass_comp);
				/* Wait until MC2 is ready to receive the Byte */
				while(UART_recieveByte() != MC1_READY){}
				/* Send the required Byte to MC2 through UART */
				UART_sendByte(res_match);
				if(res_match==0){/*if  password in correct*/
					error++;
					if(error<3){
						/*Do Nothing*/

					}else if(error==3){
						/* Set the Call back function pointer in the timer1 driver */
						Timer_setCallBack(&BUZZER_turnOn,Timer_1);
						/* Initialize the timer1 Driver */
						Timer_intit(&config_time);
						/*holed system until finish call back function*/
						while(holed_system==0){}
						/*clear holed_system for using again*/
						holed_system=0;

					}

				}else if(res_match==1){/*password correct*/
					/*Receive password from MC1 ,and store password in EEPROM*/
					for(count=0 ;count<PASSWORD_NUMBER;count++){
						/* Send MC2_READY byte to MC2 to ask it to send the Byte */
						UART_sendByte(MC1_READY);
						/* Receive Byte from MC1 through UART*/
						pass[count]=UART_recieveByte();
						/*store Byte Byte in EEPROM*/
						EEPROM_writeByte(0x0000|count, pass[count]);
						/*delay to store byte*/
						_delay_ms(60);
					}
				}

			}
			error=0;
		}

	}
}

