/*
 * General_Functions.c
 *
 * Created: 7/31/2023 9:12:30 PM
 *  Author: Mohamed
 */ 

#include "General_Functions.h"
#include "LCD.h"

char Is_Same_String(char arr[], char arr2[])
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (arr[i] != arr2[i])
		{
			return 0;
		}
	}
	return 1;
}

void Calculator(int op1, int op2, char operator)
{
	int result = 0;
	switch(operator)
	{
		case '+':
			result = op1 + op2;
			break;
		case '-':
			result = op1 - op2;
			break;
		case '*':
			result = op1 * op2;
			break;
		case '/':
			result = op1 / op2;
			break;
	}
	LCD_Integer(result);
}