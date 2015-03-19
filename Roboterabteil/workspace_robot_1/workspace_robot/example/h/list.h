/*
 * list.h
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#ifndef LIST_H_
#define LIST_H_

#define MYNORTH 1
#define MYSOUTH 2
#define MYWEST 3
#define MYEAST 4
#define MYBREAK 5

#define No 16
#define So 32
#define NS 48
#define We 64
#define NW 80
#define SW 96
#define NSW 112
#define Ea 128
#define NE 144
#define ES 160
#define NES 176
#define EW 192
#define NEW 208
#define ESW 224
#define NESW 240



typedef struct point {
	int x,y;
}point;

typedef struct intersec {
    int North, West, East, South;
}intersec;

typedef struct robot {
	point cur_pos;
	int sel_dir, no_cross;
} robot;

typedef struct list_elem *list;
typedef struct list_elem {
	point p;
	int North, West, South, East;
	list next;
} list_elem;



list insert_l(list*, point, intersec);
void delete_list(list*);
int comp_p(point, point);
int exist_list(list*, point);



#endif /* LIST_H_ */
