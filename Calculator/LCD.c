/*
 * LCD.c
 *
 * Created: 4/14/2023 3:52:28 PM
 *  Author: Mohamed
 */ 


// RW: CLEAR RW yba WRITE, SET RW yba READ
// RS:

#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "LCD.h"



void LCD_send_command(char cmd)
{
	PORTA = (cmd & 0xf0) | (PORTA & 0x0f);
	CLEARBIT(PORTB,1);							//Set RS to Send Data
	CLEARBIT(PORTB,2);							//Clear RW to write
	SETBIT(PORTB,EN_PIN);							//Set EN
	_delay_us(1);
	CLEARBIT(PORTB,EN_PIN);							//Clear EN
	_delay_us(200);
	PORTA = (cmd << 4) | (PORTA & 0x0f);
	SETBIT(PORTB,EN_PIN);
	_delay_us(1);
	CLEARBIT(PORTB,EN_PIN);
	_delay_ms(10);
	
}

void LCD_send_data(char cmd)
{
	PORTA = (cmd & 0xf0) | (PORTA & 0x0f);
	SETBIT(PORTB, 1);							//Set RS to Send Data
	CLEARBIT(PORTB, 2);							//Clear RW to write
	SETBIT(PORTB, EN_PIN);							//Set EN
	_delay_us(1);
	CLEARBIT(PORTB, EN_PIN);							//Clear EN
	_delay_us(200);
	PORTA = (cmd << 4) | (PORTA & 0x0f);
	SETBIT(PORTB, EN_PIN);
	_delay_us(1);
	CLEARBIT(PORTB, EN_PIN);
	_delay_ms(10);
}


void LCD_INIT()
{
	DDRA |= 0xf0;
	SETBIT(DDRB,1);		//SET RS
	SETBIT(DDRB,2);		//SET RW
	SETBIT(DDRB,EN_PIN);		//SET EN
	LCD_send_command(0x02);
	LCD_send_command(0x28);
	LCD_send_command(0x0c);
	LCD_send_command(0X06);
	LCD_send_command(0X01);
	_delay_ms(10);
	
}
void LCD_Integer(int x)
{
	int i = 0;
	int length = 0;
	char a[10];
	while (x != 0)
	{
		a[length] = x%10 + '0';
		x = x / 10;
		length++;
	}
	for (i = length-1; i >= 0; i--)
	{
		LCD_send_data(a[i]);
	}
}

void LCD_String(char arr[])
{
	int c = 0;
	while(arr[c] != 0)
	{
		LCD_send_data(arr[c]);
		c++;
	}
}

void LCD_ClearScreen()
{
	LCD_send_command(0x01);
}