#include "main.h"
#include "ds1307.h"
#include "i2c.h"
#include "clcd.h"
#include "matrix_keypad.h"

extern unsigned short int clock_index, blink_delay;					// clock index used to select the field(Hr, min, sec)
void set_time_rtc(unsigned char *time,unsigned char key)
{
//		get_time();
		if (key == MK_SW11)
		{
				clock_index = (clock_index + 1) % 3;
				blink_delay = 0;
		}
		else if (key == MK_SW12)
		{
				roll_over_increment(time, clock_index);
		}
		/* Display blinking */
		switch (clock_index)
		{
				case 0:
						// Hr blink
						{
								blink_delay = (blink_delay + 1) % 500;
								if (blink_delay < 250)
								{
									clcd_putch(' ', LINE2(4));
									clcd_putch(' ', LINE2(5));
								}
								else
								{
									clcd_print(time, LINE2(4));	
								}
						}
						break;
				case 1:
						// Min blink
						{
								blink_delay = (blink_delay + 1) % 500;
								if (blink_delay < 250)
								{
									clcd_putch(' ', LINE2(7));
									clcd_putch(' ', LINE2(8));
								}
								else
								{
									clcd_print(time, LINE2(4));			
								}
						}
						break;
				case 2:
						// Sec blink
						{
								blink_delay = (blink_delay + 1) % 500;
								if (blink_delay < 250)
								{	
									clcd_putch(' ', LINE2(10));			
									clcd_putch(' ', LINE2(11));
								}
								else
								{
									clcd_print(time, LINE2(4));			
								}
						}
						break;
		}
}
