#include<stdio.h>
#include<stdlib.h>
#include "ml_lib.h"

/*---------------------------------SEZIONE FUNZIONI AUSILIARIE---------------------------------*/

/* Imposta l'id_player della pedina indicata dal puntatore*/
void set_id_player(pedina *p, id_p value){
    if(p)
        p->id_player = value;
}

/* Ritorna il p->id_player della pedina specificata */
id_p get_id_player(pedina *p){
    return p->id_player;
}

/* Imposta il valore value nella posizione indicata nella scacchiera*/
void set_board_value(pedina **board, unsigned x, unsigned y, pedina *value){
    board[x * COL + y] = value;
}

/* Ritorna il valore nella posizione indicata nella scacchiera*/
pedina* get_board_value(pedina **board, unsigned x, unsigned y){
    return board[x * COL + y];
}

/* Ritorna il valore della pedina middle nella posizione indicata nella scacchiera*/
pedina* get_board_value_middle(pedina **board, unsigned x, unsigned y){
    if(!board[x * COL + y])
        return 0;
    else
        return board[x * COL + y]->middle;
}

/* Ritorna il valore della pedina down nella posizione indicata nella scacchiera*/
pedina* get_board_value_down(pedina **board, unsigned x, unsigned y){
    if(!board[x * COL + y])
        return 0;
    else
        return board[x * COL + y]->down;
}

/* Imposta il grado di una pedina*/
void set_grade(pedina *p,gr value){
    if(p)
        p->grado = value;
}

/* Ritorna il grado di una pedina*/
gr get_grade(pedina *p){

    return p->grado;
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
            if(isForbiddenCell(i,j) || i == 3){
                set_board_value(board,i,j,NULL);
            }
            else{
                pedina *a = NULL;
                a = (pedina*) malloc(sizeof(pedina));
                set_grade(a,Soldier);
                a->down=NULL;
                a->middle=NULL;

                if(i < 3)
                    set_id_player(a, UserTwo);
                else
                    set_id_player(a, UserOne);

                set_board_value(board,i,j,a);
            }
        }
    }
}

/*---------------------------------SEZIONE FUNZIONI OUTPUT---------------------------------*/

/* Stampa un carattere ASCII identificativo del contenuto della casella p
 *
 * PROVO A TOGLIERE IL CONTROLLO DEL NULL
 *
 * */
void printPedina(pedina *p){

    if(!p){}
    else if(get_id_player(p) && get_grade(p))
        printf("N ");
    else if(get_id_player(p) && !get_grade(p))
        printf("n ");
    else if(!get_id_player(p) && get_grade(p))
        printf("B ");
    else
        printf("b ");
}

/* Funzione che stampa la scacchiera in base al posizionamento delle pedine. */
void printMatrix(pedina** board){

    unsigned i,j;

    for(i=0; i<ROW; i++){


    	printf("%c > ",('A'+ i));

    	for(j=0;j<COL;j++){

            if ((i % 2 && !(j % 2)) || (!(i % 2) && (j % 2)))
                printf("# ");
            else if(!get_board_value(board,i,j)){
                printf("  ");
            }
            else{
                printPedina(get_board_value(board,i,j));
                printPedina(get_board_value_middle(board,i,j));
                printPedina(get_board_value_down(board,i,j));
            }

    	}
     printf("\n");
    }

    printf("    ");

    for(i=0;i<COL;i++)
    	printf("^ ");

    printf("\n");

    printf("    ");

    for(i=0;i<COL;i++)
    	printf("%d ", (i+1));
}

void printStatus(unsigned turn){
    printf("\n\n\nTurn number: %u\nMove player: %u\n",(turn+1),((id_p)(turn%2)));
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
        printf("\tComplimenti umano, grande vittoria!!!");
    else
        printf("\tComplimenti UserTwo, grande vittoria!!!");
}

void inputError(){
    printf("\tNon puoi spostarti in quella casella!");
}

/*---------------------------------SEZIONE FUNZIONI MOVE---------------------------------*/

/*
 * FUNZIONE CHE PRENDE IN INPUT CORDINATE PER LO SPOSTAMENTO DELLA PEDINA
*/

