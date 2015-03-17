#include "../h/main.h"
//#include "ecrobot_interface.h"

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
	int w_degree = (int) (degree / 90. * 155);
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

void rotate_r(int degree, int speed) {
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int status = 1;
	int w_degree = (int) (degree / 90. * 155);
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

int is_line() {
	return ecrobot_get_light_sensor(NXT_PORT_S3) > 600;
}

int search_line(int x) {
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
		rotate_r(angle*max, 65);
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
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
 int hallo = 0;
	while (1) {
		if (is_line()) {
			move(65);
		} else {
			stop_motor();
			hallo = search_line(0);
			display_goto_xy(1, 1);
						display_int(hallo, 1);
						display_update();
			if (hallo < 1) {
				display_goto_xy(0, 0);
				display_string("Kreuzung entdeckt");
				display_update();

				junction(65);
				beep();
				rotate_r(90, 65);
				junction(65);
			}
		}
		/* 500msec wait */
		wait(200);
	}
	while(1){

			display_goto_xy(0, 0);
			display_int(3, 1);
			display_update();
		}

}
