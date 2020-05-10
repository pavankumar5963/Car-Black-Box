#include "main.h"
#include "clcd.h"
#include "eeprom.h"
#include "matrix_keypad.h"

extern unsigned short int recent_event_index, first_event_index, num_of_events, view_disp_index;

/* 
Range of
a) num_of_events is 1 to 10
b) view_disp_index is 0 to 9
*/
void view_log(unsigned char key)
{
	//unsigned short int offset = 0;
	//unsigned char ch;
	if (view_disp_index == 0)
	{
		clcd_print("# TIME     E  SP", LINE1(0));
		unsigned char clcd_line2[MAX_CLCD_CHAR + 1];
		read_event(clcd_line2, first_event_index, view_disp_index + '0');
		clcd_print(clcd_line2, LINE2(0));
	}
	if (key == MK_SW11)
	{
		unsigned short int event_add;
		unsigned char clcd_line2[MAX_CLCD_CHAR + 1];
		if (view_disp_index < (num_of_events - 1))
		{
			view_disp_index++;		
		}
		if (num_of_events < MAX_EVENTS_STORED)						// num_of_events is 1 to 9
		{
			event_add = first_event_index + view_disp_index;
		}
		else															// num_of_events is 10
		{
			event_add = (first_event_index + view_disp_index) % MAX_EVENTS_STORED;
		}
		read_event(clcd_line2, event_add, view_disp_index + '0');
		clcd_print(clcd_line2, LINE2(0));
	}
	else if (key == MK_SW12)
	{
		unsigned short int event_add;
		//clcd_print("# TIME     E  SP", LINE1(0));
		unsigned char clcd_line2[MAX_CLCD_CHAR + 1];
		view_disp_index ? view_disp_index-- : view_disp_index;
		if (num_of_events < MAX_EVENTS_STORED)						// num_of_events is 1 to 9
		{
			event_add = first_event_index + view_disp_index;
		}
		else															// num_of_events is 10
		{
			event_add = (first_event_index + view_disp_index) % MAX_EVENTS_STORED;
		}
		read_event(clcd_line2, event_add, view_disp_index + '0');
		clcd_print(clcd_line2, LINE2(0));
	}
}
