/*
 * Multimeter.c
 *
 * Created: 9/17/2020 3:36:03 AM
 *  Author: badrm
 */ 
#include <Types.h>
#include <Registers.h>
#include <Macros.h>
#include <Multimeter_Conf.h>
#include <LCD.h>
#include <ADC.h>
#include <Timer0.h>
#include <DIO.h>
u32 result,inVoltage,resistance,CurrentR; u8 reminder,discharged=0,charged=0; u32 capacitance,test=0;
#define __INTR_ATTRS used, externally_visible
/* complete ADC operation using interrupt */
void __vector_16 (void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_16(void){
	result=ADCLow & 0b0000001111111111;
	SetBit(ADCSRA,6);		// start conversion
}
/* this function initiate the multimeter */
void Multimeter_vidInit(){
	ADC_vidInit();
	LCD_vidInit();
	DIO_vidSetPinDirection(ohmeterSwitchesPort,R1_Pin,1);			// 100 ohm
	DIO_vidSetPinDirection(ohmeterSwitchesPort,R2_Pin,1);			// 1K ohm
	DIO_vidSetPinDirection(ohmeterSwitchesPort,R3_Pin,1);			// 10K ohm
	DIO_vidSetPinDirection(ohmeterSwitchesPort,R4_Pin,1);			// 100K ohm
	DIO_vidSetPinDirection(ohmeterSwitchesPort,R5_Pin,1);			// 1M ohm
	LCD_vidWriteString("1.DCV    2.Ohm");
	LCD_vidSetPosition(1,0);
	LCD_vidWriteString("3.DCA    4.farad");
}
/* this function get the applied voltage using voltage divider circuit */
void Multimeter_vidGetVoltage(){
	inVoltage=(result*maxMeasurredVoltage/(ADC_Register));				/* calculate integer number of the applied voltage */
	reminder=(u32)(result*maxMeasurredVoltage*100/(ADC_Register))%100;		/* calculate decimal number (2 places) */
	//resistance=(((inVoltage*100)+reminder)*R1)/((100*maxMeasurredVoltage)-(100*inVoltage+reminder));
		LCD_vidSetPosition(0,0);										/* initiate LCD position */
		LCD_vidWriteNumber(inVoltage);
		LCD_vidWriteString(".");
		if(reminder<10)													/* make 2 decimal places if the reminder < 10 */
			LCD_vidWriteString("0");
		LCD_vidWriteNumber(reminder);
		LCD_vidWriteString("            ");
		LCD_vidSetPosition(1,0);
		LCD_vidWriteString("            Volt");
}
/* this function calculate the current */
void Multimeter_vidGetCurrent(){
	u32 current;
	inVoltage=(result*maxMeasurredVoltage/(ADC_Register));				/* calculate integer number of the applied voltage */
	current=inVoltage/(R1+R2);											/* calculate integer number of the applied current */
	reminder=(u32)((result*maxMeasurredVoltage*100/(ADC_Register))/(R1+R2))%10000;	/* calculate decimal number (2 places) */
	LCD_vidSetPosition(0,0);											/* initiate LCD position */
	if(current>1){														/* current in Amp */
		LCD_vidWriteNumber(current);
		LCD_vidWriteString(".");
		if(reminder<10)													/* make 2 decimal places if the reminder < 10 */
		LCD_vidWriteString("0");
		LCD_vidWriteNumber(reminder);
		LCD_vidWriteString("            ");
		LCD_vidSetPosition(1,0);
		LCD_vidWriteString("            Amp");
	}
	else{																/* current in MicroAmp */
		LCD_vidWriteNumber((result*maxMeasurredVoltage*100/(ADC_Register))*10000/(R1+R2));	/* calculate the current in MicroAmp */
		LCD_vidWriteString("               ");
		LCD_vidSetPosition(1,0);
		LCD_vidWriteString("        MicroAmp");
	}
}
void Multimeter_vidGetCapacitance(){
	if(!discharged){
		DIO_vidSetPinDirection(0,4,1);
		DIO_vidSetPinDirection(0,5,1);			// discharge capacitor
		DIO_vidSetPinValue(0,5,0);
	}
	if(!discharged && result==0) {				// making sure the capacitor is discharged 
		discharged=1;
		DIO_vidSetPinDirection(0,4,0);
		DIO_vidSetPinDirection(0,5,1);			// start charging the capacitor
		DIO_vidSetPinValue(0,5,1);
		Timer0_vid_CTC_Init();					// initializing the timer to calculate time constanct (TC)
	}	
	LCD_vidSetPosition(0,0);
	if( discharged && !charged && ((result) >= 646)){			// 646 = 1024*63/100     
		charged=1;
		LCD_vidWriteNumber(Timer0_u16GetTime()*1000/faradMeterResistor);	// TC=RC
		LCD_vidWriteString("               ");
		LCD_vidSetPosition(1,0);
		LCD_vidWriteString("      MicroFarad");
	}
}
/* this function calculate the resistance using 5 Resistors */
void Multimeter_vidGetOhm(){
	changeResistance(R5_Pin);							// R1=1M
	if(result>=100)
		CurrentR=R_R5;
	else {
		changeResistance(R4_Pin);						// R1=100K
		if(result>=100)
			CurrentR=R_R4;
		else{
			changeResistance(R3_Pin);					// R1=10K
			if(result>=100)
				CurrentR=R_R3;
			else{
				changeResistance(R2_Pin);				// R1=1K
				if(result>=100)
					CurrentR=R_R2;
				else{
					changeResistance(R1_Pin);			// R1=100 
					if(result>=100)
						CurrentR=R_R1;
				}
			}	
		}
	}
	if(result>=950)			/* check if resistor is connected, 950 =1024 - voltage drop due to transistor(.7 V) */
		resistance=0;
	else{
	/* resistance (R2)=Vout*R1 / Vin-Vout */
	/* Vout = ADC_result*(maxMicroInVoltage+transistorDropVoltage)/ADC_Register */
	resistance=(((result*(maxMicroInVoltage+transistorDropVoltage)/ADC_Register))*CurrentR)/(maxMicroInVoltage-((result*(maxMicroInVoltage+transistorDropVoltage)/ADC_Register)));
	}
	LCD_vidSetPosition(0,0);
	/* if the resistance < 1000 show it in Ohm */
	if(resistance<1000){
		LCD_vidWriteNumber(resistance);
		LCD_vidWriteString("                    ");
		LCD_vidSetPosition(1,0);
		LCD_vidWriteString("             Ohm");
	}
	/* if the resistance < 1000000 show it in Kilo Ohm */
	else if(resistance<1000000){
		LCD_vidWriteNumber(resistance/1000);

		LCD_vidWriteString(".");
		if(resistance%1000<10)													/* make 3 decimal places if the reminder < 10 */
		LCD_vidWriteString("0");
		if(resistance%1000<100)													/* make 3 decimal places if the reminder < 100 */
		LCD_vidWriteString("0");
		LCD_vidWriteNumber(resistance%1000);
		LCD_vidWriteString("            ");
		LCD_vidSetPosition(1,0);
		LCD_vidWriteString("           K Ohm");
	}
	/* if the resistance < 1000 show it in Mega Ohm */
	else {
		LCD_vidWriteNumber(resistance/1000000);
		LCD_vidWriteString(".");
		if(resistance%1000000<10)													/* make 3 decimal places if the reminder < 10 */
		LCD_vidWriteString("0");
		if(resistance%1000000<100)													/* make 3 decimal places if the reminder < 100 */
		LCD_vidWriteString("0");
		LCD_vidWriteNumber(resistance%1000000);
		LCD_vidWriteString("            ");
		LCD_vidSetPosition(1,0);
		LCD_vidWriteString("           M Ohm");		
	}
}

/* this function change the resistance (R1) in order to calculate the required Resistance (R2) */
void changeResistance(u8 num){
	switch(num){
		case R1_Pin:
			DIO_vidSetPinValue(ohmeterSwitchesPort,R1_Pin,1);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R2_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R3_Pin,0);			/* activate 100 ohm transistor */
			DIO_vidSetPinValue(ohmeterSwitchesPort,R4_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R5_Pin,0);
			break;
		case R2_Pin:
			DIO_vidSetPinValue(ohmeterSwitchesPort,R1_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R2_Pin,1);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R3_Pin,0);			/* activate 1 K ohm transistor */
			DIO_vidSetPinValue(ohmeterSwitchesPort,R4_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R5_Pin,0);
			break;
		case R3_Pin:
			DIO_vidSetPinValue(ohmeterSwitchesPort,R1_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R2_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R3_Pin,1);			/* activate 10 K ohm transistor */
			DIO_vidSetPinValue(ohmeterSwitchesPort,R4_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R5_Pin,0);
			break;
		case R4_Pin:
			DIO_vidSetPinValue(ohmeterSwitchesPort,R1_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R2_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R3_Pin,0);			/* activate 100 K ohm transistor */
			DIO_vidSetPinValue(ohmeterSwitchesPort,R4_Pin,1);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R5_Pin,0);
			break;
		case R5_Pin:
			DIO_vidSetPinValue(ohmeterSwitchesPort,R1_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R2_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R3_Pin,0);			/* activate 1 M ohm transistor */
			DIO_vidSetPinValue(ohmeterSwitchesPort,R4_Pin,0);
			DIO_vidSetPinValue(ohmeterSwitchesPort,R5_Pin,1);
			break;	
	}
}