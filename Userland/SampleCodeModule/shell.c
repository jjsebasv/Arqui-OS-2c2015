#include <stdint.h>
#include "define.h"
#include "lib.h"
#include "shell.h"
#include "../../Sounds/soundsDataBase.c"

char shellBuffer[COMMAND_LINE_SIZE] = {0};
int bufferIndex = 0;

/*
 * Clears the shell buffer
 */
static void clearBuffer();

/*
 * Help function
 */
static void help();

/*
 * Sets the system time
 */
static void setTime();

/*
 * Prints system time
 */
static void getTime();

/*
 * Set screensaver wait time
 */
static void setScreensaver(int seconds);

static void getCpuVendor();

/*
 * Plays a sound test
 */
static void playTest();

/*
 * Plays a different sound for each key
 */
static void ringingKeyboard();

static void choose_music();

static void read_music(int *score);

void startShell()
{
	char c;

	printLineStart();
	// Main loop
	while (1) {
		// Keep waiting till there's a key to read
		c = getChar();

		switch (c) {
			case '\n':
				putChar(c);
				parseCommand(shellBuffer);
				printLineStart();
				break;
			case '\b':
				if (bufferIndex > 0) {
					putChar(c);
					shellBuffer[bufferIndex] = '\0';
					bufferIndex--;
				} else {
					bufferIndex = 0;
					shellBuffer[0] = '\0';
				}

				break;
			default:
				if (bufferIndex == COMMAND_LINE_SIZE - 1) {
					putChar('\b');
					bufferIndex--;
				}

				shellBuffer[bufferIndex++] = c;
				putChar(c);
				break;
		}
	}
}

void printLineStart()
{
	printf("#> ");
}

void parseCommand(const char * line)
{
	char command[80] = {0};
	char args[80] = {0};

	// We need at least the command to be scanned
	int hasCommand = sscanf(line, "%s %s", command, args);
	if (hasCommand == 0)
		return;

	if (strcmp(command, HELP_COMMAND) == 0) {
		help();
	} else if (strcmp(command, SET_TIME_COMMAND) == 0) {
		setTime();
	} else if (strcmp(command, GET_TIME_COMMAND) == 0) {
		getTime();
	} else if (strcmp(command, SET_SCREENSAVER_COMMAND) == 0) {
		int seconds = 0;
		if (sscanf(args, "%d", &seconds) > 0 && seconds > 0) {
			setScreensaver(seconds);
		} else
			printf("Invalid argument\n");
	} else if (strcmp(command, GET_CPU_VENDOR_COMMAND) == 0) {
		getCpuVendor();
	} else if (strcmp(command, PLAY_TEST_COMMAND) == 0) {
		playTest();
	} else if (strcmp(command, KEYBOARD_SOUND_COMMAND) == 0) {
		ringingKeyboard();
	} else if (strcmp(command, CHOSE_MUSIC_COMMAND) == 0) {
		choose_music();
	} else {
		printf("Command not found.\n");
	}

	clearBuffer();
}

static void clearBuffer(void)
{
	int i;
	for (i = 0; i < 76; i++)
		shellBuffer[i] = 0;

	bufferIndex = 0;
}

/*
 * Shell functions
 */
static void help()
{
	int opt = 0;
	printf("Hi, I'm help, available commands:\n");
	printf("Please select your option\n");
	printf("0 - GET TIME\n");
	printf("1 - SET TIME\n");
	printf("2 - SET SCREENSAVER TIME\n");
	printf("3 - GET CPU VENDOR\n");
	printf("4 - TEST SOUND\n");
	printf("5 - RING KEYBOARD\n");
	printf("6 - CHOOSE MUSIC\n");

	if (scanf("%d", &opt) == 0 || opt > 6) {
		printf("Invalid option\n");
		return;
	}

	switch(opt){
		case GET_DATE:
			printf("GET DATE:\n");
			printf("Command: time\n");
			printf("Display the current date and time in the following format: YYYY/MM/DD HH:MM:SS\n");
			break;
		case SET_DATE:
			printf("SET DATE:\n");
			printf("Command: stime\n");
			printf("Set the system current date and time\n");
			break;
		case SET_SCREENSAVER:
			printf("SET SCREENSAVER TIME:\n");
			printf("Command: ss n\n");
			printf("** n is the timeout period in seconds **\n");
			printf("Set the scrensaver timeout period\n");
			break;
		case GET_CPU_VENDOR:
			printf("GET CPU VENDOR:\n");
			printf("Command: cpuid\n");
			printf("Display the CPU's manufacturer ID string\n");
			break;
		case PLAY_TEST:
			printf("PLAY TEST\n");
			printf("Command: playtest\n");
			printf("Plays a default tune\n");
			break;
		case RINGING_KEYBOARD:
			printf("RINGING KEYBOARD\n");
			printf("Command: rkeyboard\n");
			printf("Plays a different sound for each key until you press enter\n");
			break;
		case CHOSE_MUSIC:
			printf("CHOOSE MUSIC\n");
			printf("Command: choosemusic\n");
			printf("Choose one of our musics and play\n");
			break;
		default:
			printf("Invalid command.\n");
	}
}

