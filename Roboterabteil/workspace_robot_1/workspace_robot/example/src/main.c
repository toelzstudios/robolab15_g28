#include "../h/main.h"

#include "../h/functions.h"

#include "../h/search.h"
#include "../src/search.c"

#include "../h/card.h"
#include "../src/card.c"

#include "../h/list.h"
#include "../src/list.c"


TASK( OSEK_Main_Task) {
	init();			// Initialisierung des Roboters

	while(0){
		print_int(0,0,ecrobot_get_light_sensor(NXT_PORT_S3));
		wait(10);
		display_clear;
	}

	robot r;
	set_robot(&r);
	runbot(&r);		//Start des Suchprogramms
	while(1){
		beep();
	}
}




