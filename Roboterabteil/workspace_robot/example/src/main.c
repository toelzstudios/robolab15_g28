#include "../h/main.h"

const int winkelconst = 180;
int orientation = 0;
/* 0 norden
 * 1 osten
 * 2 süden
 * 3 westen
 */

const int FORW = 1, RIGHT = 2, CONTR = 4, LEFT= 8;

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

void wait(unsigned long int ms) {
	systick_wait_ms(ms);
}

void beep() {
	ecrobot_sound_tone(220, 100, 100);
}

void init() {
	print_string(0, 2, "-----------");
	print_string(0, 3, "Project - X");
	print_string(0, 4, "-----------");
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
}

int is_line() {
	return ecrobot_get_light_sensor(NXT_PORT_S3) > 600;
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
			//nxt_motor_set_speed(NXT_PORT_B, 0, 0);
		}
		if (nxt_motor_get_count(NXT_PORT_C) > -w_degree) {
			nxt_motor_set_speed(NXT_PORT_C, -speed, 0);
			status = 1;
		} else {
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
			//nxt_motor_set_speed(NXT_PORT_C, 0, 0);
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
 * max: Maximaler Winkel
 */
int search_line() {
	int found = 0;
	int max = 20;

	print_int(0, 3, found);
	wait(200);
	found = rotate_to_line_l(max, 65);
	found =is_line();
	print_int(0, 3, found);

	wait(200);
	if (found == 1) { return 1;}
	else {found=rotate_to_line_r(2*max, 65);}
	wait(200);
	if (found == 0){
		rotate_l(max, 65);
	}
	wait(200);
	return found;

}

/*
 * In die Kreuzung einfahren
 */
void junction(int speed) {
	int status = 1;
	int w_degree = 230;
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
		print_string(0, 3, "vorn");
		print_string(0, 4, "rechts");
		print_string(0, 5, "hinten");
		print_string(0, 6, "links");

		print_int(6, 3, found_forward);
		print_int(6, 4, found_right);
		print_int(6, 5, found_control);
		print_int(6, 6, found_left);

		wait(4000);

		//return found_forward + found_right*10 +found_control*100+found_left*1000;
		return found_forward*FORW + found_right*RIGHT + found_control*CONTR + found_left*LEFT;
}

void turn_left(){
	int found;
	rotate_l(45,65);
	found = rotate_to_line_l(90,65);
	if (found ==0){
		beep_error();
	}
	change_direction(-1);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

void turn_right(){
	int found;
	rotate_r(45,65);
	found = rotate_to_line_r(90,65);
	if (found ==0){
		beep_error();
	}
	change_direction(1);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

void turn_back(){
	int found;
	rotate_r(135,65);
	found = rotate_to_line_r(90,65);
	if (found ==0){
		beep_error();
	}
	change_direction(2);
	print_string(0,7,"Richtung");
	print_int(9,7, orientation);

}

void turn_forward(){
	int found;
	rotate_l(30,65);
	found = rotate_to_line_r(130,65);
	if (found ==0){
		beep_error();
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

int drive_to_crossroad(){
	while(1){
		int line_state;
		if (is_line()) {
			move(65);
			if (touched()) {
				token();
				print_string(0, 3, "Token gefunden");
				return 1;
			} else {
				stop_motor();
				line_state = search_line();
				if (line_state ==0) {
					print_string(0,1,"Kreuzung entdeckt");
					beep();
					return 0;
				}
			}
		}
	}
}

void figur() {
	int help = 0;
	if(drive_to_crossroad()){
		beep();
		help = exploration();
		if(help & LEFT) {
			turn_left();
		} else {
			turn_right();
		}
		//turn_west();

		} else {

		}
	}
}



