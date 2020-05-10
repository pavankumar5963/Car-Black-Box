#include "pic_specific.h"
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "eeprom.h"

/* Global variables */
extern unsigned short int sec, count;
extern unsigned char stage;
static short int re_enter = 1;
/* Function defination to compare password 
 */
unsigned char check_password(unsigned char usercode[], unsigned char check_passcode[])
{
		/* Call password from eeprom */
		unsigned char index = 0;
		while(index < MAX_PASS_SIZE)
		{
				if (usercode[index] != check_passcode[index])
				{
						return (unsigned char) 0;					// If password incorrect
				}
				index++;
		}
		return (unsigned char) 1;									// If password correct
}

/* Function defination to read password 
 */
unsigned char enter_password(unsigned char *usercode, unsigned char key, unsigned short int wait_time)
{	
		static unsigned char index = 0;
		if (index == 0)
		{
				TMR0ON = ON;
				/*	clcd_print("Back", LINE1(0));
					for (unsigned short int delay1 = 1000; delay1--;)
					for (unsigned short int delay2 = 2000; delay2--;);
				 */
		}
		else
		{
				TMR0ON = OFF;
				sec = 0;
				count = 0;
		}
		// Go back to dash board after 30 sec
		if ((index == 0) && (sec > wait_time))
		{
				TMR0ON = 0;
				sec = 0;			
				count = 0;
				stage = 1;
				re_enter = 1;
				return (unsigned char)0;
				/*clcd_print("Back", LINE1(0));
				  for (unsigned short int delay1 = 1000; delay1--;)
				  for (unsigned short int delay2 = 2000; delay2--;);
				 */
		}
		if (key == MK_SW11)
		{
				usercode[index] = '0';
				clcd_putch('*', LINE2(4 + index));
				index = (index + 1) % MAX_PASS_SIZE;
		}
		else if (key == MK_SW12)
		{
				usercode[index] = '1';
				clcd_putch('*', LINE2(4 + index));
				index = (index + 1) % MAX_PASS_SIZE;
		}
		if (index == (MAX_PASS_SIZE - 1))
		{
				index = 0;
				return (unsigned char) 1;											// If 8 characters of passcode has be entered
		}
		return (unsigned char) 0;													// If user did not enter 8 characters
}

/* Function defination
 */
unsigned char password_enter_check(unsigned char key)
{
		static unsigned char array[MAX_PASS_SIZE] = {'\0'};
		static unsigned short int proc_flag = 1;
		//static unsigned short int i, j;
		static unsigned char proc_return = 0, trail = 5;
		static unsigned char passcode[5];
		switch(proc_flag)
		{
				case 1:
						//
						{
								if (re_enter)
								{
										CLEAR_DISP_SCREEN;
										clcd_print(" Enter Password ", LINE1(0));
										DISP_ON_AND_CURSOR_BLINK_ON;
										MOV_CURSOR_ADDR(LINE2(4));
										re_enter = 0;
								}
								proc_return = enter_password(array, key, TEN_SEC);
								if (proc_return)
								{
										proc_flag = 2;
										DISP_ON_AND_CURSOR_OFF;
										CLEAR_DISP_SCREEN;
										TMR0ON = 0;
										sec = 0;
										count = 0;
										re_enter = 1;
										passcode[0] = read_internal_eeprom((unsigned char)(BASE_ADD_PASS + 0));
										passcode[1] = read_internal_eeprom((unsigned char)(BASE_ADD_PASS + 1));
										passcode[2] = read_internal_eeprom((unsigned char)(BASE_ADD_PASS + 2));
										passcode[3] = read_internal_eeprom((unsigned char)(BASE_ADD_PASS + 3));
										passcode[4] = '\0';
								}
						}
						break;
				case 2:
						{
								/**/
								proc_return = check_password(array, passcode);
								if (proc_return)
								{
										CLEAR_DISP_SCREEN;
										DISP_ON_AND_CURSOR_OFF;
										clcd_print("PASSWORD SUCCESSFUL", LINE1(0));
										for (unsigned short int delay1 = 1000; delay1--;)
											for (unsigned short int delay2 = 1000; delay2--;);
										//MOV_CURSOR_TO_LINE2;
										/*for(unsigned char i = 0; i < MAX_PASS_SIZE; i++)
										{
											array[i] = '\0';
											passcode[i] = '\0';
										}*/
										proc_return = 0;
										trail = 5;
										proc_flag = 1;
										re_enter = 1;
										CLEAR_DISP_SCREEN;
										return 1;
								}
								else
								{
										clcd_print("PASSWORD FAILURE", LINE1(0));
										trail--;
										if (trail == 0)
										{
												proc_flag = 3;
												trail = 5;
												TMR0ON = 1;
												CLEAR_DISP_SCREEN;
										}
										else
										{
												if (trail == 1)
												{
														clcd_print("1 Trial remain", LINE2(0));
												}
												else if (trail == 2)
												{
														clcd_print("2 Trial remain", LINE2(0));
												}
												else if (trail == 3)
												{
														clcd_print("3 Trial remain", LINE2(0));
												}
												else if (trail == 4)
												{
														clcd_print("4 Trial remain", LINE2(0));
												}
												else if (trail == 5)
												{
														clcd_print("5 Trial remain", LINE2(0));
												}
												/* Blocking delay */
												for(unsigned short int i = 1000; i--; )
												{
														for(unsigned short int j = 2000; j--; );
												}	
												proc_flag = 1;
												re_enter = 1;
												CLEAR_DISP_SCREEN;
										}
								}
						}
						break;
				case 3:
						{
								unsigned char ch;
								clcd_print("Trials Exceeded", LINE1(0));
								unsigned short int time_rem = 180 - sec;
								clcd_print("Wait for", LINE2(0));
								ch = '0' + (time_rem / 100);
								clcd_putch(ch, LINE2(9));
								ch = '0' + ((time_rem / 10) % 10);
								clcd_putch(ch, LINE2(10));
								ch = '0' + (time_rem % 10);
								clcd_putch(ch, LINE2(11));
								clcd_print("sec", LINE2(13));

								if (sec == 180)
								{
										proc_flag = 1;
										re_enter= 1;
										TMR0ON = 0;
										sec = 0;
										CLEAR_DISP_SCREEN;
								}
						}
						break;
		}
		return 0;
}

