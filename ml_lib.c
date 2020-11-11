#include<stdio.h>
#include "ml_lib.h"

/*---------------------------------SEZIONE FUNZIONI GESTIONE MEMORIA---------------------------------*/

/*Restituisce un puntatore alla matrice contenente le pedine*/
pedina ***createPedine(){
    int i,j;
    pedina ***p= (pedina***) malloc(11*2*sizeof(pedina));

    if(!p)
        return 0;
    else{
        for(i =0; i < 2; i++){
            for(j = 0; j < 11; j++){
                p[i][j] = (pedina*) malloc(sizeof(pedina));
                p[i][j]->id_pedina = j;
                p[i][j]->id_player = i;
                p[i][j]->grado = 0;
            }
        }
        return p;
    }
}

/*Distrugge la matrice contenente le pedine*/
void destroyPedine(pedina ***p){
    int i,j;

    for(i = 0; i < 2; i++){
        for(j = 0; j < 11; j++)
            p[i][j] = 0;
    }
    free(p);
}

/*
 * Funzione che crea la matrice della scacchiera
*/
pedina ***createMatrix(){

	pedina ***m = (pedina***) malloc(ROW*COL*sizeof(pedina));

	if(m)
	    return m;
	else
	    return 0;
}

/*
 * Funzione che distrugge la matrice della scacchiera
*/
void destroyMatrix(pedina ***board){
    free(board);
}


/*
 * Restituisce 1 se la cella non è accessibile (si possono usare solo le celle bianche della scacchiera), altirmenti 0
*/
int isForbiddenCell(int x, int y){
    if((x % 2 && !(y % 2)) || (!(x % 2) && (y % 2)))
        return 1;
    else
        return 0;
}

