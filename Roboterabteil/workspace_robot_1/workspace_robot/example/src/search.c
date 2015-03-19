/*
 * search.c
 *
 *  Created on: 18.03.2015
 *      Author: mk
 */

#include <stdlib.h>
#include <stdio.h>


#include "../h/search.h"
#include "../h/functions.h"


point start_point;
list visit_points, n_visit_points;
card c;

void set_inter(intersec *i,int n, int e, int s, int w) {
    i->North = n;
    i->East = e;
    i->South = s;
    i->West = w;
}

void print_inter(intersec *i) {
	printf("(%i,%i,%i,%i)", i->North, i->South, i->West, i->East);
}

void dechiff_intersec(intersec *i, int x) {
    switch (x) {
    case 16:
    	set_inter(i, 1,0,0,0); break;
    case 32:
    	set_inter(i, 0,0,1,0); break;
    case 48:
    	set_inter(i, 1,0,1,0);break;
    case 64:
    	set_inter(i, 0,0,0,1);break;
    case 80:
    	set_inter(i, 1,0,0,1);break;
    case 96:
    	set_inter(i, 0,0,1,1);break;
    case 112:
    	set_inter(i, 1,0,1,1);break;
    case 128:
    	set_inter(i, 0,1,0,0);break;
    case 144:
    	set_inter(i, 1,1,0,0);break;
    case 160:
    	set_inter(i, 0,1,1,0);break;
    case 176:
    	set_inter(i, 1,1,1,0);break;
    case 192:
    	set_inter(i, 0,1,0,1);break;
    case 208:
    	set_inter(i, 1,1,0,1);break;
    case 224:
    	set_inter(i, 0,1,1,1);break;
    case 240:
    	set_inter(i, 1,1,1,1);break;
    case 0:
    	set_inter(i, 0,0,0,0);break;
    case 1:
    	set_inter(i, 0,0,0,0);break;
    default:
    	printf("ERROR in dechiff_inter");
    }

}

int allowed_way(int opt, int code) {
	int erg = 0;
	intersec i;
	dechiff_intersec(&i, code);
	switch (opt) {
	case MYSOUTH:
		//if((code==NESW)||(code==NSW)||(code==ESW)||(code==NES)||(code==So)||(code==ES)||(code==SW)||(code==NS)) erg = 1;
		return i.South;
		break;
	case MYNORTH:
		//if ((code==NESW)||(code==NES)||(code==NSW)||(code==NEW)||(code==NE)||(code==NS)||(code==NW)||(code==No)) erg = 1;
		return i.North;
		break;
	case MYWEST:
		//if ((code==NESW)||(code==ESW)||(code==NSW)||(code==NEW)||(code==SW)||(code==EW)||(code==NW)||(code==We)) erg = 1;
		return i.West;
		break;
	case MYEAST:
		//if ((code==NESW)||(code==ESW)||(code==NEW)||(code==NES)||(code==NE)||(code==ES)||(code==EW)||(code==Ea)) erg = 1;
		return i.East;
		break;
	default:
		printf("ERROR in allowed_way");
	}
	return erg;
}

void select_direction(robot *r, intersec i) {
	print_inter(&i);
	switch (r->sel_dir) {
	case MYNORTH:
		if (i.East) r->sel_dir = MYEAST;
		if (i.West) r->sel_dir = MYWEST;
		if (i.North) r->sel_dir = MYNORTH;
		if ((!i.East)&&(!i.West)&&(!i.North)) r->sel_dir = MYBREAK;
		break;
	case MYWEST:
		if (i.West) r->sel_dir = MYWEST;
		if (i.South) r->sel_dir = MYSOUTH;
		if (i.North) r->sel_dir = MYNORTH;
		if ((!i.East)&&(!i.South)&&(!i.North)) r->sel_dir = MYBREAK;
		break;
	case MYSOUTH:
		if (i.East) r->sel_dir = MYEAST;
		if (i.West) r->sel_dir = MYWEST;
		if (i.South) r->sel_dir = MYSOUTH;
		if ((!i.East)&&(!i.West)&&(!i.South)) r->sel_dir = MYBREAK;
		break;
	case MYEAST:
		if (i.East) r->sel_dir = MYEAST;
		if (i.South) r->sel_dir = MYSOUTH;
		if (i.North) r->sel_dir = MYNORTH;
		if ((!i.East)&&(!i.South)&&(!i.North)) r->sel_dir = MYBREAK;
		break;
	default:
		printf("ERROR in select_direction");
	}
}

point new_point(point p, int orient) {
    switch (orient) {
    case MYNORTH:
        p.y++; break;
    case MYSOUTH:
        p.y--; break;
    case MYWEST:
        p.x--; break;
    case MYEAST:
        p.x++; break;
    case MYBREAK:
    	break;
    default:
        printf("ERROR in clac_point");
    }
    return p;
}

