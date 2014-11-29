#include <msp430.h> 
#include "start5.h"

int32 irpacket = 0;
int32 packetIndex = 0;
int16 packetData[32];
int8 codeMatches = 0;
int8 newIrPacket = FALSE;
int speed = 50;
int SPD = 50;

/*
 * main.c
 */
#include <msp430.h>
#include "start5.h"

/*
 * main.c
 */
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;       // stop the watchdog timer

	initMSP430();

	while (1) {
		if (newIrPacket) {       //new packet means new insturction from remote
			_disable_interrupt();
			unsigned int i = 0;
			irpacket = 0;

			do {
				irpacket += packetData[i];       //convert array to int
				if (i == 31) {

				} else {
					irpacket <<= 1;
				}
				i++;
			} while (i < 32);

			if (irpacket == PWR) {
				codeMatches = 10;
				stop();
			} else if (irpacket == ZERO) {          //spin
				codeMatches = 0;
				spin();
			} else if (irpacket == ONE) {            //left 45
				codeMatches = 1;
				turnLeft45();
			} else if (irpacket == TWO) {            //forward
				codeMatches = 2;
				forward();
			} else if (irpacket == THR) {            //right 45
				codeMatches = 3;
				turnRight45();
			} else if (irpacket == FOR) {          //left 90
				codeMatches = 4;
				turnLeft90();
			} else if (irpacket == FVE) {            //
				codeMatches = 5;
				charge();
			} else if (irpacket == SIX) {            //right 90
				codeMatches = 6;
				turnRight90();
			} else if (irpacket == SVN) {            //left 135
				codeMatches = 7;
				turnLeft135();
			} else if (irpacket == EGT) {            //backward
				codeMatches = 8;
				backward();
			} else if (irpacket == NNE) {            //right 135
				codeMatches = 9;
				turnRight135();
			} else if (irpacket == VOL_UP) {         //change speed+
				codeMatches = 11;
			} else if (irpacket == VOL_DW) {         //change speed-
				codeMatches = 12;
			} else if (irpacket == CH_UP) {			//change delay time +
				codeMatches = 13;
			} else if (irpacket == CH_DW) {			//change delay time -
				codeMatches = 14;
			}
			newIrPacket = FALSE;
			initMSP430();

			//wait time
			unsigned int j;
			for (j = 0; j < 65000; j++)
				;

			_enable_interrupt();
			packetIndex = 0;
			irpacket = 0;

		}                //end of flag if loop
	} //end while
} //end main

void stop() { //stop the PWMs
	P2DIR &= ~(BIT4 | BIT2);                // TA1CCR1 on P2.4 reversed

	P2DIR &= ~(BIT1 | BIT5);
	P2OUT &= ~(BIT1 | BIT5);					// P2.1&5 = GND

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1
}

void LF() {                //left motor forward
	P2DIR |= BIT4;                // TA1CCR1 on P2.4
	P2SEL |= BIT4;

	P2DIR |= BIT1;
	P2OUT &= ~BIT1;					// P2.1 = GND low

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	TA1CTL |= TASSEL1;           // configure for SMCLK

	TA1CCR0 = 100;  // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR2 = speed;  //50% MODULATION

	TA1CCTL2 |= OUTMOD_7;        // set TACCTL2 to Reset / Set mode

	TA1CTL |= MC0;                // count up
}

void RF() {                //right motor forward
	P2DIR |= BIT2;                // TA1CCR1 on P2.2
	P2SEL |= BIT2;

	P2DIR |= BIT5;
	P2OUT &= ~BIT5;					// P2.5 = GND low

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	TA1CTL |= TASSEL1;           // configure for SMCLK

	TA1CCR0 = 100;  // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR1 = speed;

	TA1CCTL1 |= OUTMOD_7;        // set TACCTL2 to Reset / Set mode

	TA1CTL |= MC0;                // count up
}

void LB() {                //left motor backward
	P2DIR |= BIT4;                // TA1CCR1 on P2.4
	P2SEL |= BIT4;                //

	P2DIR |= BIT1;
	P2OUT |= BIT1;				//P2.1 = high

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	TA1CTL |= TASSEL1;           // configure for SMCLK

	TA1CCR0 = 100;  // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR2 = speed;

	TA1CCTL2 |= OUTMOD_3;        // set TACCTL2 to Set / Reset mode

	TA1CTL |= MC0;                // count up
}

void RB() {                //right motor backward
	P2DIR |= BIT2;                // TA1CCR1 on P2.2
	P2SEL |= BIT2;                //

	P2DIR |= BIT5;
	P2OUT |= BIT5;				//P2.5 = high

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	TA1CTL |= TASSEL1;           // configure for SMCLK

	TA1CCR0 = 100;  // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR2 = speed;

	TA1CCTL2 |= OUTMOD_3;        // set TACCTL2 to Set / Reset mode

	TA1CTL |= MC0;                // count up
}

void forward() {
	_disable_interrupt();    //important to do whole operation without interrupt
	speed = SPD; //make speed always be 50. (from when I was trying to change speed)
	LF();                //left forward
	RF();                //& right forward make forward
	__delay_cycles(10000000);                //delay length for forward ~1 foot.
	stop();                //stop motors
}

void backward() {
	_disable_interrupt();
	speed = SPD;
	LB();
	RB();
	__delay_cycles(5000000);
	stop();
}