static void setTime()
{
	int hour = 0, minute = 0, second = 0;
	int year = 1, day = 0, month = 0;
	date current_date;
	int error = 0;

	printf("Enter date in this format: YY MM DD HH MM SS\n");
	do {
		scanf("%d %d %d %d %d %d", &year, &month, &day, &hour, &minute, &second);
		if (year <= 0  || year > 99 || month <= 0 || day <= 0 || day > 31 || month > 12 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59){
			printf("Invalid Format\n");
		}
	} while ( year <= 0 || year > 99 || month <= 0 || day <= 0 || day > 31 || month > 12 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59);
	
	current_date.hour = hour;
	current_date.minute = minute;
	current_date.second = second;
	current_date.day = day;
	current_date.month = month;
	current_date.year = year;

	printStruct(&current_date);

	execSysCall(SYS_STIME, &current_date, 1, 1);
	printf("Complete.\n");
	getTime();
}

void printStruct ( date * current_date ){
	printf("Seconds: %d\n", current_date->second);
	printf("Minutes: %d\n", current_date->minute);
	printf("Hours: %d\n", current_date->hour);
	printf("Day: %d\n", current_date->day);
	printf("Month: %d\n", current_date->month);
	printf("Year: %d\n", current_date->year);
}

static void getTime()
{
	date current_date;
	execSysCall(SYS_TIME, &current_date, 1, 1);
	printf(
		"Current date and time: %d/%d/%d %d:%d:%d\n",
		current_date.year,
		current_date.month,
		current_date.day,
		current_date.hour,
		current_date.minute,
		current_date.second
	);
}

static void setScreensaver(int seconds)
{
	execSysCall(SYS_SCREENSAVER, seconds, 0, 0);
	printf("Screensaver timeout set to %d seconds\n", seconds);
}

static void getCpuVendor() 
{
	char vendor[13];
	execSysCall(SYS_CPUVENDOR, vendor, 0, 0);
	vendor[12] = '\0';
	printf("%s\n", vendor);
}

static void playTest()
{
	int i;
	printf("Playing sound\n");
	for(i=1;i<30;i++) {
		execSysCall(SYS_SOUND, 500, 440+10*i, 0); // Time - Freq	
	}
	for(i=1;i<15;i++) {
		execSysCall(SYS_SOUND, 500, 590-10*i, 0); // Time - Freq	
	}
}

static void ringingKeyboard()
{
	int c, i = 0;
	printf("Write after this message:\n>");

	while((c=getChar())!='\n'){
		if(c == '\b'){
			if( i > 0){			
				putChar(c);
				i--;
			}
			execSysCall(SYS_SOUND, 500, 440 + (c*100), 0);
		}else{
			putChar(c);
			execSysCall(SYS_SOUND, 500, 440 + (c*100), 0);
			i++;
		}
	}
	putChar('\n');
}

static void choose_music()
{
	int opt = 0;
	printf("This are the available songs:\n");
	printf("Please select your option\n");
	int s_index;
	for( s_index = 0; songs[s_index].last != 1; s_index++) {
		printf("%d - %s\n", s_index, songs[s_index].name );
	}
	if (scanf("%d", &opt) == 0 || opt > s_index-1) {
		printf("Not such music file\n");
		return;
	}
	else {
		printf("%s\n", songs[opt].name );
		read_music(songs[opt].score);
	}
}

void read_music(int *score) {
	int i;
	for (i = 0; score[i] != -1; ) {
		execSysCall(SYS_SOUND, score[i++], score[i++], 0);
	}
}
