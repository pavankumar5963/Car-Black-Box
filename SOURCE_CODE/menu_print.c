#include "main.h"
//#include "pic_specific.h"
#include "clcd.h"
#include "matrix_keypad.h"

extern unsigned short int menu_index;

void menu_print(char *str[], char key)
{
	//unsigned char key = read_switches(STATE_CHANGE);
	if (key == MK_SW11)
	{
		if (menu_index > 0)
		{
			CLEAR_DISP_SCREEN;
			menu_index--;	
		}
		clcd_putch(RIGHT_ARROW, LINE1(0));
		clcd_putch(' ', LINE1(1));
		clcd_print(str[menu_index], LINE1(2));
		clcd_print(str[menu_index + 1], LINE2(2));
	}
	else if (key == MK_SW12)
	{
		if (menu_index < (MENU_SIZE - 1))
		{
			menu_index++;
			CLEAR_DISP_SCREEN;
		}
		clcd_putch(RIGHT_ARROW, LINE2(0));
		clcd_putch(' ', LINE2(1));
		clcd_print(str[menu_index - 1], LINE1(2));
		clcd_print(str[menu_index], LINE2(2));
	}
}