/*
* Funzione che inizializza la matrice con le pedine dei player
*/
void setValuesMatrix(pedina ***board, pedina ***players){

	int i,j, p = 0;
	
	for(i = 0; i < ROW; i++){
	    for(j = 0; j < COL; j++){
	        if(isForbiddenCell(i,j) || i == 3){
                board[i][j] = 0;
                if(i==3)
                    p = 0;
	        }
	        else if(i < 3){
	            board[i][j] = players[0][p];
	            p++;
	        }
	        else{
                board[i][j] = players[1][p];
                p++;
	        }
	    }
	}
	
	/*
	 * * Numero 1 usato per identificare il player 1,
	 * Numero 2 usato per identificare il player 2,
     * Numero 0 usato per identificare le celle su cui non sono ammessi posizionamenti delle pedine,
     * Simbolo # usato per identificare la linea di gioco tra i due player.
	 * int r1,c1;
	 * for(r1=0;r1<r;r1++){
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

/*---------------------------------SEZIONE FUNZIONI OUTPUT---------------------------------*/

void printPedina(pedina *p){
    if(!p)
        printf(" ");
    else if(p->id_player && p->grado)
        printf("N");
    else if(p->id_player && !(p->grado))
        printf("n");
    else if(!(p->id_player) && p->grado)
        printf("B");
    else
        printf("b");
}

/* Funzione che stampa la scacchiera in base al posizionamento delle pedine. */
void printMatrix(pedina ***m){

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

/*---------------------------------SEZIONE FUNZIONI MOVE---------------------------------*/

/*
 * Legge l'input dall'utente e traduce le coordinate in int, che vengono inseriti in un array apposito
*/
int catchInput(int *cord){
    char *a;
    size_t bufsize = 10;
    int success = 1;

    a=(char *)malloc(bufsize*sizeof(char));

    if(a==NULL){
        perror("Malloc error");
        exit(1);
    }

    /*acquisizione stringa dall'input*/
    getline(&a,&bufsize,stdin);

    /*conversione in coordinate*/
    cord[0]=((a[0]-96)-1);
    cord[1]=(int)((a[1]-'0')-1);

    cord[2]=((a[6]-96)-1);
    cord[3]=(int)((a[7]-'0')-1);
    free(a);
    if((cord[0] >= 0 && cord[0] <= 6) && (cord[1] >= 0 && cord[1] <= 6) && (cord[2] >= 0 && cord[2] <= 6) && (cord[3] >= 0 && cord[3] <= 6))
        success = 0;

    return success;
}

/*
 * Restituisce 1 se la mossa è stata fatta, 0 se non è stato possibile
 *
 * Le coordinate inserite sono corrette in fase di input (sono all'interno della scacchiera e non sono caselle proibite)
 * Verifica che la distanza ed il grado siano compatibili con la mossa
*/
int move(pedina ***p, int from_x, int from_y, int to_x, int to_y){
    int success = 1, d = distance(from_x,from_y,to_x,to_y), grade_control = gradeCheck(p,from_x,from_y,to_y);
    if(p[to_x][to_y] || d == -1 || !grade_control )
        success = 0;
    else{
        if(d == 1){
            p[to_x][to_y] = p[from_x][from_y];
            p[from_x][from_y] = 0;
        }
        else if(d == 2){
            int middle_x = (from_x + to_x)/2, middle_y = (from_y+to_y)/2;
            if(p[middle_x][middle_y]){ /*verifica esistenza pedina in mezzo*/
                if(p[middle_x][middle_y]->id_player == p[from_x][from_y]->id_player)
                    success = 0; /*se amica, annulla mossa*/
                else
                    capture(p,from_x,from_y,to_x,to_y); /*se nemica cattura*/
            }
            else
                success = 0;
        }
        else
            success = 0;
    }
    return success;
}

/*
 * Restituisce la distanza in modulo tra due punti nella matrice:
 * Se è maggiore di 2, uguale a 0, o la destinazione è in una casella non accessibile restituisce il codice errore -1
 *
 * Le coordinate inserite sono corrette (la destinazione non è una casella proibita)
*/
int distance(int from_x, int from_y, int to_x, int to_y){
    int result, dx = abs(to_x - from_x), dy = abs(to_y - from_y);

    if(dx == dy && dx && dx < 3)
        result = dx;
    else
        result = -1;

    return result;
}

/*
 * Questa funzione si occupa di catturare le pedine indicate.
 * Si assume la correttezza delle coordinate inserite, la legalità della mossa è verificata nella funzione move(...).
*/
void capture(pedina ***p, int from_x, int from_y, int to_x, int to_y){

    pedina *prisoner = p[(from_x+to_x)/2][(from_y+to_y)/2];
    pedina *soldier =p[from_x][from_y];

    if(prisoner->middle || prisoner-> down){ /*In questo ramo la pedina catturata ha pedine sottostanti*/
        if(prisoner->middle->id_player == soldier->id_player && prisoner->down->id_player == soldier->id_player) {/*Se entrambe le pedine catturate dal prigioniero sono alleate*/
            prisoner->middle->middle = prisoner->down;
            p[(from_x+to_x)/2][(from_y+to_y)/2] = prisoner->middle;
        }
        else if(prisoner->middle->id_player == soldier->id_player && !(prisoner->down)){/*Se la pedina prigioniera è ha solo un prigioniero, alleato, l'altra è vuota*/
            p[(from_x+to_x)/2][(from_y+to_y)/2] = prisoner->middle;
        }
        else if(prisoner->down->id_player == soldier->id_player){/*Se una delle pedine catturate dal prigioniero è alleata e l'altra è nemica*/
            prisoner->down->middle = prisoner->middle;
            p[(from_x+to_x)/2][(from_y+to_y)/2] = prisoner->down;
        }
        else{/*La pedina catturata ha sotto una pedina, nemica*/
            if(!(soldier->down))
                soldier->down = prisoner->middle;

            p[(from_x+to_x)/2][(from_y+to_y)/2] = 0;
        }

        if(soldier->middle){
            if(!soldier->down)  soldier->down = prisoner;
        }else
            soldier->middle = prisoner;
    }
    else{ /*In questo ramo la pedina catturata non ha pedine sottostanti*/
        p[(from_x + to_x) / 2][(from_y + to_y) / 2] = 0;

        if(soldier->middle && !(soldier->down)){  /*Sistema la pedina catturata nella pedina del catturante*/
            soldier->down = prisoner;
        }
        else {
            soldier->middle = prisoner;
        }
    }

    p[to_x][to_y] = soldier;
}

/* Verifica il grado della pedina mossa:
 * restituisce 1 se la mossa è consentita, 0 se non è consentita*/
int gradeCheck(pedina ***p, int from_x, int from_y, int to_y){
    int success = 1;

    if(p[from_x][from_y]->grado == 0 && (to_y - from_y) > 0)
        success = 0;

    return success;
}
