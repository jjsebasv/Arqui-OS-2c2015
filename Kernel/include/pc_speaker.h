#ifndef _pc_speaker_
#define _pc_speaker_

int set_speaker_freq(int frec);
int play_speaker(uint16_t freq);
void stop_speaker();
void wait(int ms);

#endif
