#include "main.h"
#include "eeprom.h"
#include "adc.h"

extern unsigned short int list_index, recent_event_index, first_event_index, num_of_events, speed, view_disp_index;
extern unsigned char time[9];
extern unsigned char event_list[MAX_EVENTS_LIST][3];
/* Make curent list index to zero*/
void clear_log(void)
{
	num_of_events = 0;
	first_event_index = 0;
	recent_event_index = 0;
	view_disp_index = 0;
	list_index = CLEAR_LOG;
	store_event();
}
