#include<stdio.h>
#include<ml_lib.h>

#define NUMERO_PEDINE 7

typedef struct s_node t_node;

/*alfa -> [-1,1]*/

struct s_node { //coppia valore,mossa
	int alfa; //indice 
	point start;
	point end;
	pedina *data;
}


t_node database_mosse[NUMERO_PEDINE]; //situazione


/*Legge i valori da db_mosse e li passa a cord
* Invoca select_pedina e traduce from->to
*/
int catchInput_Autoplay(int *cord); 

int can_be_eaten(pedina **board, t_node node);

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
		res = evaluate(board, node);
	}else{
		int alfa;
		if(turn%2){ /*Gioca AI*/
			alfa = INT_MIN;
			/*  res = node + (+1,+1)
				if (can_eat || can_move){
					res = minimax(res,depth-1,turn+1)
					if(alfa < res.alfa)
						alfa = res.alfa;
				}
			*/
			
			/*-1,+1*/
			if(get_grade(node.data) == Officer){
				/*+1,-1*/
				/*-1,-1*/
			}
			
		}else{ /*Gioca UMANO*/
			alfa = INT_MAX;
			/*	res = node + (+1,+1)
				if (can_eat || can_move){
					res = minimax(res,depth-1,turn+1)
					if(alfa > res.alfa)
						alfa = res.alfa;
				}
			*/
			
			/*-1,+1*/
			if(get_grade(node.data) == Officer){
				/*+1,-1*/
				/*-1,-1*/
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

