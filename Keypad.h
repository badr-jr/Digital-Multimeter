/*
 * Keypad.h
 *
 * Created: 9/15/2020 7:17:38 AM
 *  Author: badrm
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


#define Pressed 1
#define notPressed 0
u8 Keypad_u8SetButtonStatus(u8 ButtonNo);
void Keypad_vidInit(void);
u8 Keypad_u8GetKeyNumber();


#endif /* KEYPAD_H_ */