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


const int winkelconst = 180;
int orientation = 0;
/* 0 norden
 * 1 osten
 * 2 süden
 * 3 westen
 */

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
}

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
	ecrobot_sound_tone(8220, 200, 100);
}

void init() {
	print_string(0, 2, "-----------");
	print_string(0, 3, "Project - X");
	print_string(0, 4, "-----------");
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
}

int is_line() {
	int i;
	int help=0;
	for (i=0; i<2;i++){
		help += ecrobot_get_light_sensor(NXT_PORT_S3);
	}
	help /=2;
	return help > 510; //ehemals 600
}

void wait(unsigned long int ms) {
	systick_wait_ms(ms);
}


void stop_motor() {
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
}

void move(int speed) {
	nxt_motor_set_speed(NXT_PORT_B, speed, 0);
	nxt_motor_set_speed(NXT_PORT_C, speed, 0);
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
			nxt_motor_set_speed(NXT_PORT_B, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 0);
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
			nxt_motor_set_speed(NXT_PORT_B, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 0);
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
			nxt_motor_set_speed(NXT_PORT_B, -speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, speed, 0);
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
						nxt_motor_set_speed(NXT_PORT_B, -speed, 0);
						status = 1;
					} else {
						nxt_motor_set_speed(NXT_PORT_B, 0, 1);
					}
					if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
						nxt_motor_set_speed(NXT_PORT_C, speed, 0);
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
	return ecrobot_get_touch_sensor(NXT_PORT_S1) || ecrobot_get_touch_sensor(NXT_PORT_S4);
}

/*
 * Aufgaben, die beim Erkennen eines Tokens ausgeführt werden sollen
 */
void token(){
	stop_motor();
	beep();
	wait(10000);
	//token counter aufrufen!!!

}

/*
 * Suche Linie
 */
int search_line(int max) {
	int found = 0;

	found = rotate_to_line_l(max, 65);
	found =is_line();

	wait(200);
	if (found == 1) { return 1;}
	else {found=rotate_to_line_r(3*max, 65);}

	if (found == 0){
		found = rotate_to_line_l(4*max, 65);

	}
	if (found == 0){
		rotate_r(2*max, 65);

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
			nxt_motor_set_speed(NXT_PORT_B, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
		}
		if (nxt_motor_get_count(NXT_PORT_C) < w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
		}
	}
}

/*
 * Kreuzung untersuchen
 * return: entdeckte Abzweige
 */
int exploration(){
	int found_left;
	int found_right;
	int found_forward;
	int found_control;

	rotate_l(45, 65);
	found_forward = rotate_to_line_r(90, 65);
	if (found_forward){
		rotate_r(45, 65);
	}

	found_right = rotate_to_line_r(90, 65);
		if (found_right){
			rotate_r(45, 65);
		}

	found_control = rotate_to_line_r(90, 65);
		if (found_control){
			rotate_r(45, 65);
		}

	found_left = rotate_to_line_r(135, 65);
		if (found_left){
			rotate_r(90, 65);
		}
		display_clear(0);
		/*print_string(0, 3, "vorn");
		print_string(0, 4, "rechts");
		print_string(0, 5, "hinten");
		print_string(0, 6, "links");

		print_int(6, 3, found_forward);
		print_int(6, 4, found_right);
		print_int(6, 5, found_control);
		print_int(6, 6, found_left);
		*/
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




		wait(50);

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
		//print_int(3, 7, back);
		return back;
}

void turn_left(){
	int found;
	rotate_l(45,65);
	found = rotate_to_line_l(90,65);
	while (found ==0){
		beep();
		wait(100);
	}
	change_direction(-1);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

void turn_right(){
	int found;
	rotate_r(45,65);
	found = rotate_to_line_r(90,65);
	while (found ==0){
		beep();
		wait(100);
	}
	change_direction(1);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

void turn_back(){
	int found;
	rotate_r(135,65);
	found = rotate_to_line_r(90,65);
	while (found ==0){
		beep();
		wait(100);
	}
	change_direction(2);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

void turn_forward(){
	int found;
	rotate_l(30,65);
	found = rotate_to_line_r(130,65);
	while (found ==0){
		beep();
		wait(100);
	}
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}



void turn_north(){
	switch(orientation) {
		case 0: turn_forward(); break;
		case 1: turn_left(); break;
		case 2: turn_back(); break;
		case 3: turn_right(); break;
	}
	orientation = 0;
}
void turn_west(){
	switch(orientation) {
		case 3: turn_forward(); break;
		case 0: turn_left(); break;
		case 1: turn_back(); break;
		case 2: turn_right(); break;
	}
	orientation = 3;
}
void turn_south(){
	switch(orientation) {
		case 2: turn_forward(); break;
		case 3: turn_left(); break;
		case 0: turn_back(); break;
		case 1: turn_right(); break;
	}
	orientation = 2;
}
void turn_east(){
	switch(orientation) {
		case 1: turn_forward(); break;
		case 2: turn_left(); break;
		case 3: turn_back(); break;
		case 0: turn_right(); break;
	}
	orientation = 1;
}

void drive_to_crossroad(){
	nxt_motor_set_count(NXT_PORT_B, 0);
	while(1){

		int line_state;
		if (is_line()) {
			move(65);
			if(nxt_motor_get_count(NXT_PORT_B) < 300){
				move(70);
				wait(100);
			}
			wait(30);
			if (touched()) {
				token();
				print_string(0, 3, "Token gefunden");
			}

		} else {
				stop_motor();
				line_state = search_line(5);

				if (line_state ==0) {
					print_string(0,1,"Kreuzung entdeckt");

					junction(65);
					beep();
					break;
				}
			}

	}
}


void Robot_Move(int direction){
	switch(direction) {
			case MYSOUTH: turn_south(); break;
			case MYNORTH: turn_north(); break;
			case MYWEST: turn_west(); break;
			case MYEAST: turn_east(); break;
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




#endif /* MAIN_H_ */
