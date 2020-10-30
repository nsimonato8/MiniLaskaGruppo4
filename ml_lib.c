#include<stdio.h>
#include "ml_lib.h"


/*Restituisce un puntatore alla matrice contenente le pedine*/
pedina **createPedine(){
    int i,j;
    pedina **p= (pedina**) malloc(11*2*sizeof(pedina));

    for(i =0; i < 2; i++){
        for(j = 0; j < 11; j++){
            p[i][j] = (pedina*) malloc(sizeof(pedina));
            p[i][j]->id_pedina = j;
            p[i][j]->id_giocatore = i;
            p[i][j]->grado = 0;
        }
    }

    return p;
}

/*Distrugge la matrice contenente le pedine*/
void destroyPedine(pedina **p){
    int i,j;

    for(i = 0; i < 2; i++){
        for(j = 0; j < 11; j++)
            free(p[i][j]);
    }
    free(p);
}

/* Funzione che crea la matrice della scacchiera */
pedina **createMatrix(const pedina r, const pedina c){

	pedina **m = (pedina**) malloc(r*c*sizeof(pedina));
	
	return m;
}

void destroyMatrix(pedina **board){
    free(board);
}

/*
* Numero 1 usato per identificare il player 1,
* Numero 2 usato per identificare il player 2,
* Numero 0 usato per identificare le celle su cui non sono ammessi posizionamenti delle pedine,
* Simbolo # usato per identificare la linea di gioco tra i due player.
*
* Funzione che inizializza la matrice con le pedine dei player
*/
void setValuesMatrix(pedina **board, pedina **players){
	
	/*int r1,c1;*/
	int i,j, p = 0;
	
	for(i = 0; i < ROW; i++){
	    for(j = 0; j < COL; j++){
	        if((i % 2 && !(j % 2)) || (!(i % 2) && (j % 2)))
	            board[i][j] = 0;
	        else if(i < 3){
	            board[i][j] = players[0][p];
	            p++;
	        }
	        else if(i == 3)
	            p = 0;
	        else{
                board[i][j] = players[1][p];
                p++;
	        }
	    }
	} /*Dovrebbe funzionare, in caso lascio la vecchio versione a commento qui sotto*/
	
	/*for(r1=0;r1<r;r1++){
		for(c1=0;c1<c;c1++){
			if(r1<3){
				if(r1%2==0){
					if(c1%2==0)
						m[r1][c1]=1;
					else 
						m[r1][c1]=0;
				} else {
					if(c1%2==0)
						m[r1][c1]=0;
					else 
						m[r1][c1]=1;
				}
			} else {
				if(r1==3){
					if(c1%2==0)
						m[r1][c1]=0;
					else 
						m[r1][c1]=5;
				} else {
					if(r1%2==0){
						if(c1%2==0)
							m[r1][c1]=2;
						else 
							m[r1][c1]=0;
					} else {
						if(c1%2==0)
							m[r1][c1]=0;
						else 
							m[r1][c1]=2;
					}
				}
			}
			
			
		}
	}*/
}

void printPedina(pedina *p){
    if(p->id_player && p->grado)
        printf("N");
    else if(p->id_player && !(p->grado))
        printf("n");
    else if(!(p->id_player) && p->grado)
        printf("B");
    else
        printf("b");
}

/* Funzione che stampa la scacchiera in base al posizionamento delle pedine. */
void printMatrix(pedina **m){

    int i,j;

    for(i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if ((i % 2 && !(j % 2)) || (!(i % 2) && (j % 2))) /*Caselle oscurate*/
                printf("# ");
            else if(!m[i][j]){
                printf("  ");                
            }
            else{
                printPedina(m[i][j]);
                printPedina(m[i][j]->middle);
                printPedina(m[i][j]->down);
            }
        }
        printf("\n");
    }
    
/*Lascio la vecchia versione qui sotto a commento, non si sa mai*/
/*	int r1,c1;
	
	for(r1=0;r1<r;r1++){
		for(c1=0;c1<c;c1++){
			if(m[r1][c1]==0){
				printf(" ");
			} else if(m[r1][c1]==1){
					printf("N ");
				} else if(m[r1][c1]==2) {
						printf("B ");
					} else if(m[r1][c1]==5){
						printf("# ");
					}
			
		}
		printf("\n");
	}*/
}
