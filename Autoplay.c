#include<stdio.h>
#include<ml_lib.c>

typedef struct s_node t_node;
typedef struct s_row t_row;
typedef struct s_mossa mossa;

struct s_node { //coppia valore,mossa
	int alfa;
	point destinazione;
}

struct s_row{ //coppia pedina,(valore,mossa)
	pedina *ped;
	t_node value;
}

struct s_mossa{
	pedina *ped;
	point destinazione;	
}

t_row database_mosse[2][14]; //situazione



t_node minimax(t_node node, int depth){
	//Vedi https://it.wikipedia.org/wiki/Minimax
}

pedina select_pedina(id_p player, t_row db[2][14]){
	/*1) Selezione riga
	* 2) Selezione max alfa;
	* 3) Ritorno pedina,mossa
	*/
}

