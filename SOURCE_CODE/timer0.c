#include "main.h"
#include "timer0.h"
#include "pic_specific.h"
void init_timer0(void)
{
	TMR0ON = 0;
	/*
	 * Setting instruction cycle clock (Fosc / 4) as the source of
	 * timer0
	 */
	
	T08BIT = 0; 		// 16 bit register	
	T0CS = 0;			// Internal clock
	
	PSA = 0;			// Pre scaler Assignment

	/* Prescaling by 1:2 */
	T0PS2 = 0;
	T0PS1 = 0;
	T0PS0 = 0;

	/* Initial value of timer register */
	TMR0 = 3036;

	/* Clearing timer0 overflow interrupt flag bit */
	TMR0IF = 0;

	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;
}
