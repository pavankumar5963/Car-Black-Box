#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"

void init_config(void)
{
		init_clcd();
		init_matrix_keypad();
}

void main()
{
		init_config();
		/* Set Default Password (4 bytes)*/
		write_internal_eeprom(0x00, '1');
		write_internal_eeprom(0x01, '0');
		write_internal_eeprom(0x02, '1');
		write_internal_eeprom(0x03, '0');
		/* Set first, recent and total number of events (each 1 byte)*/
		write_internal_eeprom(0x05, '0');
		write_internal_eeprom(0x06, '0');
		write_internal_eeprom(0x07, '0');
}
