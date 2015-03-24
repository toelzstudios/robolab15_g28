#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdlib.h>
#include "kernel.h"
/* Will be generated: */
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "search.h"
#include "card.h"
#include "list.h"

#define No 16
#define So 32
#define We 64
#define Ea 128


const int winkelconst   = 180;
const int speedconst    = 70; // 65
const int junctionspeed = 60;
int token = 0;

int orientation = 0;

/* Variable, die aktuelle Himmelsrichtung speichert, in die der Roboter zeigt
 * dabei entspricht:
 * 0 Norden
 * 1 Osten
 * 2 Süden
 * 3 Westen
 */

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
}

/* Verändert Himmels-zeige-Richtung
 *
 *  Eingabe: Anzahl der Vierteldrehung
 *  dabei entspricht: 	positiv: nach rechts gedreht
 *  					negativ: nach links  gedreht
 *
 */
void change_direction(int x){
	orientation += x;
	if (orientation<0){
		orientation += 4;
	}
	if (orientation>3){
		orientation += -4;
	}
}

void ecrobot_device_initialize(void) {
}

void ecrobot_device_terminate(void) {
}


void print_string(int x, int y, char *msg) {
	display_goto_xy(x, y);
	display_string(msg);
	display_update();
}

void print_int(int x, int y, int value) {
	display_goto_xy(x, y);
	display_int(value, 1);
	display_update();
}

void beep() {
	ecrobot_sound_tone(220, 100, 100);
}

void init() {
	print_string(0, 2, "-----------");
	print_string(0, 3, "Project - X");
	print_string(0, 4, "-----------");
	ecrobot_set_light_sensor_active(NXT_PORT_S4);
}

int is_line() {
	int i;
	int help=0;
	for (i=0; i<2;i++){
		help += ecrobot_get_light_sensor(NXT_PORT_S4);
	}
	help /=2;
	return help > 550; //ehemals 600
}

void wait(unsigned long int ms) {
	systick_wait_ms(ms);
}


void stop_motor() {
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
}

void move(int speed) {
	nxt_motor_set_speed(NXT_PORT_B, speed, 1);
	nxt_motor_set_speed(NXT_PORT_C, speed, 1);
}

/*
 * Links herum rotieren
 * degree: Winkel in Grad
 * speed: Geschwindigkeit der Motoren
 */
void rotate_l(int degree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (degree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}

}

/*
 * Links herum rotieren bis Linie erreicht
 * degree: Maximaler Winkel in Grad
 * speed: Geschwindigkeit der Motoren
 * return: Gibt zurück, ob Linie erkannt wurde
 */
int rotate_to_line_l(int maxdegree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (maxdegree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
		if (is_line()){
			stop_motor();
			return 1;
		}
	}
	return 0;
}

/*
 * Rechts herum rotieren
 * degree: Winkel in Grad
 * speed: Geschwindigkeit der Motoren
 */
void rotate_r(int degree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (degree / 90. * winkelconst);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, -speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}

}

/*
 * Rechts herum rotieren bis Linie erreicht
 * degree: Maximaler Winkel in Grad
 * speed: Geschwindigkeit der Motoren
 * return: Gibt zurück, ob Linie erkannt wurde
 */
int rotate_to_line_r(int maxdegree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (maxdegree / 90. * winkelconst);
	while (status) {
	status = 0;
					if (nxt_motor_get_count(NXT_PORT_B) > -w_degree) {
						nxt_motor_set_speed(NXT_PORT_B, -speed, 1);
						status = 1;
					} else {
						nxt_motor_set_speed(NXT_PORT_B, 0, 1);
					}
					if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
						nxt_motor_set_speed(NXT_PORT_C, speed, 1);
						status = 1;
					} else {
						nxt_motor_set_speed(NXT_PORT_C, 0, 1);
					}
		if (is_line()){
			stop_motor();
			return 1;
		}

	}
	return 0;
}

