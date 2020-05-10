#include "pic_specific.h"
#include "matrix_keypad.h"
#include "main.h"
#include "clcd.h"
extern unsigned short int sec, count;
void init_matrix_keypad(void)
{
		/* Config PORTB as digital */
		ADCON1 = 0x0F;

		/* Set Rows (RB7 - RB5) as Outputs and Columns (RB4 - RB1) as Inputs */
		TRISB = 0x1E;

		/* Set PORTB input as pull up for columns */
		RBPU = 0;

		MATRIX_KEYPAD_PORT = MATRIX_KEYPAD_PORT | 0xE0;
}

unsigned char scan_key(void)
{
		ROW1 = LO;
		ROW2 = HI;
		ROW3 = HI;

		if (COL1 == LO)
		{
				return 1;
		}
		else if (COL2 == LO)
		{
				return 4;
		}
		else if (COL3 == LO)
		{
				return 7;
		}
		else if (COL4 == LO)
		{
				return 10;
		}

		ROW1 = HI;
		ROW2 = LO;
		ROW3 = HI;

		if (COL1 == LO)
		{
				return 2;
		}
		else if (COL2 == LO)
		{
				return 5;
		}
		else if (COL3 == LO)
		{
				return 8;
		}
		else if (COL4 == LO)
		{
				return 11;
		}

		ROW1 = HI;
		ROW2 = HI;
		ROW3 = LO;
		/* TODO: Why more than 2 times? */
		ROW3 = LO;

		if (COL1 == LO)
		{
				return 3;
		}
		else if (COL2 == LO)
		{
				return 6;
		}
		else if (COL3 == LO)
		{
				return 9;
		}
		else if (COL4 == LO)
		{
				return 12;
		}

		return 0xFF;
}

unsigned char read_switches_edge(unsigned char detection_type)
{
		static unsigned char once = 1, key, flag = 1, prev = 0xFF;

		if (detection_type == POSITIVE_EDGE)
		{
				key = scan_key();
				// Upper edge trigger
				if (key != 0xFF)
				{
						prev = key;
				}
				else if (key == 0xFF && prev != 0xFF)
				{
						key = prev;
						prev = 0xFF;
						return key;
				}
		}
		else if (detection_type == NEGATIVE_EDGE)
		{
				key = scan_key();
				/*clcd_putch('0' + key, LINE1(0));
					for (unsigned short int delay1 = 1000; delay1--;)
						for (unsigned short int delay2 = 1000; delay2--;);*/
				// Lower edge trigger
				if(key != 0xFF && once)
				{
						once = 0;
						return key;
				}
				else if(key == 0xFF)
				{
						once = 1;
				}
		}
		return 0xFF;
}
unsigned char read_switches_level(unsigned char detection_type)
{
		unsigned char key;
		static unsigned char flag = 1;
		key = scan_key();
		if (detection_type == LEVEL_CHANGE)
		{
				return scan_key();
		}
		else if (detection_type == THREE_SEC_PRESS)
		{
				key = scan_key();
				if ((key == MK_SW11) || (key == MK_SW12))
				{
						if(flag)
						{
								sec = 0;
								count = 0;
								TMR0ON = ON;
								flag = 0;
						}
						if (sec > 2)
						{
								TMR0ON = OFF;
								sec = 0;
								count = 0;
								flag = 1;
								return key;	
						}	
				}
				else
				{
						if (flag == 0)
						{
								flag = 1;
						}

				}
		}
		return 0xFF;
}
