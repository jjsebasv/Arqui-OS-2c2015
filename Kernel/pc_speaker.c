/* Las funciones set_speaker_frec, play_speaker y stop_speaker
 * estan basadas en el codigo de ejemplo de http://wiki.osdev.org/PC_Speaker */

int set_speaker_freq(int freq){

	int div = 1193182 / freq; /* 1193182 is the PIT frequency. Div is the reset counter */
	
	_outb(0x43,0xb6); /* sets the mode of the PIT. 0xb6 = 10/11/011/0 */
	_outb(0x42, (short int)div); /* sets frec on channel 2 of the PIT */
	_outb(0x42, (short int)(div >> 8));

	return 1;

}

int play_speaker(int ms){

	short int tmp;

	tmp = _inb(0x61);

	if (tmp != (tmp | 3)){/* sets bit 0 of port 0x61 to 1 */
		_outb(0x61, tmp | 3);
	}

	wait(ms);
	stop_speaker();

	return 1;
}

void stop_speaker(){

	short int tmp;
	tmp = (_inb(0x61) & 0xFC); /* sets bit 0 of port 0x61 to 0 */
	_outb(0x61, tmp);

}


