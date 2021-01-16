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
void set_board_value(pedina **board, unsigned x, unsigned y, pedina *value){
    board[y * COL + x] = value;
}

/* Ritorna il valore nella posizione indicata nella scacchiera*/
pedina* get_board_value(pedina **board, unsigned x, unsigned y){
    return board[y * COL + x];
}

/* Ritorna il valore della pedina middle nella posizione indicata nella scacchiera*/
pedina* get_board_value_middle(pedina **board, unsigned x, unsigned y){
    if(!board[y * COL + x])
        return 0;
    else
        return board[y * COL + x]->middle;
}

/* Ritorna il valore della pedina down nella posizione indicata nella scacchiera*/
pedina* get_board_value_down(pedina **board, unsigned x, unsigned y){
    if(!board[y * COL + x])
        return NULL;
    else
        return board[y * COL + x]->down;
}

/* Imposta il grado di una pedina*/
void set_grade(pedina *p,gr value){
    p->grado = value;
}

/* Ritorna il grado di una pedina*/
gr get_grade(pedina *p){
    return p->grado;
}

/*Ritorna 1 se x,y è dentro la scacchiera, 0 altrimenti*/
int is_inside(int x, int y){
	return (x >= 0) && (y <= 6) && (x >= 0) && (y <= 6);
}

/*Ritorna 1 la direzione della pedina è giusta*/
int right_path(dir direction, gr grade, id_p player){
	return grade || !(direction^player);
}

/*---------------------------------SEZIONE FUNZIONI GESTIONE MEMORIA---------------------------------*/

/*
 * Funzione che crea la matrice della scacchiera
*/
pedina **createMatrix(){

    pedina** board = (pedina **) malloc(7*7*sizeof(pedina *));

    if(!board){
        printf("createMatrix failed malloc");
        return 0;
    }
    else
        return board;
}

/*
 * Funzione che distrugge la matrice della scacchiera
 *
 * TODO: rivedere la free su ogni cella della scacchiera se non ancora fatta
 *
*/
void destroyMatrix(pedina **board){
    free(board);
}

/*
 * Restituisce 1 se la cella non è accessibile (si possono usare solo le celle bianche della scacchiera), altirmenti 0
*/
int isForbiddenCell(unsigned x, unsigned y){
    if((x % 2 && !(y % 2)) || (!(x % 2) && (y % 2)))
        return 1;
    else
        return 0;
}

/*
 * Riempie la scacchiera
 * Modifica giovanni: set_board_value nell'if se forbiddenCell e j==3, IL VALUE MESSO È 0, ma la
 * funzione vuole il tipo pedina;
*/

void fillBoard(pedina** board){

    unsigned i,j;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            if(isForbiddenCell(j,i) || i == 3){
                set_board_value(board,j,i,0);
            }
            else{
                pedina *a = NULL;
                a = (pedina*) malloc(sizeof(pedina));
                set_grade(a,Soldier);
                a->down=NULL;
                a->middle=NULL;

                if(i < 3)
                    set_id_player(a, UserTwo);
                else{
                    set_id_player(a, UserOne);
                }
                set_board_value(board,j,i,a);
            }
        }
    }
}

/*---------------------------------SEZIONE FUNZIONI INPUT---------------------------------*/

