#include "../h/main.h"
//#include "ecrobot_interface.h"
int winkelconst = 180;
/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
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
	wait(200);
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
	wait(200);
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
		wait(100);
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
	int w_degree = 212;
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

TASK( OSEK_Main_Task) {
	display_goto_xy(0, 0);
	display_string("Project - X");
	display_update();

	ecrobot_set_light_sensor_active(NXT_PORT_S3);

	int hallo = 0;

	while (1) {
		if (is_line()) {
			move(65);
			if (touched()) {beep();}
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
				rotate_to_line_l(720,65);
				//rotate_r(90, 65);
				junction(65);
			}
		}
		/* 500msec wait */
		wait(200);
	}
}








