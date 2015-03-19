/*
 * search.h
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#ifndef SEARCH_H_
#define SEARCH_H_


#include "list.h"
#include "card.h"

//insert_list(&visit_points, cur_p, cur_inter);


void dechiff(intersec*, int);

void select_direction(robot *r, intersec i);
void run_robot(robot*);
void run_by_card(robot*);
void get_nearest_unknown(point,card*,int , point*);
void runbot(robot*);



#endif /* SEARCH_H_ */
