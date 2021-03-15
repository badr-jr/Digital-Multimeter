/*
 * DIO.c
 *
 * Created: 9/12/2020 3:26:33 AM
 *  Author: badrm
 */ 
#include "Types.h"
#include "Registers.h"
#include "Macros.h"
void DIO_vidSetPortDirection(u8 portNumber,u8 value){
	switch(portNumber){
		case 0:
		DDRA=value;
		break;
		case 1:
		DDRB=value;
		break;
		case 2:
		DDRC=value;
		break;
		case 3:
		DDRD=value;
		break;
	}
}
void DIO_vidSetPortValue(u8 portNumber,u8 value){
	switch(portNumber){
		case 0:
		PORTA=value;
		break;
		case 1:
		PORTB=value;
		break;
		case 2:
		PORTC=value;
		break;
		case 3:
		PORTD=value;
		break;
	}
}
u8 DIO_u8ReadPortValue(u8 portNumber){
	switch(portNumber){
		case 0:
		return PINA;
		break;
		case 1:
		return PINB;
		break;
		case 2:
		return PINC;
		break;
		case 3:
		return PIND;
		break;
	}
	return 0;
}
void DIO_vidSetPinDirection(u8 portNumber,u8 pin,u8 value){
	switch(portNumber){
		case 0:
		if(value==1)
		SetBit(DDRA,pin);
		else if(value==0)
		ClrBit(DDRA,pin);
		break;
		case 1:
		if(value==1)
		SetBit(DDRB,pin);
		else if(value==0)
		ClrBit(DDRB,pin);
		break;
		case 2:
		if(value==1)
		SetBit(DDRC,pin);
		else if(value==0)
		ClrBit(DDRC,pin);
		break;
		case 3:
		if(value==1)
		SetBit(DDRD,pin);
		else if(value==0)
		ClrBit(DDRD,pin);
		break;
	}
}
void DIO_vidSetPinValue(u8 portNumber,u8 pin,u8 value){
	switch(portNumber){
		case 0:
		if(value==1)
		SetBit(PORTA,pin);
		else if(value==0)
		ClrBit(PORTA,pin);
		break;
		case 1:
		if(value==1)
		SetBit(PORTB,pin);
		else if(value==0)
		ClrBit(PORTB,pin);
		break;
		case 2:
		if(value==1)
		SetBit(PORTC,pin);
		else if(value==0)
		ClrBit(PORTC,pin);
		break;
		case 3:
		if(value==1)
		SetBit(PORTD,pin);
		else if(value==0)
		ClrBit(PORTD,pin);
		break;
	}
}
u8 DIO_u8ReadPinValue(u8 portNumber,u8 pin){
	switch(portNumber){
		case 0:
		return GetBit(PINA,pin);
		break;
		case 1:
		return GetBit(PINB,pin);
		break;
		case 2:
		return GetBit(PINC,pin);
		break;
		case 3:
		return GetBit(PIND,pin);
		break;
	}
	return 0;
}