void turnRight45() {
	_disable_interrupt();
	speed = SPD;
	LF();
	RB();
	__delay_cycles(2500000);
	stop();
}

void turnLeft45() {
	_disable_interrupt();
	speed = SPD;
	LB();
	RF();
	__delay_cycles(2500000);
	stop();
}

void turnRight90() {
	_disable_interrupt();
	speed = SPD;
	LF();
	RB();
	__delay_cycles(5000000);
	stop();
}

void turnLeft90() {
	_disable_interrupt();
	speed = SPD;
	LB();
	RF();
	__delay_cycles(5000000);
	stop();
}

void turnLeft135() {
	_disable_interrupt();
	speed = SPD;
	LB();
	RF();
	__delay_cycles(7500000);
	stop();
}

void turnRight135() {
	_disable_interrupt();
	speed = SPD;
	LF();
	RB();
	__delay_cycles(7500000);
	stop();
}

void spin() {                //spin in a circle endlessly
	speed = SPD;
	LF();
	RB();
}

//not working yet
void charge() {
	speed = 50;
	P2DIR |= BIT4 | BIT2;                // TA1CCR1 on P2.4
	P2SEL &= ~(BIT4 | BIT2);                //

	P2DIR |= BIT1 | BIT5;
	P2OUT |= BIT1 | BIT5;				//P2.1 = high

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	TA1CTL |= TASSEL1;           // configure for SMCLK

	TA1CCR0 = 100;  // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR2 = speed;
	TA1CCR1 = speed;

	TA1CCTL2 |= OUTMOD_7;        // set TACCTL2 to Set / Reset mode
	TA1CCTL1 |= OUTMOD_7;

	TA1CTL |= MC0;
}

// -----------------------------------------------------------------------
// Since the IR decoder is connected to P2.6, we want an interrupt
// to occur every time that the pin changes - this will occur on
// a positive edge and a negative edge.
//
// Negative Edge:
// The negative edge is associated with end of the logic 1 half-bit and
// the start of the logic 0 half of the bit.  The timer contains the
// duration of the logic 1 pulse, so we'll pull that out, process it
// and store the bit in the global irPacket variable. Going forward there
// is really nothing interesting that happens in this period, because all
// the logic 0 half-bits have the same period.  So we will turn off
// the timer interrupts and wait for the next (positive) edge on P2.6
//
// Positive Edge:
// The positive edge is associated with the end of the logic 0 half-bit
// and the start of the logic 1 half-bit.  There is nothing to do in
// terms of the logic 0 half bit because it does not encode any useful
// information.  On the other hand, we going into the logic 1 half of the bit
// and the portion which determines the bit value, the start of the
// packet, or if the timer rolls over, the end of the ir packet.
// Since the duration of this half-bit determines the outcome
// we will turn on the timer and its associated interrupt.
// -----------------------------------------------------------------------
#pragma vector = PORT2_VECTOR			// This is from the MSP430G2553.h file
__interrupt void pinChange(void) {

	int8 pin;
	int16 pulseDuration;			// The timer is 16-bits

	if (IR_PIN)
		pin = 1;
	else
		pin = 0;

	switch (pin) {					// read the current pin level
	case 0:						// !!!!!!!!!NEGATIVE EDGE!!!!!!!!!!
		pulseDuration = TAR;
		if (pulseDuration > minStartPulse && pulseDuration < maxStartPulse) {
			packetIndex = 0;

		} else if (pulseDuration > minLogic1Pulse
				&& pulseDuration < maxLogic1Pulse && packetIndex < 33) {

			packetData[packetIndex] = 1;
			packetIndex++;

		} else if (pulseDuration > minLogic0Pulse
				&& pulseDuration < maxLogic1Pulse && packetIndex < 33) {

			packetData[packetIndex] = 0;
			packetIndex++;
		}

		LOW_2_HIGH; 				// Setup pin interrupr on positive edge

		if (packetIndex == 33) {
			newIrPacket = TRUE;

			//_disable_interrupt();
		} // end if new IR packet arrived

		//myCode >> "0";
		break;

	case 1:							// !!!!!!!!POSITIVE EDGE!!!!!!!!!!!
		TAR = 0x0000;				// time measurements are based at time 0
		HIGH_2_LOW; 				// Setup pin interrupr on positive edge

		break;
	} // end switch

	P2IFG &= ~BIT6;	// Clear the interrupt flag to prevent immediate ISR re-entry

} // end pinChange ISR

void initMSP430() {

	IFG1 = 0; 					// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD; 		// stop WD

	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	P2SEL &= ~BIT6;						// Setup P2.6 as GPIO not XIN
	P2SEL2 &= ~BIT6;
	P2DIR &= ~BIT6;
	P2IFG &= ~BIT6;						// Clear any interrupt flag
	P2IE |= BIT6;						// Enable PORT 2 interrupt on pin change

	HIGH_2_LOW;
	P1DIR |= BIT0 | BIT6;				// Enable updates to the LED
	P1OUT &= ~(BIT0 | BIT6);			// An turn the LED off

	TA0CCR0 = 0x8000;					// create a 16mS roll-over period
	TACTL &= ~TAIFG;	// clear flag before enabling interrupts = good practice
	TACTL = ID_3 | TASSEL_2 | MC_1;	// Use 1:1 presclar off MCLK and enable interrupts

	_enable_interrupt();
}

