ECE382Lab6
==========
Austin Bolinger

Dr. York

ECE 382

18 Nov 14


Description: Lab 6 is IR signals talking to a robot. This builds off of lab 5 where we found a way to use our remote controlls to operate the LCD. Now the remotes will control a robot.


##Prelab

**Hardware Setup**
This is what the set up looks like in picture form.

![set up]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/Setup1.jpg?raw=true "Set Up" )

![MSP430]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/MSP430.JPG?raw=true "MSP430" )

The MSP430 will be hooked up to the voltage driver to take the battery down from 5V to 3.3V. There will be four pins in use. Two for high and two for low on the pulse width modulation. One set of high and low for each motor. The pins can be set and reset in order to control which direction the voltage will flow through the motors.

![Voltage Regulator]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/voltageRegulator.JPG?raw=true "Voltage Regulator" )

Vin is the voltage supply from the batteries. Vout is the power supply, now regulated, going to the MSP430.

![Motor Driver]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/motorDriver.jpg?raw=true "Motor Driver" )

The motor driver is split into two parts. The left side for one motor and the right side for the other motor. All GND will be grounded. M1&2 Enable are the Power from 5V. 5V and Motor power in pins are connected. Input power and ground on one side will correspond with P1.4 & P1.5 and on the other side correspond with P2.0 & P2.1. Output power and ground on one side will correspond with the motors power and ground respectively.

**Software Setup**

![Flow Chart]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/flowchart.JPG?raw=true "Flow Chart" )

##Documentation
I used the robot in the lab to understand what each hardware piece was to do. I looked up the images online and added my own words to them.