/*
 * FUNZIONE CHE PRENDE IN INPUT CORDINATE PER LO SPOSTAMENTO DELLA PEDINA
 * controllo aggiuntivo per non inserire coordinate di start su cella a null.
 * per la destinazione non posso mettere questo controllod
*/
int catchInput(int *cord, pedina **board){
    char *v = (char *)malloc(sizeof(char)*4);

    do {
        printf("\n\nInserisci le coordinate della pedina da muovere: \n\n");

        printf("Coordinata Alfabetica: \n");

        do {
            if (scanf(" %c", &v[0]) != 1)
                perror("Errore acquisizione coordinata");

        } while (!(v[0] >= 'a' && v[0] <= 'g'));

        cord[0] = ((v[0] - 96) - 1);

        printf("Coordinata Numerica: \n");

        do {
            if (scanf(" %c", &v[1]) != 1)
                perror("Errore acquisizione coordinata");

        } while (!(v[1] >= '1' && v[1] <= '7'));

        cord[1] = ((v[1] - '0') - 1);

        if(get_board_value(board, cord[1], cord[0]) == 0)
            printf("\nCella non selezionabile, reinserisci le coordinate\n");

    }while(get_board_value(board, cord[1], cord[0]) == 0);

    printf("\nInserisci le coordinate di destinazione: \n\n");

    printf("Coordinata Alfabetica: \n");

    do{
        if(scanf(" %c",&v[2])!=1)
            perror("Errore acquisizione coordinata");

    }while(!(v[2]>='a' && v[2]<='g'));

    cord[2]=((v[2]-96)-1);

    printf("Coordinata Numerica: \n");

    do{
        if(scanf(" %c",&v[3])!=1)
            perror("Errore acquisizione coordinata");

    }while(!(v[3]>='1' && v[3]<='7'));

    cord[3]=((v[3]-'0')-1);

    return 1;
}

/*---------------------------------SEZIONE FUNZIONI OUTPUT---------------------------------*/

/* Stampa un carattere ASCII identificativo del contenuto della casella p
 *
 * PROVO A TOGLIERE IL CONTROLLO DEL NULL
 *
 * */
void printPedina(pedina *p){

    if(!p){
        printf(" ");
    }
    else if(get_id_player(p) && get_grade(p))
        printf("N");
    else if(get_id_player(p) && !get_grade(p))
        printf("n");
    else if(!get_id_player(p) && get_grade(p))
        printf("B");
    else
        printf("b");
}

/* Funzione che stampa la scacchiera in base al posizionamento delle pedine. */
void printMatrix(pedina** board){

    unsigned i,j;

    for(i=0; i<ROW; i++){

        printf("%c > ",('A'+ i));

        for(j=0;j<COL;j++){

            if ((i % 2 && !(j % 2)) || (!(i % 2) && (j % 2)))
                printf("###");
            else if(!get_board_value(board,j,i)){
                printf("   ");
            }
            else{
                printPedina(get_board_value(board,j,i));
                printPedina(get_board_value_middle(board,j,i));
                printPedina(get_board_value_down(board,j,i));
            }
            printf("|");
        }
        printf("\n");
    }

    printf("    ");

    for(i=0;i<COL;i++)
        printf("^   ");

    printf("\n");

    printf("    ");

    for(i=0;i<COL;i++){
        printf("%d   ", (i+1));
    }

    printf("\n");
}

void printStatus(unsigned turn){
    printf("\n\nTurn number: %u\nMove player: %s\n\n",(turn+1),(turn%2)?"User 2":"User 1");
}

void printRules(){
    printf("                          Benvenuto in MiniLaska\n\n");
    printf("MiniLaska è una variante del gioco originale Lasca le cui uniche differenze sono due:\n");
    printf("1)si può avere una colonna di massimo tre pedine,\n");
    printf("se si supera tale numero si perde l'ultima pedina a partire dal basso\n");
    printf("2)si può conquistare/mangiare una pedina per volta.\n");
    printf("E' composta da una scacchiera 7x7, delle 49 caselle solo 25 sono giocabili\n");
    printf("essendo che ci si può spostare solo in diagonale.\n");
    printf("I due giocatori partono con 11 pedine ciascuno.\n\n\n\n");

    printf("Struttura: soldato,ufficiale,colonna,comandante:\n\n");
    printf("Tutti partono come soldati semplici. Una volta raggiunta l'ultima riga\n");
    printf("del lato opposto si diventa ufficiali (la pedina viene capovolta),\n");
    printf("ora ci si può muovere sia in avanti che indietro,sempre diagonalmente.\n");
    printf("Quando si catturano le pedine dell'avversario si forma una\n");
    printf("colonna dove in cima abbiamo il giocatore che ha mangiato la/e pedina/e,\n");
    printf("la colonna può essere fomata da due/tre pedine, quella più in alto è detta comandante,\n");
    printf("se il comandante è un colonello permette alla colonna di spostarsi anche all'indietro.\n\n\n\n");

    printf("Come si vince?\n\n");
    printf("quando uno dei due giocatori non ha piu mosse disponibili: \n");
    printf("o tutte le sue pedine vengono catturate oppure viene bloccato,\n");
    printf("quindi qualsiasi mossa faccia finirebbe col perdere.\n\n\n\n");
}

