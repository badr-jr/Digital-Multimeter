/*
 * Registers.h
 *
 * Created: 9/12/2020 3:28:55 AM
 *  Author: badrm
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_


#define DDRA *((volatile u8*)0x3A)
#define PORTA *((volatile u8*)0x3B)
#define PINA *((volatile u8*)0x39)
#define DDRB *((volatile u8*)0x37)
#define PORTB *((volatile u8*)0x38)
#define PINB *((volatile u8*)0x36)
#define DDRC *((volatile u8*)0x34)
#define PORTC *((volatile u8*)0x35)
#define PINC *((volatile u8*)0x33)
#define DDRD *((volatile u8*)0x31)
#define PORTD *((volatile u8*)0x32)
#define PIND *((volatile u8*)0x30)
#define SREG *((volatile u8*)0x5F)
#define MCUCR *((volatile u8*)0x55)
#define GICR *((volatile u8*)0x5B)
#define TCCR0 *((volatile u8*)0x53)
#define TIMSK *((volatile u8*)0x59)
#define OCR0 *((volatile u8*)0x5C)
#define TCCR1A *((volatile u8*)0x4F)
#define TCCR1B *((volatile u8*)0x4E)
#define TCCR2 *((volatile u8*)0x45)
#define TIFR *((volatile u8*)0x58)
#define ICR1 *((volatile u16*)0x46)
#define OCR1 *((volatile u16*)0x4A)
#define ADMUX *((volatile u8*)0x27)
#define ADCSRA *((volatile u8*)0x26)
#define ADCLow *((volatile u16*)0x24)
#define UCSRC_UBRRH *((volatile u8*)0x40)
#define UCSRB *((volatile u8*)0x2A)
#define UCSRA *((volatile u8*)0x2B)
#define UDR *((volatile u8*)0x2C)
#define UBRRL *((volatile u8*)0x29)
#define WDTCR *((volatile u8*)0x41)
#define SPCR *((volatile u8*)0x2D)
#define SPSR *((volatile u8*)0x2E)
#define SPDR *((volatile u8*)0x2F)
#define TWBR *((volatile u8*)0x20)
#define TWCR *((volatile u8*)0x56)
#define TWSR *((volatile u8*)0x21)
#define TWDR *((volatile u8*)0x23)
#define TWAR *((volatile u8*)0x22)


#endif /* REGISTERS_H_ */