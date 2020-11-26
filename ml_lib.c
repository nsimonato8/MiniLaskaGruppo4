#include<stdio.h>
#include<stdlib.h>

#include "ml_lib.h"

/*---------------------------------SEZIONE FUNZIONI AUSILIARIE---------------------------------*/

/* Imposta l'id_player della pedina indicata dal puntatore*/
void set_id_player(pedina *p, id_p value){
    p->id_player = value;
}

/* Ritorna il p->id_player della pedina specificata */
id_p get_id_player(pedina *p){
    return p->id_player;
}

/* Imposta il valore value nella posizione indicata nella scacchiera*/
void set_board_value(pedina ***p, int x, int y, pedina *value){
    p[x][y] = value;
}

/* Ritorna il valore nella posizione indicata nella scacchiera*/
pedina* get_board_value(pedina ***p, int x, int y){
    return p[x][y];
}

/* Ritorna il valore della pedina middle nella posizione indicata nella scacchiera*/
pedina* get_board_value_middle(pedina ***p, int x, int y){
    return p[x][y]->middle;
}

/* Ritorna il valore della pedina down nella posizione indicata nella scacchiera*/
pedina* get_board_value_down(pedina ***p, int x, int y){
    return p[x][y]->down;
}

/* Imposta il grado di una pedina*/
void set_grade(pedina *p,gr value){
    p->grado = value;
}