unsigned char change_password(unsigned char key)
{
		static unsigned char new_password[MAX_PASS_SIZE] = {'\0'};
		static unsigned char recheck_password[MAX_PASS_SIZE] = {'\0'};
		static unsigned short int proc_flag = 1, flag = 1;
		//static unsigned short int i, j;
		static unsigned char proc_return;
		switch(proc_flag)
		{
				case 1:
						//
						{
								if (flag)
								{
										clcd_print("New Password", LINE1(2));
										DISP_ON_AND_CURSOR_BLINK_ON;
										MOV_CURSOR_ADDR(LINE2(4));
										flag = 0;
								}
								proc_return = enter_password(new_password, key, THIRTY_SEC);
								if (proc_return)
								{
										proc_flag = 2;
										DISP_ON_AND_CURSOR_OFF;
										CLEAR_DISP_SCREEN;
										TMR0ON = 0;
										sec = 0;
										flag = 1;
										count = 0;
								}
						}
						break;
				case 2:
						{
								if (flag)
								{
										clcd_print("Re-Enter Password", LINE1(0));
										DISP_ON_AND_CURSOR_BLINK_ON;
										MOV_CURSOR_ADDR(LINE2(4));
										flag = 0;
								}
								proc_return = enter_password(recheck_password, key, TEN_SEC);
								if (proc_return)
								{
										proc_flag = 3;
										DISP_ON_AND_CURSOR_OFF;
										CLEAR_DISP_SCREEN;
										TMR0ON = 0;
										sec = 0;
										flag = 1;
										count = 0;
								}
						}
						break;

				case 3:
						{
								/**/
								proc_return = check_password(new_password, recheck_password);
								if (proc_return)
								{
										CLEAR_DISP_SCREEN;
										DISP_ON_AND_CURSOR_OFF;
										clcd_print("RESET SUCCESSFUL", LINE1(0));
										//MOV_CURSOR_TO_LINE2;
										proc_flag = 4;
								}
								else
								{
										clcd_print("  RESET FAILED  ", LINE1(0));
										/* Blocking delay */
										for(unsigned short int i = 1000; i--; )
										{
												for(unsigned short int j = 2000; j--; );
										}	
										proc_flag = 1;
										flag = 1;
										CLEAR_DISP_SCREEN;
								}
						}
						break;
				case 4:
						{
								write_internal_eeprom(BASE_ADD_PASS, new_password[0]);
								write_internal_eeprom(BASE_ADD_PASS + 1, new_password[1]);
								write_internal_eeprom(BASE_ADD_PASS + 2, new_password[2]);
								write_internal_eeprom(BASE_ADD_PASS + 3, new_password[3]);
								proc_flag = 5;
						}
						break;
				case 5:
						// Redefine all static variable 
						{
								for(unsigned char i = 0; i < MAX_PASS_SIZE; i++)
								{
										new_password[i] = '\0';
										recheck_password[i] = '\0';
								}
								proc_return = 0;
								proc_flag = 1;
								flag = 1;
								CLEAR_DISP_SCREEN;
								return 1;
						}
		}
		return 0;
}
