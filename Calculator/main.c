/*
 * GateEntry.c
 *
 * Created: 8/6/2023 4:49:01 PM
 * Author : Mohamed
 */ 

#define  F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "STD_Macros.h"
#include "LCD.h"
#include "Keypad.h"
#include "General_Functions.h"

int main(void)
{
	Keypad_INIT();
	LCD_INIT();
	char c;					//To take input from the keypad
	char SwOp = 0;			//To see if I'm writing on the first or second operand
	int x = 0;
	int y = 0;
	char op = 0;	
    while (1) 
    {
		SwOp = 0, op = 0;
		x = 0, y = 0;
		do
		{
			c = getkey();
			while (c == '\0')
			{ c = getkey(); }
			LCD_send_data(c);
			_delay_us(100);
			if (c<'0' || c>'9')
			{
				if (c == '=')
				{ continue; }
				else
				{
					op = c;
					SwOp = 1;
				}
			}
			else
			{
				if (SwOp == 0)
				{
					c = c -'0';
					x = x*10 + c;
				}
				else
				{
					c = c -'0';
					y = y*10 + c;
				}
			}
		} while(c != '=');
		Calculator(x,y,op);
		_delay_ms(2000);
		LCD_ClearScreen();
    }
}

