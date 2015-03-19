/*
 * card.h
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#ifndef C_H_CARD_H_
#define C_H_CARD_H_


#include "search.h"

#define START 84


typedef struct card {
	int map[169];
	int cur_pos;
} card;


void init_card(card*);
void set_state(card*, int, int, int);
void print_card(card*);
void print_row(card*, int);
int get_state(card*, int, int);
void set_global_envoriment(card*);
void set_local_envoriment(card*, int, int);
int koord_to_i(int, int);
void i_to_koord(point *p, int i);



#endif /* C_H_CARD_H_ */
