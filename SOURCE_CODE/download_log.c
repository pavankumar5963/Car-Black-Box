#include "main.h"
#include "uart.h"
#include "eeprom.h"

extern unsigned short int first_event_index, num_of_events;

void download_log(void)
{
		unsigned char disp_screen[MAX_CLCD_CHAR + 1] = {'\0'};
		unsigned short int disp_index = 0;
		puts("**************DOWNLOAD STARTED**************\n\r");
		puts("#   TIME   ET SP\n\r");
		while (disp_index < num_of_events)
		{
			read_event(disp_screen, (first_event_index + disp_index) % EACH_EVENT_ADD_SIZE, disp_index + '0');
			puts(disp_screen);
			putch('\n');
			putch('\r');
			disp_index++;
		}
		puts("*************DOWNLOAD COMPLETED*************\n\r");
}
