#define	REST	50000
#define C		262
#define C_SHARP	277
#define D 		294
#define D_SHARP 311
#define E 		330
#define F 		349
#define F_SHARP 370
#define G 		392
#define G_SHARP	415
#define A 		440
#define A_SHARP 466
#define B 		494
#define HI_C	523

#define DEMISEMIQUAVER 	 1500
#define SEMIQUAVER		 3000
#define QUAVER	  		 6000
#define CORCHET   		 12000
#define MINIM 	  		 24000
#define SEMIBREVE 		 48000

struct song {
	int last;
  	char  name[50];
  	int   score[100];
};