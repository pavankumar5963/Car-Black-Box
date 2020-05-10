#include "main.h"
#include "clcd.h"
#include "adc.h"

extern unsigned short int speed, recent_event_index, list_index;
extern unsigned char time[9];
extern unsigned char event_list[MAX_EVENTS_LIST][3];

void display_dashboard(void)
{
	unsigned char clcd_line2[MAX_CLCD_CHAR + 1];
	speed = (read_adc(CHANNEL4));
	get_time();
	clcd_line2[0] = ' ';
	clcd_line2[1] = ' ';
	clcd_line2[2] = time[0];
	clcd_line2[3] = time[1];
	clcd_line2[4] = time[2];
	clcd_line2[5] = time[3];
	clcd_line2[6] = time[4];
	clcd_line2[7] = time[5];
	clcd_line2[8] = time[6];
	clcd_line2[9] = time[7];
	clcd_line2[10] = ' ';
	clcd_line2[11] = event_list[list_index][0];
	clcd_line2[12] = event_list[list_index][1];
	clcd_line2[13] = ' ';
	clcd_line2[14] = '0' + (speed / 10);
	clcd_line2[15] = '0' + (speed % 10);
	clcd_line2[16] = '\0';
	//read_event(clcd_line2, recent_event_index, ' ');
	clcd_print("  TIME     E  SP", LINE1(0));
	clcd_print(clcd_line2, LINE2(0));
}
