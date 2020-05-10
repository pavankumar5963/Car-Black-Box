#ifndef PIC_SPECIFIC_H
#define PIC_SPECIFIC_H

#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config OSC			= XT
#pragma config WDT			= OFF
#pragma config BOREN		= OFF
#pragma config PBADEN		= OFF
#pragma config LVP			= OFF


#define CLCD_PORT										PORTD
#define CLCD_EN											PORTCbits.RC2
#define CLCD_RS											PORTCbits.RC1
#define CLCD_RW											PORTCbits.RC0
#define CLCD_BUSY										PORTDbits.RD7
#define PORT_DIR										TRISD7
#define MATRIX_KEYPAD_PORT	PORTB
#define ROW3					PORTBbits.RB7
#define ROW2					PORTBbits.RB6
#define ROW1					PORTBbits.RB5
#define COL4					PORTBbits.RB4
#define COL3					PORTBbits.RB3
#define COL2					PORTBbits.RB2
#define COL1					PORTBbits.RB1

#define PSW_COUNT  		5
#define MAX_LOG_COUNT  		10
#define CNG_PSW_COUNT 		60
#define TRIES_OVER_COUNT 	15

#endif
