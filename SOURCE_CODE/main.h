#ifndef MAIN_H
#define	MAIN_H

/* MACROS */
#define MAX_CLCD_CHAR			16
#define MENU_SIZE				5
#define BASE_ADD_PASS    		0x00
#define BASE_ADD_EVENTS			0x10
#define BASE_ADD_RESET			0x05
#define MAX_PASS_SIZE			5
#define MAX_EVENTS_STORED		10
#define MAX_EVENTS_LIST			12
#define EACH_EVENT_ADD_SIZE		10
#define EVENT_ON				0
#define COLLISION				1
#define GEAR_REVERSE			2
#define GEAR_NEUTRAL			3
#define GEAR_1					4
#define GEAR_2					5
#define GEAR_3					6
#define GEAR_4					7
#define CHANGE_PASSWORD			8
#define CLEAR_LOG				9
#define DOWNLOAD_LOG			10
#define SET_TIME				11
#define ON						1
#define OFF						0
#define NEGATIVE_EDGE			0
#define POSITIVE_EDGE			1
#define TEN_SEC					10
#define THIRTY_SEC				30

#define EVENTS_ADD(x)		(BASE_ADD_EVENTS + (10 * x))

/* User defined structure */
/*
struct event_var
{
	char *time;
	char *event;
	unsigned short int speed;
}*/

/* */
unsigned char change_password(unsigned char key);

/* */
//unsigned char compare_password(unsigned char new_password[], unsigned char recheck_password[]);

/* */
unsigned char check_password(unsigned char usercode[], unsigned char check_passcode[]);

/* */
unsigned char enter_password(unsigned char *usercode, unsigned char key, unsigned short int wait_time);

/* */
//unsigned char re_enter_password(unsigned char *usercode, unsigned char key);

/* */
unsigned char password_enter_check(unsigned char key);

/* */
void store_event();

/* */
void read_event(unsigned char *clcd_line2_data, unsigned short int index_add, unsigned char first_char);

/* */
void roll_over_increment(unsigned char *time, unsigned short int index);

/* */
void store_rtc_time(void);

/* */
void get_time(void);

/* */
void set_time_rtc(unsigned char *time, unsigned char key);

/* */
void view_log(unsigned char key);

/* */
void menu_print(char *str[], char key);

/* */
void display_dashboard(void);

/* */
void clear_log(void);

/* */
void download_log(void);
#endif
