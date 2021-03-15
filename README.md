# Digital Mulitmeter - AVR32

This digital multimeter can be used as: 
- DC Voltmeter.
- DC Ammeter.
- Ohmmeter.
- Capacitance Meter.

The whole project is represented in hardware (Atmega32 based).

[View demo video.](https://youtu.be/gX1puoKukP4)

<img src="https://user-images.githubusercontent.com/74314248/111159946-4bedbd80-85a2-11eb-93a3-3004398506ee.JPG" width="40%" height="40%">
<img src="https://user-images.githubusercontent.com/74314248/111160234-93744980-85a2-11eb-821b-a394a313b63d.JPG" width="40%" height="40%">
<img src="https://user-images.githubusercontent.com/74314248/111160374-b272db80-85a2-11eb-8a36-7b391589b428.JPG" width="40%" height="40%">
<img src="https://user-images.githubusercontent.com/74314248/111160089-70499a00-85a2-11eb-805d-48aa00d76721.JPG" width="40%" height="40%">


## Components Required
- Power supply.
- Atmega32 microcontroller which is used here.
- LCD to display the output.
- Voltage divider circuit to divide measured voltage.
- 220Ω resistor for measring capacitance and some other resistors for the rest of project.
- 5 transistors for measuring resistance.
## Getting Started
All configurations can be adjusted using **Multimeter_conf.h** file in order to control the measured values limits.

Voltage divider circuit is used to reduce the magnitude of a voltage.

![IMG](https://www.allaboutcircuits.com/uploads/thumbnails/voltage-divider-main-circuit.png)

5 resistors is used to control limits of measureing resistance values (low values and high values).

![IMG](https://engineerzero.files.wordpress.com/2012/12/resisty1.png?w=640&h=487)

Resistance can be measured in 3 different units(Ohm, Kilo, Mega) based on its value.

Circuit needed to measure capacitance.

![IMG](https://www.arduino.cc/wiki/static/916fab0013be4fc4b2268e128ec4fc02/6db71/CapacitanceMeterSchem.png)

## Software Used
- Atmel Studio 7.0

## Skills Needed
- Experience with C language.
- Good interacting with AVR microcontrollers.
- Understanding of some circuits topics (e.g voltage divider circuit) and other circuits generally.
