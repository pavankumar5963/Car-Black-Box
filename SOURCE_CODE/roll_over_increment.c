#include "main.h"

void roll_over_increment(unsigned char *time, unsigned short int index)
{
		/* Change minutes and seconds */
		if (index)
		{
				unsigned short int temp = index * 3;
				time[temp + 1] = '0' + (((time[temp + 1] - '0') + 1) % 10);
				if ((time[temp + 1] == '0'))
				{
					time[temp] = '0' + (((time[temp] - '0') + 1) % 6);
				}
		}
		/* Change hours */
		else
		{
				if (time[index] == '2')
				{

						time[index + 1] = '0' + (((time[index + 1] - '0') + 1) % 4);
						if (time[index + 1] == '0')
						{
								time[index] = '0';
						}
				}
				else
				{
						time[index + 1] = '0' + (((time[index + 1] - '0') + 1) % 10);
						if (time[index + 1] == '0')
						{
								time[index] = '0' + (((time[index] - '0') + 1) % 3);
						}
				}
		}
}
