/*
 * Multimeter.h
 *
 * Created: 9/17/2020 3:47:07 AM
 *  Author: badrm
 */ 


#ifndef MULTIMETER_H_
#define MULTIMETER_H_
void Multimeter_vidInit();
void Multimeter_vidGetVoltage();
void Multimeter_vidGetCurrent();
void Multimeter_vidGetCapacitance();
void Multimeter_vidGetOhm();
enum{
	DCV,
	Ohm,
	DCA,
	Farad,
};
#define noChoice 4

#endif /* MULTIMETER_H_ */