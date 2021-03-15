/*
 * rememb.c
 *
 * Created: 9/12/2020 2:33:45 AM
 * Author : badrm
 */ 


#include <util/delay.h>
#define F_CPU 8000000
#include <Types.h>
#include <Multimeter.h>
#include <Keypad.h>
#include <LCD.h>
#include <Timer0.h>
int main(void)
{	u8 keyNumber=noChoice;
	Multimeter_vidInit();
	Keypad_vidInit();
	while (1)
	{	if(keyNumber==noChoice)
			keyNumber=Keypad_u8GetKeyNumber();
		
		switch(keyNumber){
			case DCV:
				DIO_vidSetPinDirection(0,4,0);
				DIO_vidSetPinDirection(0,5,1);			// start charging the capacitor
				DIO_vidSetPinValue(0,5,1);
				Multimeter_vidGetVoltage();
				break;
			case DCA:
				Multimeter_vidGetCurrent();
				break;
			case Farad:
				Multimeter_vidGetCapacitance();
				break;
			case Ohm:
				Multimeter_vidGetOhm();
				break;
		
		
		
	}
	
}
}