point get_next_point(point p, card *c,int *dir) {
	point new_p;
	if ((get_state(c, p.x, p.y-1)==1)&&allowed_way(MYSOUTH, c->map[koord_to_i(p.x, p.y)])){
		new_p.x = p.x;
		new_p.y = p.y-1;
		*dir = MYSOUTH;
		return new_p;
	}
	if ((get_state(c, p.x, p.y+1)==1)&&allowed_way(MYNORTH, c->map[koord_to_i(p.x, p.y)])){
			new_p.x = p.x;
			new_p.y = p.y+1;
			*dir = MYNORTH;
			return new_p;
		}
	if ((get_state(c, p.x-1, p.y)==1)&&allowed_way(MYWEST, c->map[koord_to_i(p.x, p.y)])){
			new_p.x = p.x-1;
			new_p.y = p.y;
			*dir = MYWEST;
			return new_p;
		}
	if ((get_state(c, p.x+1, p.y)==1)&&allowed_way(MYEAST, c->map[koord_to_i(p.x, p.y)])){
			new_p.x = p.x+1;
			new_p.y = p.y;
			*dir = MYEAST;
			return new_p;
		}
	return p;
}

int get_orient_of_next_point(point p, card *c) {
	if ((get_state(c, p.x, p.y-1)==1)&&allowed_way(MYSOUTH, c->map[koord_to_i(p.x, p.y)])){
		return MYSOUTH;
	}
	if ((get_state(c, p.x, p.y+1)==1)&&allowed_way(MYNORTH, c->map[koord_to_i(p.x, p.y)])){
			return MYNORTH;
		}
	if ((get_state(c, p.x-1, p.y)==1)&&allowed_way(MYWEST, c->map[koord_to_i(p.x, p.y)])){
			return MYWEST;
		}
	if ((get_state(c, p.x+1, p.y)==1)&&allowed_way(MYEAST, c->map[koord_to_i(p.x, p.y)])){
			return MYEAST;
		}
	return MYBREAK;
}


void get_nearest_unknown(point p, card *k, int or, point *output) {
	point new_p = p;
	int i;
	if (comp_p(get_next_point(p,k,i),p)) {
		intersec opt;
		dechiff_intersec(&opt, k->map[koord_to_i(p.x, p.y)]);
		if ((opt.East==1)&&(or!=MYWEST)) {
			new_p.x++;
			get_nearest_unknown(new_p, k, MYEAST, output);
		}
		if ((opt.West==1)&&(or!=MYEAST)) {
					new_p.x--;
					get_nearest_unknown(new_p, k, MYWEST, output);
				}
		if ((opt.North==1)&&(or!=MYSOUTH)) {
					new_p.y++;
					get_nearest_unknown(new_p, k, MYNORTH, output);
				}
		if ((opt.South)&&(or!=MYNORTH)) {
					new_p.y--;
					get_nearest_unknown(new_p, k, MYSOUTH, output);
				}
	}
	else {
		output->x = new_p.x;
		output->y = new_p.y;
	}
}

void move_robot(robot *r) {
	point cur_p = r->cur_pos;
	int dir;
	//point new_p = new_point(cur_p, r->sel_dir);
	point new_p = get_next_point(r->cur_pos, &c, &dir);
	if (comp_p(cur_p, new_p)) {
		r->sel_dir = MYBREAK;
		return;
	}
	Robot_Move(dir);
	//printf("Move to %i \n", get_orient_of_next_point(cur_p, &c));
	r->cur_pos = new_p;
}

point calc_point_form_orient(point p, int orient) {
	switch (orient) {
	case MYNORTH:
		p.y++;
		break;
	case MYSOUTH:
		p.y--;
		break;
	case MYWEST:
		p.x++;
		break;
	case MYEAST:
		p.x--;
		break;
	default:
		break;
	}
	return p;
}

/*
void run_robot(robot *r) {

	intersec cur_inter;
	point cur_p = r->cur_pos;
	dechiff_intersec(&cur_inter);
	insert_l(&visit_points, cur_p, cur_inter);
	select_direction(r, cur_inter);
	move_robot(r);
	if (r->no_cross) return;
	if (!exist_list(&visit_points, r->cur_pos))
		run_robot(r);
	print_card(&c);
}
*/

void run_by_card(robot *r) {
	point return_p;
	int state = Robot_GetIntersections();
	intersec in;
	dechiff_intersec(&in, state);
	set_state(&c, r->cur_pos.x, r->cur_pos.y, state);
	set_local_envoriment(&c, r->cur_pos.x, r->cur_pos.y);
	//select_direction(r, in);
	move_robot(r);
	/*if (r->sel_dir==MYBREAK) {
		print_card(&c);
		r->sel_dir = 2;
		get_nearest_unknown(r->cur_pos, &c, MYBREAK, &return_p);
		r->cur_pos= return_p;
		Robot_Move(get_orient_of_next_point(return_p, &c));
	}
	run_by_card(r);
*/
}



void runbot(robot *r) {
	point return_p;
	while (1) {

		run_by_card(r);
		if (r->sel_dir==MYBREAK) {
				//print_card(&c);
		/*		r->sel_dir = 2;
				get_nearest_unknown(r->cur_pos, &c, MYBREAK, &return_p);
				r->cur_pos= return_p;
				//Robot_Move(get_orient_of_next_point(return_p, &c));
				return;  */
		while(1){
			beep();
		}
			}
	}


}
