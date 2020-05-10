#include "main.h"
#include "eeprom.h"
#include "adc.h"

extern unsigned char clock_reg[3];       
extern unsigned char time[9];
extern unsigned short int sec, count, speed, recent_event_index, list_index, num_of_events, first_event_index;
extern unsigned char event_list[MAX_EVENTS_LIST][3];

/*
   Store ASCII values of the event data
 */
void store_event()
{
		unsigned short int offset_add = 0;
		unsigned char data;
		if (num_of_events)
		recent_event_index = (recent_event_index + 1) % MAX_EVENTS_STORED;
		speed = read_adc(CHANNEL4);
		get_time();
		/* offset goes from 0 to 9*/
		while(offset_add < EACH_EVENT_ADD_SIZE)
		{
				switch(offset_add)
				{
						case 0:
								data = time[0];
								break;
						case 1:
								data = time[1];
								break;
						case 2:
								data = time[3];
								break;
						case 3:
								data = time[4];
								break;
						case 4:
								data = time[6];
								break;
						case 5:
								data = time[7];
								break;
						case 6:
								data = event_list[list_index][0];
								break;
						case 7:
								data = event_list[list_index][1];
								break;
						case 8:
								data = '0' + (speed / 10);
								break;
						case 9:
								data = '0' + (speed % 10);
								break;
				}
				write_internal_eeprom((unsigned char)EVENTS_ADD(recent_event_index) + offset_add, data);
				offset_add++;
		}
		if (num_of_events < MAX_EVENTS_STORED)
		{
				num_of_events++;
		}
		else
		{
				first_event_index = (recent_event_index + 1) % MAX_EVENTS_STORED;
		}
		write_internal_eeprom((unsigned char)(BASE_ADD_RESET), (unsigned char) (first_event_index + '0'));
		write_internal_eeprom((unsigned char)(BASE_ADD_RESET + 1), (unsigned char) (recent_event_index + '0'));
		write_internal_eeprom((unsigned char)(BASE_ADD_RESET + 2), (unsigned char) (num_of_events + '0'));
		
}
