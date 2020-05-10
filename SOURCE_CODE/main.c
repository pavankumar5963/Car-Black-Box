#include "main.h"
#include "pic_specific.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "timer0.h"
#include "i2c.h"
#include "ds1307.h"
#include "adc.h"
#include "uart.h"
#include "eeprom.h"

unsigned char clock_reg[3]; 
unsigned char time[9], stage = 1;
unsigned short int sec, count, speed, recent_event_index, list_index, menu_index, first_event_index, num_of_events, view_disp_index, clock_index, blink_delay;
unsigned char event_list[MAX_EVENTS_LIST][3] = {"ON","CS", "GR", "GN", "G1", "G2", "G3", "G4", "SP", "CL", "DL", "ST"};

void init_config(void)
{
		init_matrix_keypad();
		init_clcd();
		init_timer0();
		init_i2c();
		init_ds1307();
		init_adc();
		init_uart();
		GIE = 1;
}

void main(void)
{
		init_config();
		unsigned char event_key = 0, key_level = 0, password_flag = 0;
		unsigned char process_flag = 0, gear = GEAR_NEUTRAL, level_up_down_key = 0xFF, negative_edge_key = 0xFF, positive_edge_key = 0xFF;
		first_event_index = (unsigned short int) (read_internal_eeprom(BASE_ADD_RESET + 0) - '0');
		recent_event_index = (unsigned short int) (read_internal_eeprom(BASE_ADD_RESET + 1) - '0');
		num_of_events = (unsigned short int)(read_internal_eeprom(BASE_ADD_RESET + 2) - '0');
		/* Call get time, adc */
		list_index = EVENT_ON;
		store_event();
		unsigned char *str_menu[5] ={"VIEW LOG", "CLEAR LOG", "DOWNLOAD LOG", "CHANGE PASSWORD", "SET TIME"};
		while(1)
		{
				/* Handle cases of collision, gear up and gear down */
				event_key = read_switches_edge(NEGATIVE_EDGE);
				for(unsigned short int delay = 300; delay--;);
				
				positive_edge_key = read_switches_edge(POSITIVE_EDGE);
				for(unsigned short int delay = 300; delay--;);

				if ((event_key == MK_SW12) || (event_key == MK_SW11))
				{
						negative_edge_key = event_key;
				}
				else
				{
						negative_edge_key = 0xFF;
				}
				level_up_down_key = read_switches_level(THREE_SEC_PRESS);
				if (event_key == MK_SW1)
				{
						list_index = COLLISION;
						store_event();
				}
				/* Gear up */
				else if (event_key == MK_SW2)
				{
						if (gear < GEAR_4)
						{
								gear++;
						}
						list_index = gear;
						store_event();
				}
				/* Gear down */
				else if (event_key == MK_SW3)
				{
						if (gear > GEAR_REVERSE)
						{
								gear--;
						}
						list_index = gear;
						store_event();
				}
				switch(stage)
				{
						case 1:
								/* DashBoard Display*/
								{
										display_dashboard();
										if (level_up_down_key == MK_SW11)
										{
												stage = 2;
												TMR0ON = OFF;
												sec = 0;
												count = 0;
												CLEAR_DISP_SCREEN;
										}
								}
								break;
						case 2:
								/* Enter password */
								{
										if(password_enter_check(negative_edge_key))
										{
												stage = 3;
												CLEAR_DISP_SCREEN;
												clcd_putch(RIGHT_ARROW, LINE1(0));
												clcd_putch(' ', LINE1(1));
												clcd_print(str_menu[0], LINE1(2));
												clcd_putch(' ', LINE2(1));
												clcd_print(str_menu[1], LINE2(2));
												menu_index = 0;
										}
								}
								break;
						case 3:
								/* Menu display and select*/
								{

										// Scrolling the menu
										if ((positive_edge_key == MK_SW11) || (positive_edge_key == MK_SW12))	
										{
												menu_print(str_menu, positive_edge_key);
										}
										// ENTER NEXT STAGE
										if (level_up_down_key == MK_SW11)
										{
												stage = 4;
												CLEAR_DISP_SCREEN;
										}
										// GO BACK
										else if (level_up_down_key == MK_SW12)
										{
												stage = 1;
												TMR0ON = OFF;
												sec = 0;			
												count = 0;
												CLEAR_DISP_SCREEN;
												clcd_print("   GOING BACK   ", LINE1(0));
												for (unsigned short int delay1 = 1000; delay1--;)
														for (unsigned short int delay2 = 2000; delay2--;);
												CLEAR_DISP_SCREEN;
										}
								}
								break;
						case 4:
								/* Display each log contents */
								{
										static unsigned char store_flag = 1;
										unsigned char dummy;
										// GO BACK
										if (level_up_down_key == MK_SW12)
										{
												stage = 3;
												TMR0ON = OFF;
												sec = 0;			
												count = 0;
												store_flag = 1;	
												CLEAR_DISP_SCREEN;
												if (menu_index == 4)
												{
													/* Store the new time when coming back to menu */
													store_rtc_time();	
													/* Setting the CH bit of the RTC to Start the Clock */
													dummy = read_ds1307(SEC_ADDR);
													write_ds1307(SEC_ADDR, dummy & 0x7F);
													
													get_time();
													clcd_print("RESET SUCCESSFUL", LINE1(0));
													clcd_print(time, LINE2(4));
													for (unsigned short int delay1 = 1000; delay1--;)
														for (unsigned short int delay2 = 2000; delay2--;);
													clock_index = 0;
													blink_delay = 0;
													CLEAR_DISP_SCREEN;
												}
												else
												{
													clcd_print("   GOING BACK   ", LINE1(0));
													for (unsigned short int delay1 = 1000; delay1--;)
														for (unsigned short int delay2 = 2000; delay2--;);
													CLEAR_DISP_SCREEN;
												}
												continue;
										}
										switch(menu_index)
										{
												case 0:
														{

																view_log(negative_edge_key);
														}
														break;
												case 1:
														{
																clear_log();
																stage = 3;
																clcd_print("  LOGS CLEARED  ", LINE1(0));
																for (unsigned short int delay1 = 1000; delay1--;)
																		for (unsigned short int delay2 = 2000; delay2--;);
																CLEAR_DISP_SCREEN;
														}
														break;
												case 2:
														{
																download_log();
																stage = 3;
																clcd_print("DOWNLOAD SUCCESSFUL", LINE1(0));
																for (unsigned short int delay1 = 1000; delay1--;)
																		for (unsigned short int delay2 = 2000; delay2--;);
																CLEAR_DISP_SCREEN;
														}
														break;
												case 3:
														{
																unsigned char flag_proc = 0;
																if (store_flag)
																{
																		recent_event_index = (recent_event_index + 1) % MAX_EVENTS_STORED;
																		list_index = CHANGE_PASSWORD;
																		store_event();
																		store_flag = 0;
																}
																flag_proc = change_password(negative_edge_key);
																if (flag_proc)
																{
																		stage = 3;
																		store_flag = 1;	
																		CLEAR_DISP_SCREEN;
																		clcd_print("RESET SUCCESSFUL", LINE1(0));
																		for (unsigned short int delay1 = 1000; delay1--;)
																				for (unsigned short int delay2 = 2000; delay2--;);
																}
														}
														break;
												case 4:
														{
																if (store_flag)
																{
																		list_index = SET_TIME;
																		store_event();
																		store_flag = 0;
																		clcd_print("    HH:MM:SS    ", LINE1(0));
																}
																set_time_rtc(time, positive_edge_key);
														}
														break;
										}
								}
								break;
				}
		}
}