void victory(id_p winner){
    if(winner == UserOne)
        printf("\tComplimenti giocatore, grande vittoria!!!");
    else
        printf("\tComplimenti UserTwo, grande vittoria!!!");
}

void inputError(){
    printf("\n\n|----- Non puoi spostarti in quella casella -----|\n");
}

/*---------------------------------SEZIONE FUNZIONI LOGICHE DI GIOCO---------------------------------*/

/* Verifica che il giocatore idPlayer abbia vinto
 * Restituisce 1 se idPlayer ha vinto, altrimenti 0
 * TODO: DA RIVEDERE QUANDO TI BLOCCANO
*/
int isWinner(pedina **board, id_p idPlayer) {

    int i,j,c;
	pedina *current;
	
	current = 0;
	c = 0;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
			current = get_board_value(board,j,i);
            if(current && get_id_player(current) != idPlayer && can_move(board,j,i))
                    c++;
        }
    }

    if(c>0){
        return 0;
    } else {
        return 1;
    }
}

/*
 * Restituisce 1 se la mossa è stata fatta, 0 se non è stato possibile
 *
 * Le coordinate inserite sono corrette in fase di input (sono all'interno della scacchiera e non sono caselle proibite)
 * Verifica che la distanza ed il grado siano compatibili con la mossa
 * distance -> distanza tra due punti
 * grade_cntrl -> ctrl spostamento tipo pedina
 * existM -> se esiste mossa obb.
 *legal ply-> ctrl player che muove
*/
int move(pedina** board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, unsigned turn){

    printf("\nMOVE From: %d,%d --> To: %d,%d", from_x,from_y,to_x ,to_y);

    int success, d, grade_control, existM, legal_player;
    
	success = 1;
	
	printf("\ndist: ");
	d = distance(from_x,from_y,to_x,to_y);
	printf("%d|\t", d);
	
	printf(" grade: ");
	grade_control = gradeCheck(board,from_x,from_y,to_y);
	printf("%d|\t", grade_control);
	
	printf(" legal_player: ");
	legal_player = (get_id_player(get_board_value(board,from_x,from_y)) == (turn %2));
	printf("%d|\t", legal_player);
	
	printf(" exist m: ");
	existM = existMandatory(board,from_x,from_y,to_x,to_y);
	printf("%d|\n", existM);
	
    
	if(!legal_player || get_board_value(board,to_x,to_y) || d == -1 || !grade_control || existM){
        success = 0;
    } else{
        if(d == 1){
            printf("\n\t--> if d == 1\n");
            set_board_value(board,to_x,to_y,get_board_value(board,from_x,from_y));
            set_board_value(board,from_x,from_y,0);
        }
        else if(d == 2){
            printf("\n\t--> if d == 2\n");
            unsigned middle_x;
            unsigned middle_y;

            middle_x = (from_x + to_x)/2;
            middle_y = (from_y+to_y)/2;

            if(get_board_value(board,middle_x,middle_y)){ /*verifica esistenza pedina in mezzo*/
                if(get_id_player(get_board_value(board,middle_x,middle_y)) == get_id_player(get_board_value(board,from_x,from_y)))
                    success = 0; /*se amica, annulla mossa*/
                else
                    capture(board,from_x,from_y,to_x,to_y); /*se nemica cattura*/
            }
            else
                success = 0;
        }
        else{
            success = 0;
		}
		
		if(success && (to_y == 6 || to_y == 0)){ /*Controllo per l'aumento del grado della pedina*/
			int tb;
			if(to_y == 6)
				tb = 1;
			if(to_y == 0)
				tb = 0;
				
			if(!(tb ^ get_id_player(get_board_value(board,to_x,to_y))))
				set_grade(get_board_value(board,to_x,to_y), Officer);
		} 
		
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
    int result;
    int dx = abs(to_x - from_x), dy = abs(to_y - from_y);

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
void capture(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y){ /*Correggi con funzioni ausiliarie*/

    unsigned middle_x = (from_x+to_x)/2, middle_y = (to_y+from_y)/2;
    pedina *prisoner = get_board_value(board,middle_x,middle_y);
    pedina *soldier = get_board_value(board,from_x,from_y);

    /*printf("\n MX %d, MY %d, FX %d, FY %d, TX %d, TY %d\n", middle_x,middle_y,from_x,from_y,to_x,to_y);
    printf("\n PRISONER %d, SOLDIER %d\n",prisoner->middle,prisoner->down );*/

    if(prisoner->middle || prisoner->down){ /*In questo ramo la pedina catturata ha pedine sottostanti*/
        /*printf("\n ENTRA NELL'IF CAPTURE ");*/
        if(get_id_player(prisoner->middle) == get_id_player(soldier) && prisoner->down && get_id_player(prisoner->down) == get_id_player(soldier)) {/*Se entrambe le pedine catturate dal prigioniero sono alleate*/
            /*printf("\n ENTRA NELL'IF 1.1 ");*/
            prisoner->middle->middle = prisoner->down;
            set_board_value(board,middle_x,middle_y,prisoner->middle);
        }
        else if(get_id_player(prisoner->middle) == get_id_player(soldier) && !(prisoner->down)){/*Se la pedina prigioniera è ha solo un prigioniero, alleato, l'altra è vuota*/
            /*printf("\n ENTRA  NELL'IF 1.2\n");*/
            set_board_value(board,middle_x,middle_y,prisoner->middle);
        }
        else if(get_id_player(prisoner->down) == get_id_player(soldier)){/*Se una delle pedine catturate dal prigioniero è alleata e l'altra è nemica*/
            prisoner->down->middle = prisoner->middle;
            set_board_value(board,middle_x,middle_y,prisoner->down);
        }
        else{/*La pedina catturata ha sotto una pedina, nemica*/
            if(!(soldier->down))
                soldier->down = prisoner->middle;

            free(get_board_value(board,middle_x,middle_y));
            set_board_value(board,middle_x,middle_y,0);
        }

        if(soldier->middle){
            if(!soldier->down)
                soldier->down = prisoner;
        }else
            soldier->middle = prisoner;
    }
    else{ /*In questo ramo la pedina catturata non ha pedine sottostanti*/
        set_board_value(board,middle_x,middle_y,0);

        if(soldier->middle && !(soldier->down)){  /*Sistema la pedina catturata nella pedina del catturante*/
            soldier->down = prisoner;
        }
        else {
            soldier->middle = prisoner;
        }
    }

    set_board_value(board,from_x,from_y,0);
    set_board_value(board,to_x,to_y,soldier);
}

/* Verifica il grado della pedina mossa:
 * restituisce 1 se la mossa è consentita, 0 se non è consentita
*/
int gradeCheck(pedina **board, unsigned from_x, unsigned from_y, unsigned to_y){ /*IMPLEMENTA UP/DOWN*/

    int success = 1;
	/*printf("\n\t\t GRADE CHECK");*/
    if(get_board_value(board,from_x,from_y)) { /* controlla se la casella è piena o vuota*/
        /*printf("\n\n\t\t\t FROM: %d,%d --> to X,%d\n\n", from_x, from_y, to_y);*/
        if (!get_grade(get_board_value(board, from_x, from_y))) { /*controlla il grado della pedina*/

            if (!get_id_player(get_board_value(board, from_x, from_y))) {

                if (to_y > from_y){
                    /*printf("\n\n\t\t\t\t if toY %d > fromy %d\n\n", to_y,from_y);*/
                    success = 0;
                }

            } else { /*controlla se la pedina appartiene al giocatore 1*/
                if (to_y < from_y) {
                    /*printf("\n\n\t\t\t\t if toY %d < fromy %d\n\n", to_y,from_y)*/;
                    success = 0;
                }
            }
        }
    } else {
        /*printf("\n\n\t\t\t default \n\n");*/
        success = 0;
    }

    return success;

}

/*
* Verifica che la pedina in x,y possa mangiare almeno una pedina avversaria
* Viene verificata prima l'esistenza della casella a distanza due, poi che questa sia libera e che la casella adiacente sia occupata.
* Poi viene verificata la possibilità di mangiare la pedina nella casella adiacente.    
*/
int can_eat(pedina **board, int x, int y){
	int success;
	id_p current_player;
	gr current_grade;
	
	current_grade = get_grade(get_board_value(board,x,y));
	current_player = get_id_player(get_board_value(board,x,y));
	success = 0;
	
	
	if(is_inside(x+2,y+2) && !get_board_value(board,x+2,y+2) && get_board_value(board,x+1,y+1) && right_path(Down,current_grade,current_player)){ /*Controllo (x+2,y+2)*/
		success = get_id_player(get_board_value(board,x + 1,y + 1)) != current_player;
	}
	else if(is_inside(x+2,y-2) && !get_board_value(board,x+2,y-2) && get_board_value(board,x+1,y-1) && right_path(Up,current_grade,current_player)){
		success = get_id_player(get_board_value(board,x + 1,y - 1)) != current_player;	
	}
	else if(is_inside(x-2,y-2) && !get_board_value(board,x-2,y-2) && get_board_value(board,x-1,y-1) && right_path(Up,current_grade,current_player)){
		success = get_id_player(get_board_value(board,x - 1,y - 1)) != current_player;
	}
	else if(is_inside(x-2,y+2) && !get_board_value(board,x-2,y+2) && get_board_value(board,x-1,y+1) && right_path(Down,current_grade,current_player)){
		success = get_id_player(get_board_value(board,x - 1,y + 1)) != current_player;
	}
	
	return success;
		
}

/*
* Verifica che la pedina in x,y possa mangiare almeno una pedina avversaria
* Viene verificata prima l'esistenza della casella a distanza due, poi che questa sia libera e che la casella adiacente sia occupata.
* Poi viene verificata la possibilità di mangiare la pedina nella casella adiacente.    
*/
int can_move(pedina **board, int x, int y){

	int success;
	id_p current_player;
	gr current_grade;
	
	current_grade = get_grade(get_board_value(board,x,y));
	current_player = get_id_player(get_board_value(board,x,y));

	success = 0;
	
	if(is_inside(x+1,y+1) && !get_board_value(board,x+1,y+1) && right_path(Down,current_grade,current_player)){ /*Controllo (x+2,y+2)*/
		success = 1;
	}
	else if(is_inside(x+1,y+1) && !get_board_value(board,x+1,y-1) && right_path(Up,current_grade,current_player)){
		success = 1;	
	}
	else if(is_inside(x-1,y-1) && !get_board_value(board,x-1,y-1) && right_path(Up,current_grade,current_player)){
		success = 1;
	}
	else if(is_inside(x-1,y+1) && !get_board_value(board,x-1,y+1) && right_path(Down,current_grade,current_player)){
		success = 1;
	}
	
	return success || can_eat(board,x,y);
		
}

/* Verifica se, nel caso di non cattura, esiste una cattur obbligatoria da fare
 * Restituisce 1 se esiste una mossa obbligatoria non tentata, altrimenti 0
 */
int existMandatory(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y){

    int success;
	unsigned i, j;
	id_p current_player;
	
	success = 0;
	
	if(get_board_value(board,from_x,from_y)){
		
		current_player = get_id_player(get_board_value(board,from_x,from_y));
		
		printf("\nPedina partenza:\tcan_eat: %d\nMosse obbligatorie:\n", can_eat(board,from_x,from_y));
	
		if(distance(from_x,from_y,to_x,to_y) != 2 || !can_eat(board,from_x,from_y)){/*Se la pedina di partenza non sta mangiando*/
			for(i = 0; i < COL; i++){
				for(j = 0; j < ROW; j++){
					if(get_board_value(board,i,j) && (get_id_player(get_board_value(board,i,j)) == current_player) && can_eat(board,i,j)){
						printf("%d,%d \n",i,j);
						success = 1; /*esite pedina(i,j) && è amica && può mangiare*/
						break;
					}
				}	
			}
			printf("\n");
		}
	}	

    return success;
}