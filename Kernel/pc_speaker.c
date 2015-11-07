#include <stdint.h>

/* Las funciones set_speaker_frec, play_speaker y stop_speaker
 * estan basadas en el codigo de ejemplo de http://wiki.osdev.org/PC_Speaker */

int set_speaker_freq(int freq){

	int div = 1193182 / freq; /* 1193182 is the PIT frequency. Div is the reset counter */
	

	return 1;

}

int play_speaker(uint16_t f) {

	int freq = 1193182 / f;

	_outb(0xb6, 0x43); /* sets the mode of the PIT. 0xb6 = 10/11/011/0 */
	_outb((short int)freq, 0x42); /* sets frec on channel 2 of the PIT */
	_outb((short int)(freq >> 8), 0x42);

	uint8_t tmp = _inb(0x61);
	tmp = tmp | 3;
	_outb(tmp, 0x61);

	return 1;
}

void stop_speaker() {
	uint8_t tmp = _inb(0x61);
	tmp = tmp | 252;
	_outb(tmp, 0x61);
}