/*
 * Gibt zurück, ob Berühungssensor betätigt
 */
int touched(){
	return ecrobot_get_touch_sensor(NXT_PORT_S1) || ecrobot_get_touch_sensor(NXT_PORT_S2) || ecrobot_get_touch_sensor(NXT_PORT_S3);
}

/*
 * Aufgaben, die beim Erkennen eines Tokens ausgeführt werden sollen:
 */
void token_found(){
	stop_motor();			// Anhalten
	token++;				// Counter hochzählen
	beep();					// Piepen, 1s bei 220 Hz
	wait(10000);			// 10s warten


}

/*
 * Linienfindung:
 * Eingabe:  Suchradius in grad
 * Rückgabe: 	0... keine Linie gefunden
 * 				1... Linie gefunden
 * 	pendelt zuerst nach links, dann nach rechts
 */
int search_line(int max) {
	int found = 0;
	int speed = 30;
	found = rotate_to_line_l(max, speed);
	found =is_line();

	wait(200);
	if (found == 1) { return 1;}
	else {found=rotate_to_line_r(3*max, speed);}

	if (found == 0){
		found = rotate_to_line_l(4*max, speed);

	}
	if (found == 0){
		rotate_r(2*max, speed);

		}

	wait(200);
	return found;

}

/*
 * In die Kreuzung einfahren
 */
void junction(int speed) {
	int status = 1;
	int w_degree = 225;
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while (status) {
		status = 0;
		if (nxt_motor_get_count(NXT_PORT_B) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_B, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, speed, 1);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}
}

/*
 * Kreuzung untersuchen
 * Rückgabe: 	entdeckte Abzweige, Codierung siehe #defines,
 * 				in globalen Himmelsrichtungen
 */
int exploration(){
	int found_left;
	int found_right;
	int found_forward;
	int found_control;

	int exp_speed = speedconst;

	rotate_l(45, exp_speed);

	found_forward = rotate_to_line_r(90, exp_speed);

	//print_int(0,0,found_forward);
	wait(50);
	if (found_forward){
		rotate_r(45, exp_speed);
	}

	found_right = rotate_to_line_r(90, exp_speed);
	wait(50);
		if (found_right){
			rotate_r(45, exp_speed);
		}



	found_control = rotate_to_line_r(90, exp_speed);
	wait(50);
	if (found_control){
			rotate_r(45, exp_speed);
		}



	found_left = rotate_to_line_r(100, exp_speed); //ehemals 135
	wait(50);
	if (found_left){
			rotate_r(90, exp_speed);
		} else {rotate_r(30, exp_speed);}
		display_clear(0);

		if (found_left){
			print_string(1, 1, "LINKS");
		}

		if (found_right){
			print_string(1, 3, "RECHTS");
		}

		if (found_forward){
			print_string(1, 5, "GERADEAUS");
		}

		if (found_control){
			print_string(1, 4, "Hinten");
		}

		int found_north = 0;
		int found_east  = 0;
		int found_south = 0;
		int found_west  = 0;

		if(found_forward){
			switch(orientation) {
					case 0: found_north = 1; break;
					case 1: found_east  = 1; break;
					case 2: found_south = 1; break;
					case 3: found_west  = 1; break;
				}
		}
		if(found_right){
				switch(orientation) {
					case 3: found_north = 1; break;
					case 0: found_east  = 1; break;
					case 1: found_south = 1; break;
					case 2: found_west  = 1; break;
				}
		}
		if(found_control){
				switch(orientation) {
					case 2: found_north = 1; break;
					case 3: found_east  = 1; break;
					case 0: found_south = 1; break;
					case 1: found_west  = 1; break;
				}
		}

		if(found_left){
				switch(orientation) {
					case 1: found_north = 1; break;
					case 2: found_east  = 1; break;
					case 3: found_south = 1; break;
					case 0: found_west  = 1; break;
				}
		}

		int back;
		back = found_north*No + found_south*So + found_east*Ea + found_west*We;
		print_int(3, 7, back);
		return back;
}

