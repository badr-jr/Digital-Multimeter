/*
 * Multimeter_Conf.h
 *
 * Created: 9/17/2020 3:43:40 AM
 *  Author: badrm
 */ 


#ifndef MULTIMETER_CONF_H_
#define MULTIMETER_CONF_H_

#define R1 10000
#define R2 5000
#define R_R1 100
#define R_R2 1000
#define R_R3 10000
#define R_R4 100000
#define R_R5 1000000
#define maxMicroInVoltage 4.85
#define dropVoltageFactor (R1+R2)/R2
#define maxMeasurredVoltage maxMicroInVoltage*dropVoltageFactor
#define ADC_Register 1024
#define faradMeterResistor 10000
#define transistorDropVoltage .7
#define ohmeterSwitchesPort 2
#define R1_Pin 0
#define R2_Pin 1
#define R3_Pin 2
#define R4_Pin 3
#define R5_Pin 4

#endif /* MULTIMETER_CONF_H_ */