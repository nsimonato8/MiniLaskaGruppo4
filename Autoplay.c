#include<stdio.h>
#include<ml_lib.c>

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
t_node minimax(/*pedina **board, */t_node node, int depth, int turn){
	
	t_node res;
	if(!depth){
		res = valutazione_euristica(node);
	}else{
		int alfa = INT_MIN;
		if(turn%2){
			
			/*res = node + (+1,+1)
			/*if (can_eat || can_move){
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
			
		}else{
			/**/
			
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

