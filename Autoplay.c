#include<stdio.h>
#include<ml_lib.c>

typedef struct node rec_tree;
typedef struct row t_row;

struct node { //valore,mossa
	int alfa;
	point destinazione;
}

struct row{ //pedina,(valore,mossa)
	pedina *ped;
	rec_tree value;
}

struct mossa{
	pedina *ped;
	point destinazione;	
}

t_row database_mosse[2][14]; //situazione



rec_tree minimax(rec_tree node, int depth){
	//Vedi https://it.wikipedia.org/wiki/Minimax
}

pedina select_pedina(id_p player, t_row db[2][14]){
	/*1) Selezione riga
	* 2) Selezione max alfa;
	* 3) Ritorno pedina,mossa
	*/
}

