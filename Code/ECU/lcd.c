/*
 * lcd.c
 *
 *      Author: nader essam ali
 */
#include <util/delay.h> /* For the delay functions */
#include "commen_macros.h" /* To use the macros like SET_BIT */
#include "lcd.h"
#include "gpio.h"

void LCD_init(void)
{
	/* Configure the direction for RS, RW and E pins as output pins */
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);

	/* Configure the data port as output port */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */

	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_sendCommand(uint8 command){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
}
void LCD_displayCharacter(uint8 data){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT_ID,data);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
}
/*
 * Description:
 * function display required string
 */
void LCD_displayString(const char *Str){
	uint8 count=0;
	while(Str[count]!='\0'){
		LCD_displayCharacter(Str[count]);
		count++;
	}
}
/*
 * Description:
 * move cursor in specific position
 */
void LCD_moveCursor(uint8 row,uint8 col){
	uint8 lcd_memory_adress;
	switch(row){
	case 0:
		lcd_memory_adress=col;
		break;
	case 1:
		lcd_memory_adress=col+0x040;
		break;
	case 2:
		lcd_memory_adress=col+0x10;
		break;
	case 3:
		lcd_memory_adress=col+0x50;
		break;
	}
	/*move cursor*/
	LCD_sendCommand(lcd_memory_adress|LCD_SET_CURSOR_LOCATION);
}
/*
 * Description:
 * display required string in required row and column index
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str){
	LCD_moveCursor(row,col);
	LCD_displayString(Str);
}
/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}
/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

