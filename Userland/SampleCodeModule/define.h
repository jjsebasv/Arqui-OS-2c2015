#ifndef _DEFINE_H
#define _DEFINE_H

#include <stdint.h>

#define SYS_READ	0x03
#define SYS_WRITE	0x04
#define SYS_TIME	0x0D
#define SYS_STIME	0x19
#define SYS_SCREENSAVER	0x20
#define SYS_CPUVENDOR	0x24
#define SYS_SOUND	0x0C80

#define COMMAND_LINE_SIZE	77
#define GET_DATE			0
#define SET_DATE			1
#define SET_SCREENSAVER		2
#define GET_CPU_VENDOR		3
#define PLAY_TEST 			4
#define RINGING_KEYBOARD	5
#define CHOSE_MUSIC 		6

#define STDIN	0
#define STDOUT	1

#define HELP_COMMAND	"help"
#define SET_TIME_COMMAND	"stime"
#define GET_TIME_COMMAND	"time"
#define SET_SCREENSAVER_COMMAND	"ss"
#define GET_CPU_VENDOR_COMMAND	"cpuid"
#define PLAY_TEST_COMMAND "playtest"
#define KEYBOARD_SOUND_COMMAND "rkeyboard"
#define CHOSE_MUSIC_COMMAND "choosemusic"

#define MUSIC_ZERO 0
#define MUSIC_ONE 1
#define MUSIC_TWO 2
#define MUSIC_THREE 3
#define MUSIC_FOUR 4

typedef struct date {
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
   	uint8_t minute;
   	uint8_t second;
} date;

#endif

