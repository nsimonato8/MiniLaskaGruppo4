#include<stdio.h>
#include<limits.h>
#include "Autoplay.h"

#define NUMERO_PEDINE 7
t_node database_mosse[NUMERO_PEDINE]; /*situazione*/


/*
* Legge i valori da db_mosse e li passa a cord
* Invoca select_pedina e traduce from->to
*/
void catchInput_Autoplay(int *cord, t_node result){
	cord[1] = result.start.x + 'a' + 1;
	cord[0] = result.start.y + '0' + 1;
	cord[3] = result.end.x + 'a' + 1;
	cord[2] = result.end.y + '0' + 1;
	
}

int can_be_eaten(pedina **board, point p){
	int success;
	pedina *avversario;
	
	success = 0;	
	
	avversario = get_board_value_immediate(board,p.x-1,p.y-1);	
	if(is_inside(p.x+1,p.y+1) && !get_board_value_immediate(board,p.x+1,p.y+1) && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (p.x+2,p.y+2)*/
		success = 1;
	}
	
	avversario = get_board_value_immediate(board,p.x-1,p.y+1);	
	if(is_inside(p.x+1,p.y-1) && !get_board_value_immediate(board,p.x+1,p.y-1) && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (p.x+2,p.y+2)*/
		success = 1;
	}
	
	avversario = get_board_value_immediate(board,p.x+1,p.y+1);	
	if(is_inside(p.x-1,p.y-1) && !get_board_value_immediate(board,p.x-1,p.y-1) && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (p.x+2,p.y+2)*/
		success = 1;
	}
	
	avversario = get_board_value_immediate(board,p.x+1,p.y-1);	
	if(is_inside(p.x-1,p.y+1) && !get_board_value_immediate(board,p.x-1,p.y+1) && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (p.x+2,p.y+2)*/
		success = 1;
	}
	
	return success;
}

void check_son(pedina **board, t_node *res, int x, int y, t_node *node, int *alfa, int depth, int turn){
	(*res).end.x = (*node).end.x + x;
	(*res).end.y = (*node).end.y + y;
	if (can_eat(board,(*res).end) || can_move(board,(*res).end)){
		*res = minimax(board,(*res),depth-1,turn+1);
		if(*alfa < res->alfa)
			*alfa = res->alfa;
	}	
}

int evaluate(pedina **board, t_node node){
	if(can_eat(board,node.end))
		return 1;
	else if(can_be_eaten(board,node.end))
		return -1;
	else
		return 0;
	
}


/*
function minimax(nodo, profondità)

    SE nodo è un nodo terminale OPPURE profondità = 0
        return il valore euristico del nodo 
		
    SE l'avversario deve giocare
        α := +∞
        PER OGNI figlio di nodo
            α := min(α, minimax(figlio, profondità-1))
			
			
    ALTRIMENTI dobbiamo giocare noi
        α := -∞
        PER OGNI figlio di nodo
            α := max(α, minimax(figlio, profondità-1))
			
			
    return α
*/
t_node minimax(pedina **board, t_node node, int depth, int turn){
	
	t_node res;
	if(!depth){
		res.alfa = evaluate(board, node);
	}else{
		int alfa;
		if(turn%2){ /*Gioca AI*/
			alfa = INT_MIN;
			
			/*+1,+1*/  /*void check_son(pedina **board, t_node *res, int x, int y, t_node *node, int *alfa, int depth, int turn)*/
			check_son(board, &res, +1, +1, &node, &alfa, depth, turn);
			
			/*-1,+1*/
			check_son(board, &res, -1, +1, &node, &alfa, depth, turn);
			
			if(get_grade(node.data) == Officer){
				/*+1,-1*/
				check_son(board, &res, +1, -1, &node, &alfa, depth, turn);
				/*-1,-1*/
				check_son(board, &res, -1, -1, &node, &alfa, depth, turn);
			}
			
		}else{ /*Gioca UMANO*/
			alfa = INT_MAX;
			/*-1,+1*/
			check_son(board, &res, +1, +1, &node, &alfa, depth, turn);
			
			/*-1,+1*/
			check_son(board, &res, -1, +1, &node, &alfa, depth, turn);
			
			if(get_grade(node.data) == Officer){
				/*+1,-1*/
				check_son(board, &res, +1, -1, &node, &alfa, depth, turn);
				
				/*-1,-1*/
				check_son(board, &res, -1, -1, &node, &alfa, depth, turn);
			}
			
		}
		
	}
	return res;
}

/*
* 1) Selezione riga
* 2) Selezione max alfa;
* 3) Ritorno pedina,mossa (t_node)
*/
t_node select_pedina(t_node db[NUMERO_PEDINE]){	
	int i, max = INT_MIN;
	t_node res;
	for(i = 0; i < NUMERO_PEDINE; i++){
		if(db[i].alfa > max){
			res = db[i];
			max = db[i].alfa;
		}			
	}
	return res;
}

