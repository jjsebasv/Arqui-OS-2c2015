/* Sounds and music data base */
/*
	To add a song, just add a struc song to de songs array.
	A song is formed in the following way:
		flag bit: 1 indicates the end of the song's database
		song name: the name of the song
		score: int array where i is the chord and i++ the duration of the chord
			last element should be -1 to indicate the end of the score
			chord timming [for non musician users]:
				corchet - 1 beat
				quaver - half beat
				semiquaver - half quaver
				demisemequaver - half semiquaver
				minim - 2 beats
				semibreve - 4 beats 
*/

#include "defines.h"

struct song songs[] = {
	{0, "two per ten", {B, CORCHET, A, CORCHET, G, MINIM, B, CORCHET, A, CORCHET, G, CORCHET, REST, CORCHET, G, QUAVER, G, QUAVER, G, QUAVER, G, QUAVER, A, QUAVER, A, QUAVER, A, QUAVER, A, QUAVER, B, CORCHET, A, CORCHET, G, MINIM, -1}},
	{0, "joysong", {247, 6000, 262, 5000, 294, 4000, 294,4000,262,4000, 262,4000, 247,4000, 220,4000, 196,4000, 196,4000, 196,4000, 220,4000, 262,4000, 262,4000, 262,4000, 220,4000,220,4000, -1}},
	{0, "happy birthday", {C,SEMIQUAVER, C, SEMIQUAVER, D, CORCHET, C,CORCHET, E, CORCHET, D, CORCHET,C, CORCHET,C, CORCHET,D, CORCHET,C, CORCHET,F, CORCHET,E, CORCHET,C, CORCHET,C, CORCHET,A, CORCHET,F, CORCHET, F, CORCHET,F, CORCHET,E, CORCHET,D, CORCHET,A_SHARP, QUAVER,A_SHARP, QUAVER,A, CORCHET,F, CORCHET,G, CORCHET,F,CORCHET, -1 }},
	{1, "last", {-1}}
};