/* Ritorna il grado di una pedina*/
gr get_grade(pedina *p){
    return p->grado;
}

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
                set_id_player(p[i][j], i);
                set_grade(p[i][j],Soldier);
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
            free(get_board_value(p,i,j));
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
                set_board_value(board,i,j,0);
                if(i==3)
                    p = 0;
	        }
	        else if(i < 3){
                set_board_value(board,i,j,get_board_value(players,0,p));
	            p++;
	        }
	        else{
                set_board_value(board,i,j,get_board_value(players,1,p));
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

/* Stampa un carattere ASCII identificativo del contenuto della casella p*/
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
                printPedina(get_board_value(p,i,j));
                printPedina(get_board_value_middle(p,i,j));
                printPedina(get_board_value_down(p,i,j));
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

void printStatus(unsigned turn){
    printf("\t\t\tTurn number: %u\n\t\t\tMove: %u",turn,(id_p) (turn%2));
}

void printRules(){
    printf("                        MiniLaska\n\n\n");
    printf("    MiniLaska è una variante del gioco originale Lasca le cui uniche differenze sono due:\n");
    printf("    1)si può avere una colonna di massimo tre pedine,\n");
    printf("    se si supera tale numero si perde l'ultima pedina a partire dal basso\n");
    printf("    2)si può conquistare/mangiare una pedina per volta.\n");
    printf("    E' composta da una scacchiera 7x7, delle 49 caselle solo 25 sono giocabili\n");
    printf("    essendo che ci si può spostare solo in diagonale.\n ");
    printf("    I due giocatori partono con 11 pedine ciascuno.\n\n\n");

    printf("    Struttura: soldato,ufficiale,colonna,comandante:\n\n");
    printf("    Tutti partono come soldati semplici. Una volta raggiunta l'ultima riga\n");
    printf("    del lato opposto si diventa ufficiali (la pedina viene capovolta),\n");
    printf("    ora ci si può muovere sia in avanti che indietro,sempre diagonalmente.\n");
    printf("    Quando si catturano le pedine dell'avversario si forma una\n");
    printf("    colonna dove in cima abbiamo il giocatore che ha mangiato la/e pedina/e,\n");
    printf("    la colonna può essere fomata da due/tre pedine, quella più in alto è detta comandante,\n");
    printf("    se il comandante è un colonello permette alla colonna di spostarsi anche all'indietro.\n\n\n");

    printf("    Come si vince?\n\n");
    printf("    quando uno dei due giocatori non ha piu mosse disponibili: \n");
    printf("    o tutte le sue pedine vengono catturate oppure viene bloccato,\n");
    printf("    quindi qualsiasi mossa faccia finirebbe col perdere.");
}

void victory(id_p winner){
    if(winner == UserOneOne)
        printf("\tComplimenti umano, grande vittoria!!!");
    else
        printf("\tComplimenti UserTwo, grande vittoria!!!");
}

void inputError(){
    printf("\tNon puoi spostarti in quella casella!");
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
int move(pedina ***p, int from_x, int from_y, int to_x, int to_y, id_p first, int turn){
    int success = 1, d = distance(from_x,from_y,to_x,to_y), grade_control = gradeCheck(p,from_x,from_y,to_y), existM = existMandatory(p,from_x,from_y,to_x,to_y), legal_player = first == (turn %2);
    if(!legal_player || get_board_value(p,to_x,to_y) || d == -1 || !grade_control || existM)
        success = 0;
    else{
        if(d == 1){
            set_board_value(p,to_x,to_y,get_board_value(p,from_x,from_y));
            set_board_value(p,from_x,from_y,0);
        }
        else if(d == 2){
            int middle_x = (from_x + to_x)/2, middle_y = (from_y+to_y)/2;
            if(get_board_value(p,middle_x,middle_y)){ /*verifica esistenza pedina in mezzo*/
                if(get_id_player(p[middle_x][middle_y]) == get_id_player(p[from_x][from_y]))
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

    int middle_x = (from_x+to_x)/2, middle_y = (to_y+from_y)/2;
    pedina *prisoner = p[middle_x][middle_y];
    pedina *soldier =p[from_x][from_y];

    if(prisoner->middle || prisoner->down){ /*In questo ramo la pedina catturata ha pedine sottostanti*/
        if(get_id_player(prisoner->middle) == get_id_player(soldier) && get_id_player(prisoner->down) == get_id_player(soldier)) {/*Se entrambe le pedine catturate dal prigioniero sono alleate*/
            prisoner->middle->middle = prisoner->down;
            p[middle_x][middle_y] = prisoner->middle;
        }
        else if(get_id_player(prisoner->middle) == get_id_player(soldier) && !(prisoner->down)){/*Se la pedina prigioniera è ha solo un prigioniero, alleato, l'altra è vuota*/
            set_board_value(p,middle_x,middle_y,prisoner->middle);
        }
        else if(get_id_player(prisoner->down) == get_id_player(soldier)){/*Se una delle pedine catturate dal prigioniero è alleata e l'altra è nemica*/
            prisoner->down->middle = prisoner->middle;
            set_board_value(p,middle_x,middle_y,prisoner->down);
        }
        else{/*La pedina catturata ha sotto una pedina, nemica*/
            if(!(soldier->down))
                soldier->down = prisoner->middle;

            set_board_value(p,middle_x,middle_y,0);
        }

        if(soldier->middle){
            if(!soldier->down)
                soldier->down = prisoner;
        }else
            soldier->middle = prisoner;
    }
    else{ /*In questo ramo la pedina catturata non ha pedine sottostanti*/
        set_board_value(p,middle_x,middle_y,0);

        if(soldier->middle && !(soldier->down)){  /*Sistema la pedina catturata nella pedina del catturante*/
            soldier->down = prisoner;
        }
        else {
            soldier->middle = prisoner;
        }
    }

    set_board_value(p,middle_x,middle_y,soldier);
}

/* Verifica il grado della pedina mossa:
 * restituisce 1 se la mossa è consentita, 0 se non è consentita
*/
int gradeCheck(pedina ***p, int from_x, int from_y, int to_y){
    int success = 1;

    if(!get_grade(p[from_x][from_y]) && (to_y - from_y) > 0)
        success = 0;

    return success;
}

/* Verifica se, nel caso di non cattura, esiste una cattur obbligatoria da fare
 * Restituisce 1 se esiste una mossa obbligatoria non tentata, altrimenti 0
 */
int existMandatory(pedina ***p, int from_x, int from_y, int to_x, int to_y){

    int success, dx = to_x - from_x, dy = to_y - from_y;

    if(distance(from_x,from_y,to_x,to_y) == 2){
        success = 0;
    }
    else{
        if(get_board_value(p,from_x-dx,from_y-dy) || get_board_value(p,from_x+dx,from_y-dy) || get_board_value(p,from_x-dx,from_y+dy)) { /*Verifico l'esitenza di pedine intorno alla posizione di partenza*/
            if(get_board_value(p,from_x-dx,from_y-dy)){
                if(get_id_player(p[from_x-dx][from_y-dy]) != get_id_player(p[from_x][from_y]) && !p[from_x-2*dx][from_y-2*dy]) /*Verifico che siano nemiche e che la casella successiva sia libera*/
                    success = 1;
            }
            else if(get_board_value(p,from_x+dx,from_y-dy)){
                if(get_id_player(p[from_x+dx][from_y-dy]) != get_id_player(p[from_x][from_y]) && !p[from_x+2*dx][from_y-2*dy])
                    success = 1;
            }
            else{
                if(get_id_player(p[from_x-dx][from_y+dy]) != get_id_player(p[from_x][from_y]) && !p[from_x-2*dx][from_y+2*dy])
                    success = 1;
            }
        }
        else
            success = 0;
    }

    return success;
}

/*---------------------------------SEZIONE FUNZIONI LOGICHE DI GIOCO---------------------------------*/

/* Verifica che il giocatore idPlayer abbia vinto
 * Restituisce 1 se idPlayer ha vinto, altrimenti 0
*/
int isWinner(pedina ***p, int idPlayer) {

    int i,j,c=0;


    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (!c) {
                if (get_id_player(p[i][j]) == idPlayer)
                    c++;
            } else
                return 0;
        }
    }

    return 1;
}

