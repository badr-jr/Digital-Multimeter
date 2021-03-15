/*
 * Macros.h
 *
 * Created: 9/12/2020 2:35:42 AM
 *  Author: badrm
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define SetBit(reg,bit) reg|=(1<<bit)
#define ClrBit(reg,bit) reg&=~(1<<bit)
#define ToggleBit(reg,bit) reg^=(1<<bit)
#define GetBit(reg,bit) ((reg>>bit)&1)



#endif /* MACROS_H_ */