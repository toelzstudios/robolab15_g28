#include "../h/main.h"
#include "../h/functions.h"
#include "../h/search.h"
#include "../src/search.c"

#include "../h/card.h"
#include "../src/card.c"

#include "../h/list.h"
#include "../src/list.c"




TASK( OSEK_Main_Task) {
	init();
	/*
	if(exploration()){
		wait(10000);
	}
	*/


	while(0){
		print_int(0,0,ecrobot_get_light_sensor(NXT_PORT_S3));
		wait(10);
		display_clear;
	}

	//drive_to_crossroad();

	robot r;
	set_robot(&r);
	//run_by_card(&r);

	runbot(&r);




	/*while(1){

	Robot_Move(MYSOUTH);

	print_int(0,0,Robot_GetIntersections());
	Robot_Move(MYSOUTH);
	Robot_Move(MYNORTH);
	Robot_Move(MYNORTH);
	wait(10);


	}*/

/*	int help = 0;
	while (1) {
		drive_to_crossroad();
		beep();
		help = exploration();
		turn_north();

		drive_to_crossroad();
		beep();
		help = exploration();
		turn_east();


		drive_to_crossroad();
		beep();
		help = exploration();
		turn_south();


		drive_to_crossroad();
		beep();
		help = exploration();
		turn_west();


		drive_to_crossroad();
		beep();
		turn_south();


		drive_to_crossroad();
		beep();
		turn_east();


		drive_to_crossroad();
		beep();
		turn_north();
		drive_to_crossroad();
		beep();
		turn_west();

								} */
	}




