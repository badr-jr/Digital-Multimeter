/*
 * Keypad.c
 *
 * Created: 9/15/2020 7:08:55 AM
 *  Author: badrm
 */ 
#include "Types.h"
#include "Keypad_Conf.h"
#include "Keypad.h"
#include "DIO.h"
#include <util/delay.h>
#define F_CPU 8000000
u8 flag[16]={0},i;
void Keypad_vidInit(){
	DIO_vidSetPinDirection(KeybadPort,R1,0);
	DIO_vidSetPinDirection(KeybadPort,R2,0);
	DIO_vidSetPinDirection(KeybadPort,R3,0);
	DIO_vidSetPinDirection(KeybadPort,R4,0);
	DIO_vidSetPinDirection(KeybadPort,C1,1);
	DIO_vidSetPinDirection(KeybadPort,C2,1);
	DIO_vidSetPinDirection(KeybadPort,C3,1);
	DIO_vidSetPinDirection(KeybadPort,C4,1);
	DIO_vidSetPinValue(KeybadPort,R1,1);
	DIO_vidSetPinValue(KeybadPort,R2,1);
	DIO_vidSetPinValue(KeybadPort,R3,1);
	DIO_vidSetPinValue(KeybadPort,R4,1);
}

u8 Keypad_u8SetButtonStatus(u8 ButtonNo){
	u8 status=0;
	u8 realCol[]={C1,C2,C3,C4};
	u8 realRow[]={R1,R2,R3,R4};
	u8 row=ButtonNo/4;
	u8 col=ButtonNo%4;

	DIO_vidSetPinValue(KeybadPort,C1,1);
	DIO_vidSetPinValue(KeybadPort,C2,1);
	DIO_vidSetPinValue(KeybadPort,C3,1);
	DIO_vidSetPinValue(KeybadPort,C4,1);
	DIO_vidSetPinValue(KeybadPort,realCol[col],0);
	u8 value=DIO_u8ReadPinValue(KeybadPort,realRow[row]);
	if(value==0){
		_delay_ms(5);
		value=DIO_u8ReadPinValue(KeybadPort,realRow[row]);
		if(value==0 && flag[ButtonNo]==0){
			status=Pressed;
			flag[ButtonNo]=1;
		}
	}
	else if(value==1){
		flag[ButtonNo]=0;
	}
	return status;
}

u8 Keypad_u8GetKeyNumber(){
	for(i=0;i<5;i++){
		if(Keypad_u8SetButtonStatus(i)==1){
			return i;
			break;
		}
	}
	return 4;
}