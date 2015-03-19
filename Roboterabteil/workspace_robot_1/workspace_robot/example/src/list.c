/*
 * list.c
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */


#include <stdlib.h>
#include "../h/list.h"

int comp_p(point p1, point p2) {
	if ((p1.x==p2.x)&&(p1.y==p2.y)) return 1;
	return 0;
}

list insert_l(list *l, point p, intersec i) {
    list new_elem_ptr = (list) malloc(sizeof(list_elem));
    new_elem_ptr->p = p;
    new_elem_ptr->next = NULL;
    while (*l!=NULL) {
        l = &((*l)->next);
    }
    *l = new_elem_ptr;
    return new_elem_ptr;
}

int exist_list(list* l, point p2) {
	while ((*l)->next!=NULL) {
		if (comp_p((*l)->p, p2)) return 1;
		l = &(*l)->next;
	}
	return 0;
}