/*
 * Funktion lässt Roboter nach links abbiegen
 */

void turn_left(){
	int found;
	rotate_l(45,speedconst);
	found = rotate_to_line_l(90,speedconst);

	change_direction(-1);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

/*
 * Funktion lässt Roboter nach rechts abbiegen
 */
void turn_right(){
	int found;
	rotate_r(45,speedconst);
	found = rotate_to_line_r(90,speedconst);
	if (found ==0){
		rotate_l(45,speedconst);
	}
	change_direction(1);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

/*
 * Funktion lässt Roboter umkehren
 */
void turn_back(){
	int found;
	rotate_r(135,speedconst);
	found = rotate_to_line_r(90,speedconst);

	change_direction(2);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

/*
 * Funktion lässt Roboter geradeaus fahren
 */
void turn_forward(){
	int found;
	rotate_l(30,speedconst);
	found = rotate_to_line_r(60,speedconst); //130

	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}


/*
 * Funktion lässt Roboter nach Norden abbiegen
 */
void turn_north(){
	switch(orientation) {
		case 0: turn_forward(); break;
		case 1: turn_left(); break;
		case 2: turn_back(); break;
		case 3: turn_right(); break;
	}
	orientation = 0;
}

/*
 * Funktion lässt Roboter nach Westen abbiegen
 */
void turn_west(){
	switch(orientation) {
		case 3: turn_forward(); break;
		case 0: turn_left(); break;
		case 1: turn_back(); break;
		case 2: turn_right(); break;
	}
	orientation = 3;
}

/*
 * Funktion lässt Roboter nach Süden abbiegen
 */
void turn_south(){
	switch(orientation) {
		case 2: turn_forward(); break;
		case 3: turn_left(); break;
		case 0: turn_back(); break;
		case 1: turn_right(); break;
	}
	orientation = 2;
}

/*
 * Funktion lässt Roboter nach Osten abbiegen
 */
void turn_east(){
	switch(orientation) {
		case 1: turn_forward(); break;
		case 2: turn_left(); break;
		case 3: turn_back(); break;
		case 0: turn_right(); break;
	}
	orientation = 1;
}


/*
 * Funktion lässt Roboter bis zur nächsten Kreuzung fahren (inklusive Tokenerkennung)
 */
void drive_to_crossroad(){
	nxt_motor_set_count(NXT_PORT_B, 0);
	int speedy = 90;
	while(1){

		if (is_line()) {
			move(speedy); //65
			if(nxt_motor_get_count(NXT_PORT_B) < 300){
				move(speedy+15);//80
				wait(30); //100
			}
			wait(10); // 30
			if (touched()) {
				display_clear(0);
				print_string(0, 3, "Token gefunden");
				token_found();
			}

		} else {
				stop_motor();
				if (!search_line(8)) {
					display_clear(0);
					print_string(0,1,"Kreuzung entdeckt");

					junction(junctionspeed); //65
					//beep();
					break;
				}
			}

	}
}

/*
 * Funktion zur Ansteuerung
 */

void Robot_Move(int direction){
	switch(direction) {
			case MYNORTH: turn_north(); break;
			case MYSOUTH: turn_south(); break;
			case MYWEST:  turn_west(); break;
			case MYEAST:  turn_east(); break;
		}
	drive_to_crossroad();

}

int Robot_GetIntersections(){
	return exploration();
}

void set_robot(robot *r){
	point p;
	p.x = 0;
	p.y = 0;
	r->cur_pos = p;
	r->sel_dir = MYNORTH;
	r->no_cross = 0;
}

int explorate_orientation(int orient) {
	int help = 0;
	print_int(0,0,orient);

	return exploration();

	switch(orient) {
		case No: turn_north(); rotate_l(10,speedconst );
			if (rotate_to_line_r(70,speedconst)){
				help = No;
			} else {
				wait(50);
				rotate_l(60,speedconst);
			}
			print_int(0,0,help);
			return help;

		case So: turn_south(); rotate_l(10,speedconst); if (rotate_to_line_r(70,speedconst)){
			if (rotate_to_line_r(70,speedconst)){
				help = So;
			} else {
				wait(50);
				rotate_l(60,speedconst);
			}
			print_int(0,0,help);
			return help;

		case Ea: turn_east(); rotate_l(10,speedconst);  wait(50);
			if (rotate_to_line_r(70,speedconst)){
				help = Ea;
			} else {
				wait(50);
				rotate_l(60,speedconst);
			}
			print_int(0,0,help);
			return help;

		case We: turn_west(); rotate_l(10,speedconst);
			wait(50);
			if (rotate_to_line_r(70,speedconst)){
				help = We;
			} else {
				wait(50);
				rotate_l(60,speedconst);
			}
			print_int(0,0,help);
			return help;

		case NS:
			turn_north();  rotate_r(50,speedconst);  orientation = 2;
			wait(50);
			help = No*rotate_to_line_l(90,speedconst);
			wait(50);
			if (help){
				rotate_l(135,speedconst);
			} else {
				rotate_l(45,speedconst);
			}
			wait(50);
			help = help + rotate_to_line_l(90,speedconst)*So;
			print_int(0,0,help);
			return help;

		case EW:
			turn_west();  rotate_r(50,speedconst);  orientation = 1;
			wait(50);
			help = We*rotate_to_line_l(90,speedconst);
			wait(50);
			if (help){
				rotate_l(135,speedconst);
			} else {
				rotate_l(45,speedconst);
			}
			wait(50);
			help = help + rotate_to_line_l(90,speedconst)*Ea;
			print_int(0,0,help);
			return help;




		case NW:
			if (orientation ==0 || orientation ==1 ){
				turn_north();  rotate_r(60,speedconst);  orientation = 3;
				wait(50);
				help = No*rotate_to_line_l(90,speedconst);
				wait(50);
				if (help){
					rotate_l(45,speedconst);
				}
				wait(50);
				help = help + rotate_to_line_l(90,speedconst)*We;
			} else {
				turn_west(); wait(1000); rotate_l(60,speedconst);  orientation = 0;
				wait(1000);
				help = We*rotate_to_line_r(90,speedconst);
				wait(1050);
				if (help){
					rotate_r(45,speedconst);
				}
				wait(1050);

				if(rotate_to_line_r(90,speedconst)){
					help += No;
				} else {
					rotate_l(45,speedconst);
				}

			}

			print_int(0,0,help);
			wait(500);
			return help;

		case NE:
			if (orientation == 0 || orientation == 3 ){
				turn_north();  rotate_l(60,speedconst);  orientation = 1;
				wait(50);
				help = No*rotate_to_line_r(90,speedconst);
				wait(50);
				if (help){
					rotate_r(45,speedconst);
				}
				wait(50);
				help = help + rotate_to_line_r(90,speedconst)*Ea;
			} else {
				turn_east();  wait(1000);rotate_r(30,speedconst);  wait(1000);orientation = 0;
				wait(50);wait(1000);
				help = Ea*rotate_to_line_l(90,speedconst);
				wait(50);wait(1000);
				if (help){
					rotate_l(45,speedconst);
				}
				wait(50);wait(1000);
				help = help + rotate_to_line_l(90,speedconst)*No;
			}


			print_int(0,0,help);
			return help;


		case SW:
			if (orientation == 2 || orientation == 1 ){
				turn_south();  rotate_l(60,speedconst);  orientation = 3;
				wait(50);
				help = So*rotate_to_line_r(90,speedconst);
				wait(50);
				if (help){
					rotate_r(45,speedconst);
				}
				wait(50);
				help = help + rotate_to_line_r(90,speedconst)*We;
			} else {
				turn_west();  rotate_r(60,speedconst);  orientation = 3;
				wait(50);
				help = We*rotate_to_line_l(90,speedconst);
				wait(50);
				if (help){
					rotate_l(45,speedconst);
				}
				wait(50);
				help = help + rotate_to_line_l(90,speedconst)*So;
			}
			print_int(0,0,help);
			return help;

		case ES:
			if (orientation == 0 || orientation == 1 ){
				turn_east();  rotate_l(60,speedconst);  orientation = 2;
				wait(50);
				help = Ea*rotate_to_line_r(90,speedconst);
				wait(50);
				if (help){
					rotate_r(45,speedconst);
				}
				wait(50);
				help = help + rotate_to_line_r(90,speedconst)*So;
			} else {
				turn_south();  rotate_r(60,speedconst);  orientation = 1;
				wait(50);
				help = So*rotate_to_line_l(90,speedconst);
				wait(50);
				if (help){
					rotate_l(45,speedconst);
				}
				wait(50);
				help = help + rotate_to_line_l(90,speedconst)*Ea;
			}

			print_int(0,0,help);
			return help;

		case NSW:
			rotate_r(135,speedconst);  orientation = 2;
			wait(50);
			help = No*rotate_to_line_l(90,speedconst);
			wait(50);
			if (help){
				rotate_l(45,speedconst);
			}
			wait(50);
			if(rotate_to_line_l(90,speedconst)){
				help = help + We;
				rotate_l(45,speedconst);
			}
			wait(50);
			if(rotate_to_line_l(90,speedconst)){
				help = help + So;
			} else {
				rotate_r(45,speedconst);
			}
			print_int(0,0,help);
			orientation = 2;
			return help;


		case NES:
			rotate_r(135,speedconst);  orientation = 2;
			wait(50);
			help = So*rotate_to_line_l(90,speedconst);
			wait(50);
			if (help){
				rotate_l(45,speedconst);
			}
			wait(50);
			if(rotate_to_line_l(90,speedconst)){
				help = help + Ea;
				rotate_l(45,speedconst);
			}
			wait(50);
			if(rotate_to_line_l(90,speedconst)){
				help = help + No;
			} else {
				rotate_r(45,speedconst);
			}
			print_int(0,0,help);
			orientation = 0;
			return help;
		case NEW:
			rotate_r(135,speedconst);  orientation = 2;
			wait(50);
			help = Ea*rotate_to_line_l(90,speedconst);
			wait(50);
			if (help){
				rotate_l(45,speedconst);
			}
			wait(50);
			if(rotate_to_line_l(90,speedconst)){
				help = help + No;
				rotate_l(45,speedconst);
			}
			wait(50);
			if(rotate_to_line_l(90,speedconst)){
				help = help + We;

			} else {
				rotate_r(45,speedconst);
			}
			print_int(0,0,help);
			orientation = 3;
			return help;

		case ESW:
			rotate_r(135,speedconst);  orientation = 2;
			wait(50);
			help = We*rotate_to_line_l(90,speedconst);
			wait(50);
			if (help){
				rotate_l(45,speedconst);
			}
			wait(50);
			if(rotate_to_line_l(90,speedconst)){
				help = help + So;
				rotate_l(45,speedconst);
			}
			wait(50);
			if(rotate_to_line_l(90,speedconst)){
				help = help + Ea;

			} else {
			rotate_r(45,speedconst);
			}
			print_int(0,0,help);
			orientation = 1;
			return help;

		case 240: return exploration();

		default: return 0;

	}
	return 0;
	}
}

int get_intersec(int calc_cross) {
	int back_val = calc_cross;
	back_val += explorate_orientation(240-calc_cross);

	return back_val;
}


#endif /* FUNCTIONS_H_ */
