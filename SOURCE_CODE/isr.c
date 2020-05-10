#include "pic_specific.h"

extern unsigned short int sec;
extern unsigned short int count;

void interrupt isr(void)
{
	if (TMR0IF)
	{
		TMR0 = TMR0 + 3038;

		if (count++ == 40)			// Count reaches 40 for every 1 sec
		{
			count = 0;
			sec++;
		}
		TMR0IF = 0;
	}
}
