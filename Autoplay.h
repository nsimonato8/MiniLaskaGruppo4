
#ifndef Autoplay_h
#define Autoplay_h

#include<stdio.h>
#include<limits.h>
#include"ml_lib.h"

#define NUMERO_PEDINE 7
#define MOSSE 8
#define DEPTH_MAX 7

typedef struct s_node t_node;
typedef struct s_node_list *t_node_list;
typedef enum mod {MIN, MAX} mode;

/*alfa -> [-1,1]*/

struct s_node { /*coppia valore,mossa*/
    point start;
    point end;
    int value;
};

struct s_node_list {
    t_node data;
    t_node_list next;
};

int catchInput_Autoplay(pedina **board, int turn);

int can_be_eaten(pedina **board, point p);

int evaluate(pedina **board);

void print_t_node(t_node t);

void print_list(t_node_list i);

int prepend(t_node_list *l, t_node val);

void destroy_list(t_node_list l);

int append(t_node_list *l, t_node val);

t_node get_from_list(t_node_list l, mode x);

point* get_dir(void);

t_node_list get_moves(pedina **board, int turn);

int minimax(pedina **board, t_node move, int depth, int turn);

void print_list(t_node_list i);

#endif /* Autoplay_h */
