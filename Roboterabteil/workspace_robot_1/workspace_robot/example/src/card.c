/*
 * card.c
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#include <stdlib.h>
#include <stdio.h>
#include "../h/card.h"


int koord_to_i(int x, int y) {
	int i;
	if ((x<(-6))||(x>6)||(y<(-6))||(y>6)) {
		//printf("ERROR over range\n");
		return 0;
	}
	x += 6;
	y -= 6;
	y = -y;
	i = y*13 + x;
	return i;
}
void print_row(card* c, int row) {
	int begin = 13*row;
	int index;
	if (row > 12) {
		printf("ERROR row over limit");
		return;
	}
	for (index=begin; index<begin+13; index++) {
		printf(" %i", c->map[index]);
	}
}
void print_card(card *c) {
	int i = 0;
	for (i;i<13;i++) {
		print_row(c, i);
		printf("\n");
	}
}
void init_card(card *c) {
	int i;
	for (i=0;i<169;i++) {
		c->map[i] = 0;
	}
	c->map[START] = 1;
	c->cur_pos = START;
}
int get_state(card *c, int x, int y) {
	int i = koord_to_i(x,y);
	return c->map[i];
}
void set_state(card *c, int x, int y, int state) {
	int i = koord_to_i(x,y);
	c->map[i] = state;
}


void set_global_envoriment(card* c) {
	int x,y;
	intersec state;
	for (x=-6;x<6;x++) {
		for (y=-6;y<6;y++) {
			dechiff_intersec(&state, c->map[koord_to_i(x,y)]);
			if ((state.North)&&(!get_state(c, x,y+1))) c->map[koord_to_i(x, y+1)]=1;
			if ((state.South)&&(!get_state(c, x,y-1))) c->map[koord_to_i(x, y-1)]=1;
			if ((state.West)&&(!get_state(c, x-1,y))) c->map[koord_to_i(x-1, y)]=1;
			if ((state.East)&&(!get_state(c, x+1,y))) c->map[koord_to_i(x+1, y)]=1;
		}
	}
}
void set_local_envoriment(card* c, int x, int y) {
	intersec state;
	dechiff_intersec(&state, c->map[koord_to_i(x,y)]);
	if ((state.North)&&(!get_state(c, x,y+1))) c->map[koord_to_i(x, y+1)]=1;
	if ((state.South)&&(!get_state(c, x,y-1))) c->map[koord_to_i(x, y-1)]=1;
	if ((state.West)&&(!get_state(c, x-1,y))) c->map[koord_to_i(x-1, y)]=1;
	if ((state.East)&&(!get_state(c, x+1,y))) c->map[koord_to_i(x+1, y)]=1;
}

void i_to_koord(point *p, int i) {
	p->x = i%12 - 6;
	p->y = -((i- (p->x + 6))/12)+6;
}