int catchInput(int *cord){
    char *v = (char *)malloc(sizeof(char)*4);
    int i;

    printf("\n\nInserisci le coordinate della pedina da muovere: \n\n");

    printf("Coordinata Alfabetica: \n");

    do{
        if(scanf(" %c",&v[0])!=1)
            perror("Errore acquisizione coordinata");

    }while(!(v[0]>='a' && v[0]<='g'));

    cord[0]=((v[0]-96)-1);

    printf("Coordinata Numerica: \n");

    do{
        if(scanf(" %c",&v[1])!=1)
            perror("Errore acquisizione coordinata");

    }while(!(v[1]>='1' && v[1]<='7'));

    cord[1]=((v[1]-'0')-1);

    printf("\n\nInserisci le coordinate di destinazione: \n\n");

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


    for(i=0;i<4;i++){
        printf("\n-- cord[%d] -> %d\n",i,cord[i]);
    }


    return 1;
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
int move(pedina** board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, id_p first, unsigned turn){
    int success = 1, d = distance(from_x,from_y,to_x,to_y), grade_control = gradeCheck(board,from_x,from_y,to_y), existM = existMandatory(board,from_x,from_y,to_x,to_y), legal_player = (first == (turn %2));
    if(!legal_player || get_board_value(board,to_x,to_y) || d == -1 || !grade_control || existM)
        success = 0;
    else{
        if(d == 1){
            set_board_value(board,to_x,to_y,get_board_value(board,from_x,from_y));
            set_board_value(board,from_x,from_y,0);
        }
        else if(d == 2){
            unsigned middle_x = (from_x + to_x)/2, middle_y = (from_y+to_y)/2;
            if(get_board_value(board,middle_x,middle_y)){ /*verifica esistenza pedina in mezzo*/
                if(get_id_player(get_board_value(board,middle_x,middle_y)) == get_id_player(get_board_value(board,from_x,from_y)))
                    success = 0; /*se amica, annulla mossa*/
                else
                    capture(board,from_x,from_y,to_x,to_y); /*se nemica cattura*/
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
int distance(unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y){
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
void capture(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y){ /*Correggi con funzioni ausiliarie*/

    unsigned middle_x = (from_x+to_x)/2, middle_y = (to_y+from_y)/2;
    pedina *prisoner = get_board_value(board,middle_x,middle_y);
    pedina *soldier = get_board_value(board,from_x,from_y);

    if(prisoner->middle || prisoner->down){ /*In questo ramo la pedina catturata ha pedine sottostanti*/
        if(get_id_player(prisoner->middle) == get_id_player(soldier) && get_id_player(prisoner->down) == get_id_player(soldier)) {/*Se entrambe le pedine catturate dal prigioniero sono alleate*/
            prisoner->middle->middle = prisoner->down;
            set_board_value(board,middle_x,middle_y,prisoner->middle);
        }
        else if(get_id_player(prisoner->middle) == get_id_player(soldier) && !(prisoner->down)){/*Se la pedina prigioniera è ha solo un prigioniero, alleato, l'altra è vuota*/
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

    set_board_value(board,middle_x,middle_y,soldier);
}

/* Verifica il grado della pedina mossa:
 * restituisce 1 se la mossa è consentita, 0 se non è consentita
*/
int gradeCheck(pedina **board, unsigned from_x, unsigned from_y, unsigned to_y){
    int success = 1;

    if(get_board_value(board,from_x,from_y)){
        if(!get_grade(get_board_value(board,from_x,from_y)) && (to_y - from_y) > 0) /*get_board_value al posto di p[from_x][from_y]*/
            success = 0;
    } else {
        success = 0;
    }

    return success;
}

/* Verifica se, nel caso di non cattura, esiste una cattur obbligatoria da fare
 * Restituisce 1 se esiste una mossa obbligatoria non tentata, altrimenti 0
 */
int existMandatory(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y){

    int success = 0, dx = to_x - from_x, dy = to_y - from_y;

    if(distance(from_x,from_y,to_x,to_y) == 2){
        success = 0;
    }
    else{
        if(get_board_value(board,from_x-dx,from_y-dy) || get_board_value(board,from_x+dx,from_y-dy) || get_board_value(board,from_x-dx,from_y+dy)) { /*Verifico l'esitenza di pedine intorno alla posizione di partenza*/
            if(get_board_value(board,from_x-dx,from_y-dy)){
                if(get_id_player(get_board_value(board,from_x-dx,from_y-dy)) != get_id_player(get_board_value(board,from_x,from_y)) && !get_board_value(board,from_x-2*dx,from_y-2*dy)) /*Verifico che siano nemiche e che la casella successiva sia libera*/
                    success = 1;
            }
            else if(get_board_value(board,from_x+dx,from_y-dy)){
                if(get_id_player(get_board_value(board,from_x+dx,from_y-dy)) != get_id_player(get_board_value(board,from_x,from_y)) && !get_board_value(board,from_x+2*dx,from_y-2*dy))
                    success = 1;
            }
            else{
                if(get_id_player(get_board_value(board,from_x-dx,from_y+dy)) != get_id_player(get_board_value(board,from_x,from_y)) && !get_board_value(board,from_x-2*dx,from_y+2*dy))
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
int isWinner(pedina **board, id_p idPlayer) {

    int i,j,c=0;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (!c) {
                if (get_id_player(board[i * COL + j]) == idPlayer)
                    c++;
            } else
                return 0;
        }
    }

    return 1;
}
