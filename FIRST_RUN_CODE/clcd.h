#ifndef LCD_H
#define LCD_H

/* Refer pic_specific.h for port specific definations */

#define HI												1
#define LO												0

#define INPUT											0xFF
#define OUTPUT											0x00

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0

#define LINE1(x)										(0x80 + (x))
#define LINE2(x)										(0xC0 + (x))

#define TWO_LINE_5x7_MATRIX_8_BIT						clcd_write(0x38, INSTRUCTION_COMMAND)
#define CLEAR_DISP_SCREEN								clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME										clcd_write(0x02, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF							clcd_write(0x0C, INSTRUCTION_COMMAND)

void init_clcd(void);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void clcd_write(unsigned char bit_values, unsigned char control_bit);

#endif
