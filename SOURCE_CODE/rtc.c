#include "main.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"

extern unsigned char clock_reg[3];
extern unsigned char time[9];

void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);
	// 12 Hour clock
	if (clock_reg[0] & 0x40)
	{

		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	// 24 Hour clock
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}

void store_rtc_time(void)
{
	unsigned char num1, num2, hr_bcd, min_bcd, sec_bcd;
	/* Convert to bcd and Store hour */
	num1 = time[0] - '0';
	num2 = time[1] - '0';
	hr_bcd = (num1 << 4) | (num2);
	write_ds1307(HOUR_ADDR, hr_bcd);
	/* Convert to bcd and Store min */
	num1 = time[3] - '0';
	num2 = time[4] - '0';
	min_bcd = (num1 << 4) | (num2);
	write_ds1307(MIN_ADDR, min_bcd);
	/* Convert to bcd and Store sec and stop the clock*/
	num1 = time[6] - '0';
	num2 = time[7] - '0';
	sec_bcd = ((num1 << 4) | (num2)) | 0x80;
	write_ds1307(SEC_ADDR, sec_bcd);
}
