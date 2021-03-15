/*
 * LCD.c
 *
 * Created: 9/14/2020 3:15:11 AM
 *  Author: badrm
 */ 
#include "Types.h"
#include "LCD.h"
#include "DIO.h"
#include "LCD_Conf.h"
#include "Macros.h"
#include <util/delay.h>
#define F_CPU 8000000


void LCD_vidInit(void){
	DIO_vidSetPortDirection(LCD_DataPort,255);
	DIO_vidSetPinDirection(LCD_ControlPort,RS,1);
	DIO_vidSetPinDirection(LCD_ControlPort,RW,1);
	DIO_vidSetPinDirection(LCD_ControlPort,E,1);
	_delay_ms(50);
	LCD_vidWriteCommand(0b00111000);
	_delay_ms(1);
	LCD_vidWriteCommand(0b00001100);
	_delay_ms(2);
	LCD_vidWriteCommand(0b00000001);
}
void LCD_vidWriteData(u8 data){
	DIO_vidSetPinValue(LCD_ControlPort,RS,1);
	DIO_vidSetPinValue(LCD_ControlPort,RW,0);
	DIO_vidSetPortValue(LCD_DataPort,data);
	DIO_vidSetPinValue(LCD_ControlPort,E,1);
	_delay_ms(3);
	DIO_vidSetPinValue(LCD_ControlPort,E,0);
	_delay_ms(1);
}
void LCD_vidWriteCommand(u8 command){
	DIO_vidSetPinValue(LCD_ControlPort,RS,0);
	DIO_vidSetPinValue(LCD_ControlPort,RW,0);
	DIO_vidSetPortValue(LCD_DataPort,command);
	DIO_vidSetPinValue(LCD_ControlPort,E,1);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_ControlPort,E,0);
	_delay_ms(10);
}

void LCD_vidWriteString(u8 str[]){
	u8 i=0;
	while(str[i]!=0){
		LCD_vidWriteData(str[i]);
		i++;
	}

}
void LCD_vidWriteNumber(s32 num){
	u8 result[10]; s8 i=-1;
	do{
		i++;
		result[i]=((num%10)+48);
		num/=10;
	}
	while(num!=0);
	while(i>=0){
		LCD_vidWriteData(result[i]);
		i--;
	}

}

void LCD_vidSetPosition(u8 row,u8 col){
	LCD_vidWriteCommand(0b10000000+(row*64)+col);
}
