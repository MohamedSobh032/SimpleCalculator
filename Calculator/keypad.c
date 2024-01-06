/*
 * Keypad.c
 *
 * Created: 4/29/2023 2:02:40 PM
 *  Author: Mohamed
 */ 


#define  F_CPU 1000000ul
#include <avr/io.h>
#include "STD_Macros.h"
#include "Keypad.h"
#include "LCD.h"
#include <util/delay.h>
#include "General_Functions.h"

void Keypad_INIT()  /*Can change port and DDR*/
{
	DDRC=0x0f;			// DDRC most significant 4 bits are input and least significant 4 bits are output
	PORTC = 0xff;
}

char getkey()  
{
	char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','=','+'}};  /*Change configuration as keypad is set*/
	
	//char arr[4][4]={{'1','4','7','c'},{'2','5','8','0'},{'3','6','9','='},{'/','*','-','+'}};
	char key =0 ;
	for(int i=0;i<4;i++)
	{
		CLEARBIT(PORTC,i);
		for(int j=4;j<8;j++)
		{
			if(READBIT(PINC,j)==0)
			{
				while(READBIT(PINC,j)==0){;}
				key = arr[i][j-4];
				break;
			}
		}
		if (key != 0)
		{
			break;
		}
		_delay_us(20);
		SETBIT(PORTC,i);
	}
	return key;
}

