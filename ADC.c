/*
 * ADC.c
 *
 * Created: 9/15/2020 7:43:38 AM
 *  Author: badrm
 */ 
#include <ADC.h>
#include <Types.h>
#include <Registers.h>
#include <Macros.h>
	void ADC_vidInit(void){
		ClrBit(ADMUX,0);
		ClrBit(ADMUX,1);
		ClrBit(ADMUX,2);		// single conversion channel 0
		ClrBit(ADMUX,3);
		ClrBit(ADMUX,4);

		ClrBit(ADMUX,6);		// AREF internal
		ClrBit(ADMUX,7);

		ClrBit(ADMUX,5);		// Right Adjustment

		ClrBit(ADCSRA,0);
		ClrBit(ADCSRA,1);		// prescaler 128
		ClrBit(ADCSRA,2);

		SetBit(ADCSRA,3);      // enable ADC interrupt

		SetBit(ADCSRA,7);		// enable ADC

		SetBit(SREG,7);			// enable global interrupt

		SetBit(ADCSRA,6);		// start conversion
	}

