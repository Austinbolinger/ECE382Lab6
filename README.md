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

![IR Sensor]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/IRSensor.JPG?raw=true "IR Sensor" )

The IR Sensor will hook up to the MSP430 ground, 3.3V, and Xin pin for input.

![Voltage Regulator]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/voltageRegulator.JPG?raw=true "Voltage Regulator" )

Vin is the voltage supply from the batteries. Vout is the power supply, now regulated, going to the MSP430.

![Motor Driver]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/motorDriver.jpg?raw=true "Motor Driver" )

The motor driver is split into two parts. The left side for one motor and the right side for the other motor. All GND will be grounded. M1&2 Enable are the Power from 5V. 5V and Motor power in pins are connected. Input power and ground on one side will correspond with P1.4 & P1.5 and on the other side correspond with P2.0 & P2.1. Output power and ground on one side will correspond with the motors power and ground respectively.

**Software Setup**

![Flow Chart]( https://github.com/Austinbolinger/ECE382Lab6/blob/master/flowchart.JPG?raw=true "Flow Chart" )



**Lab**
#Robot
I hooked the robot up similar to my design above. I changed the use of pins for the PWM and GPIO because of something I will later discuss. I also added capacitors as suggested. I added capacitors between ground and power between the 5V and 12V and between all power signals to ground on the motor driver. I changed my MSP430 pins to port2 pins 2 and 4 as PWM and pins 1 and 5 for GPIOs. This was because of the need for different clocks. Also, several people in the lab suggested these pins for PWM because they could not get port 1's pins to work well. Neither could I.

##Functionality
The functionality is to have a robot preform a set operation without remote control and while not plugged into the USB. PWM drives the motors. It is up to the me w=to tell when the motors need to be active. I will use different lengths of delays to tell my program to continue operating as it is set in order to perform certain turns. The turns will be performed in tank style turns (one wheel forward and the other one backwards.]
code found here 
https://github.com/Austinbolinger/ECE382Lab6/blob/master/Lab6Required

##A Functionality
The A functionality is to perform operations as given by the remote control while not plugged into the USB. This is the same as functionality but it adds in the remote control from lab 5.
code found here (most comments found here)
https://github.com/Austinbolinger/ECE382Lab6/blob/master/Lab6pre

##Debugging Functionality
To start off I tried to always have the PWM on and just change when the motors were active by the output mode. In order to code, I used the coding style from lesson 32's powerpoint. The key to take away from that style was to use two different clocks, one for each motor. After 30 minutes of coding, I was ready to go. I hooked up the robot and tested my code. I could found that it worked but one wheel always spun way to fast. I decided after talking to other classmates that it was the problem of the use of wrong pins on the MSP430. I switched methods and used different pins. 

My new method was changing the direction of the pins in combination with the output mode. Using this method, I made functions for each motor's forwards and backwards. I selected the PWM pin to move in output direction. I selected the GPIO to be grounded low for forward movement and the outout mode to be reset/set or mode 7. This moved the motors forward. To move back, I selected the PWM to be output direction, the GPIOs to be grounded high, and the output mode as set/reset or out 5. My next coding was to make functions like forward which combined left motor forward with right motor forward and a delay time. I made methods for forward, backward, and left/right turns at 45/90/135 degrees. The turns were made by using different delay times. I added in a stop function for clearing the PWMs from the motors so that I could stop if I wanted to and to make demonstrating easier. The stop function just turned my PWM pins around, switched directions, and made the GPIOs off.

##Debugging A Functionality
This code did not take 12 hours like the required functionality. It only took about 10 minutes. I just added in the from lab 5. This added interrupts to sense my button presses. Each button on the number pad would be recognized and perform a set motor function. I made sure to not allow button presses to interrupt an operation by turning off interrupts in my new code. I tried adding a charge or speed change function. But, my robot does not like to change its speed from 50% PWM. I assume this is because the 50% works because it does not draw too much current. My robot is slow, but it works just fine.

##Documentation
I used the robot in the lab to understand what each hardware piece was to do. I looked up the images online and added my own words to them.

I worked a lot with C2C Wooden. together we trouble shot eachother's programs to try and figure out where are programs were messing up at within the program. We were able to help eachother figure out how to make the new pins work for eachother's robots.
