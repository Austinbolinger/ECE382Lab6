#include <msp430.h> 
#include "start5.h"

int speed = 50;

/*
 * main.c
 */
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;       // stop the watchdog timer

	while (1) {

		forward();
		stop();
		turnLeft30();
		stop();
		forward();
		stop();
		turnRight30();
		stop();
		forward();
		stop();
		turnLeft90();
		stop();
		forward();
		stop();
		turnRight90();
		stop();
		forward();
		stop();
		backward();
		stop();
	}
} //end main

void stop() {
	P2DIR &= ~(BIT4 | BIT2);                // TA1CCR1 on P2.4

	P2DIR &= ~(BIT1 | BIT5);
	P2OUT &= ~(BIT1 | BIT5);					// P2.1 = GND

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	__delay_cycles(1000000);
}

void LF() {
	P2DIR |= BIT4;                // TA1CCR1 on P2.4
	P2SEL |= BIT4;

	P2DIR |= BIT1;
	P2OUT &= ~BIT1;					// P2.1 = GND

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	TA1CTL |= TASSEL1;           // configure for SMCLK

	TA1CCR0 = 100;  // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR2 = speed;

	TA1CCTL2 |= OUTMOD_7;        // set TACCTL2 to Reset / Set mode

	TA1CTL |= MC0;                // count up
}

void RF() {
	P2DIR |= BIT2;                // TA1CCR1 on P2.4
	P2SEL |= BIT2;

	P2DIR |= BIT5;
	P2OUT &= ~BIT5;

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	TA1CTL |= TASSEL1;           // configure for SMCLK

	TA1CCR0 = 100;  // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR1 = speed;

	TA1CCTL1 |= OUTMOD_7;        // set TACCTL2 to Reset / Set mode

	TA1CTL |= MC0;                // count up
}

void LB() {
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

void RB() {
	P2DIR |= BIT2;                // TA1CCR1 on P2.4
	P2SEL |= BIT2;                //

	P2DIR |= BIT5;
	P2OUT |= BIT5;

	TA1CTL &= ~MC1 | MC0;            // stop timer A1

	TA1CTL |= TACLR;                // clear timer A1

	TA1CTL |= TASSEL1;           // configure for SMCLK

	TA1CCR0 = 100;  // set signal period to 100 clock cycles (~100 microseconds)
	TA1CCR2 = speed;

	TA1CCTL2 |= OUTMOD_3;        // set TACCTL2 to Set / Reset mode

	TA1CTL |= MC0;                // count up
}

void forward() {
	LF();
	RF();
	__delay_cycles(1000000);
}

void backward() {
	LB();
	RB();
	__delay_cycles(1000000);
}

void turnRight30() {
	LF();
	RB();
	__delay_cycles(250000);
}

void turnLeft30() {
	LB();
	RF();
	__delay_cycles(250000);
}

void turnRight90() {
	LF();
	RB();
	__delay_cycles(550000);
}

void turnLeft90() {
	LB();
	RF();
	__delay_cycles(550000);
}
