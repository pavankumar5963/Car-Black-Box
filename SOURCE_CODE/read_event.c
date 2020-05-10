#include "main.h"
#include "eeprom.h"
//#include "pic_specific.h"

void read_event(unsigned char *clcd_line2_data, unsigned short int index_add, unsigned char first_char)
{
		clcd_line2_data[0] = first_char;
		clcd_line2_data[1] = ' ';
		clcd_line2_data[2] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 0));
		clcd_line2_data[3] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 1));
		clcd_line2_data[4] = ':';
		clcd_line2_data[5] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 2));
		clcd_line2_data[6] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 3));
		clcd_line2_data[7] = ':';
		clcd_line2_data[8] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 4));
		clcd_line2_data[9] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 5));
		clcd_line2_data[10] = ' ';
		clcd_line2_data[11] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 6));
		clcd_line2_data[12] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 7));
		clcd_line2_data[13] = ' ';
		clcd_line2_data[14] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 8));
		clcd_line2_data[15] = read_internal_eeprom((unsigned char) (EVENTS_ADD(index_add)+ 9));
		clcd_line2_data[16] = '\0';
}
