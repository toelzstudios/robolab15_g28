#include "../h/main.h"

#include "../h/functions.h"

#include "../h/search.h"
#include "../src/search.c"

#include "../h/card.h"
#include "../src/card.c"

#include "../h/list.h"
#include "../src/list.c"

// Start des Hauptprogramms

TASK( OSEK_Main_Task) {
	init();			// Initialisierung des Roboters





	/*if(explorate_orientation(64)){
		wait(1000);
		turn_east();
	}
	wait(1000);
*/
	int help;
	//turn_east();
	//help = explorate_orientation(NE);
	//wait(10000);

	init_logfile(&logbook);
	set_robot(&r);
	runbot(&r);		//Start des Suchprogramms

	beep();
	wait(1000);

	// lustiges Piepen




	while(1){
		int i = 0;
		for (i=0; i<20;i++){
			print_int(0,0,i*10);
			ecrobot_sound_tone(10*i, 100, 100);
			wait(100);
		}
		for (i=20; i>0;i--){
			print_int(0,0,i*10);
			ecrobot_sound_tone(10*i, 100, 100);
			wait(100);
		}

		for (i=0; i<20;i++){
			print_int(0,0,i*10);
			ecrobot_sound_tone(100*i, 100, 10);
			wait(100);
		}
		for (i=20; i>0;i--){
			print_int(0,0,i*10);
			ecrobot_sound_tone(100*i, 100, 10);
			wait(100);
		}
		for (i=0; i<20;i++){
			print_int(0,0,i*10);
			ecrobot_sound_tone(1000*i, 100, 10);
			wait(100);
		}
		for (i=20; i>0;i--){
			print_int(0,0,i*10);
			ecrobot_sound_tone(1000*i, 100, 10);
			wait(100);
			}
	}
}
/*
// Notfallprogramm
TASK(OSEK_Task_Background) {
	  while(1){
		beep();
		systick_wait_ms(500);
	  }
}
*/


