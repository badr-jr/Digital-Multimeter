/*
 * Timer0.c
 *
 * Created: 9/19/2020 6:56:17 AM
 *  Author: badrm
 */ 
#include <Registers.h>
#include <Macros.h>
#include <Timer0.h>
#include <Types.h>
u16 milliSeconds;
#define __INTR_ATTRS used, externally_visible
void __vector_10(void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_10(void){
	milliSeconds++;
	//LCD_vidWriteString("hi");
}

void Timer0_vid_CTC_Init(){
	SetBit(TCCR0,7);  /* non PWM Mode */
	
	ClrBit(TCCR0,6);  /*CTC Mode */
	SetBit(TCCR0,3);
	
	SetBit(TCCR0,0);
	SetBit(TCCR0,1);  /* prescaler 64 */
	ClrBit(TCCR0,2);
	
	
	
	SetBit(TIMSK,1);  /* enable CTC interrupt */
	
	OCR0=124;		  /* top value */
	
	SetBit(SREG,7);   /* enable global interrupt */
}

u32 Timer0_u16GetTime(){
	return milliSeconds;
}