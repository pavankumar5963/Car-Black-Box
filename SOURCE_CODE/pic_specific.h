#ifndef PIC_SPECIFIC_H
#define PIC_SPECIFIC_H

#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config OSC			= XT
#pragma config WDT			= OFF
#pragma config BOREN		= OFF
#pragma config PBADEN		= OFF
#pragma config LVP			= OFF

#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7

#define MATRIX_KEYPAD_PORT		PORTB
#define ROW3				RB7
#define ROW2				RB6
#define ROW1				RB5
#define COL4				RB4
#define COL3				RB3
#define COL2				RB2
#define COL1				RB1


#define BUZZER				RE0

#define LED_PORT			PORTB
#define LED7				RB6
#define LED8				RB7

#endif
