#include<stdio.h>
#include "ml_lib.h"

#define NUMERO_PEDINE 7

typedef struct s_node t_node;

/*alfa -> [-1,1]*/

struct s_node { /*coppia valore,mossa*/
	int alfa; /*indice */
	point start;
	point end;
	pedina *data;
};

void catchInput_Autoplay(int *cord, t_node result);

int can_be_eaten(pedina **board, point p);

void check_son(pedina **board, t_node *res, int x, int y, t_node *node, int *alfa, int depth, int turn);

int evaluate(pedina **board, t_node node);

t_node minimax(pedina **board, t_node node, int depth, int turn);

t_node select_pedina(t_node db[NUMERO_PEDINE]);
