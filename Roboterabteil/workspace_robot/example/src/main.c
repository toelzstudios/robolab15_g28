#include "../h/main.h"
//#include "ecrobot_interface.h"
int winkelconst = 180;
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

void wait(unsigned long int ms) {
	systick_wait_ms(ms);
}
int is_line() {
	return ecrobot_get_light_sensor(NXT_PORT_S3) > 600;
}
void beep() {
	ecrobot_sound_tone(220, 100, 100);
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


void stop_motor() {
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
}

void move(int speed) {
	nxt_motor_set_speed(NXT_PORT_B, speed, 0);
	nxt_motor_set_speed(NXT_PORT_C, speed, 0);
}

/* positiv: links herum
 * negativ: rechts herum
 * */
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
int touched(){
	return ecrobot_get_touch_sensor(NXT_PORT_S1) || ecrobot_get_touch_sensor(NXT_PORT_S4);
}

void token(){
	stop_motor();
	beep();
	wait(10000);
	//token counter aufrufen!!!

}
int search_line() {
	int i;
	int found = 0;
	int max = 6;
	int angle = 3;

	display_goto_xy(0, 0);
	display_int(found, 1);
	display_update();

	wait(200);
	for (i = 0; i < max; i++) {
		rotate_l(angle, 65);
		if (is_line()) {
			found = 1;
			display_goto_xy(0, 0);
			display_int(found, 1);
			display_update();
			wait(200);
			return found;
		}
		systick_wait_ms(400);
	}
	display_goto_xy(0, 0);
	display_int(found, 1);
	display_update();

	if (found == 1) { return found;}
		rotate_r(angle*(max+1), 65);
		int k=0;
		max = 6,
		angle = 3;
		for (k = 0; k < max; k++) {
			rotate_r(angle, 65);
			if (is_line()) {
								found = 1;
				return found;
			}

		systick_wait_ms(400);
	}
	rotate_l(angle*max, 65);
	return found;

}
int search_line2() {
	int found = 0;
	int max = 20;

	display_goto_xy(0, 3);
	display_int(found, 1);
	display_update();

	wait(200);
	found = rotate_to_line_l(max, 65);
	found =is_line();
	display_goto_xy(0, 3);
	display_int(found, 1);
	display_update();

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

		return found_forward + found_right*10 +found_control*100+found_left*1000;
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

TASK( OSEK_Main_Task) {
	print_string(0, 3, "Project - X");


	ecrobot_set_light_sensor_active(NXT_PORT_S3);

	int hallo = 0;

	while (1) {
		if (is_line()) {
			move(65);
			if (touched()) {token();}
		} else {
			stop_motor();
			hallo = search_line2();
			display_goto_xy(1, 1);
			display_int(hallo, 1);
			display_update();

			if (hallo < 1) {
				display_goto_xy(0, 1);
				display_string("Kreuzung entdeckt");
				display_update();

				junction(65);
				beep();
				hallo = exploration();
				turn_west();

				//rotate_to_line_l(720,65);
				//rotate_r(90, 65);
				hallo = search_line2();
				//junction(65);
			}
		}


	}
}








