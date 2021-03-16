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
void set_board_value(pedina **board, point p, pedina *value){
    board[p.y * COL + p.x] = value;
}

/* Ritorna il valore nella posizione indicata nella scacchiera*/
pedina* get_board_value(pedina **board, point p){
    return board[p.y * COL + p.x];
}

/* Ritorna il valore nella posizione indicata nella scacchiera*/
pedina* get_board_value_immediate(pedina **board, int x, int y){
    return board[y * COL + x];
}

/* Ritorna il valore della pedina middle nella posizione indicata nella scacchiera*/
pedina* get_board_value_middle(pedina **board, point p){
    if(!board[p.y * COL + p.x])
        return 0;
    else
        return board[p.y * COL + p.x]->middle;
}

/* Ritorna il valore della pedina down nella posizione indicata nella scacchiera*/
pedina* get_board_value_down(pedina **board, point p){
    if(!board[p.y * COL + p.x])
        return NULL;
    else
        return board[p.y * COL + p.x]->down;
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
    return (x >= 0) && (x <= 6) && (y >= 0) && (y <= 6);
}

/*Ritorna 1 la direzione della pedina è giusta*/
int right_path(dir direction, gr grade, id_p player){
    return grade || !(direction^player);
}

/*Ritorna 1 se input è una lettera da a ad g, altrimenti è 0*/
int is_valid_letter(char input){
    return ((input >= 'a') && (input <= 'g'));
}

/*Ritorna 1 se input è un numero da 1 a 7, altrimenti è 0*/
int is_valid_number(char input){
    return (input >= 49) && (input <= 55);
}

/*Ritorna 1 se l'input da tastiera è valido, altrimenti è 0*/
int is_valid_input(char input[5]){
    return is_valid_letter(input[0]) && is_valid_number(input[1]) && is_valid_letter(input[2]) && is_valid_number(input[3]);
}

void print_coord(int *c){
    printf("\n");
    for(int i=0;i<4;i++){
        if(i%2==0)
            printf("i: %d -> x= %d\n",i,c[i]);
        else
            printf("i: %d -> y= %d\n",i,c[i]);
    }
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
int isForbiddenCell(point p){
    if((p.x % 2 && !(p.y % 2)) || (!(p.x % 2) && (p.y % 2)))
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

    int i,j;
    point p;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            p.x = j;
            p.y = i;
            if(isForbiddenCell(p) || i == 3){
                set_board_value(board,p,0);
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
                set_board_value(board,p,a);
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
int catchInput(int *cord){
    char input[5];
    int success = 0;
    do{
        printf("\tInserisci le coordinate della mossa [LETTERA-NUMERO-LETTERA-NUMERO]: \n\t\t");
        scanf("%s",input);
        
        if(is_valid_input(input)){ /*Controllo validità input*/
            success = 1;
            printf("\n");}
        else
            printf("\t\t[Input Error] Coordinate inserite non valide \n");
    }while(!success);
    
    cord[0] = input[0] - 'a';
    cord[1] = input[1] - '0' - 1;
    cord[2] = input[2] - 'a';
    cord[3] = input[3] - '0' - 1;
    
    return success;
    
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

    int i,j;
    point p;

    for(i=0; i<ROW; i++){

        printf("%c > ",('A'+ i));

        for(j=0;j<COL;j++){
            p.x = j;
            p.y = i;

            if ((i % 2 && !(j % 2)) || (!(i % 2) && (j % 2)))
                printf("###");
            else if(!get_board_value(board,p)){
                printf("   ");
            }
            else{
                printPedina(get_board_value(board,p));
                printPedina(get_board_value_middle(board,p));
                printPedina(get_board_value_down(board,p));
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

void printStatus(int turn){
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
    point p;
    current = 0;
    c = 0;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) { /*Controllo ordine coordinate*/
            p.x = j;
            p.y = i;
            current = get_board_value(board,p);
            if(current && get_id_player(current) != idPlayer && can_move(board,p)) /*Prima era j,i*/
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
int my_move(pedina** board, point from, point to, int turn){

    int success, d, grade_control, existM, legal_player;

    success = 1;
    
    printf("\npedina from: %d\t",get_board_value(board,from));
    
    printf("pedina to: %d\t",get_board_value(board,to));
    
    printf("\n 1 FROM x: %d, y: %d\n",from.x, from.y);
    printf("dist: ");
    d = distance(from,to);
    printf("%d|\t", d);
    
    printf("grade: ");
    grade_control = gradeCheck(board,from,to);
    printf("%d|\t", grade_control);
    
    printf("legal_player: ");
    legal_player = (get_id_player(get_board_value(board,from)) == (turn %2));
    printf("%d|\t", legal_player);
    
    printf("exist m: ");
    existM = existMandatory(board,from,to); /*Da rivederla*/
    printf("%d|\n", existM);
    
    
    if(!legal_player || !get_board_value(board,from) || get_board_value(board,to) || d == -1 || !grade_control || existM){
        success = 0;
    } else{
        if(d == 1){
            printf("\n\t--> if d == 1\n");
            set_board_value(board,to,get_board_value(board,from));
            set_board_value(board,from,0);
        }
        else if(d == 2){
            printf("\n\t--> if d == 2\n");
            point middle;
            middle.x = (from.x + to.x)/2;
            middle.y = (from.y + to.y)/2;

            if(get_board_value(board,middle)){ /*verifica esistenza pedina in mezzo*/
                if(get_id_player(get_board_value(board,middle)) == get_id_player(get_board_value(board,from)))
                    success = 0; /*se amica, annulla mossa*/
                else
                    capture(board,from,to); /*se nemica cattura*/
            }
            else
                success = 0;
        }
        else{
            success = 0;
        }
        
        if(success && (to.y == 6 || to.y == 0)){ /*Controllo per l'aumento del grado della pedina*/
            int tb;
            if(to.y == 6)
                tb = 1;
            if(to.y == 0)
                tb = 0;
                
            if(!(tb ^ get_id_player(get_board_value(board,to))))
                set_grade(get_board_value(board,to), Officer);
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
int distance(point from, point to){
    int result;
    int dx = abs(to.x - from.x), dy = abs(to.y - from.y);

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
void capture(pedina **board, point from, point to){ /*Correggi con funzioni ausiliarie*/

    point mid;
    mid.x = (from.x+to.x)/2;
    mid.y = (to.y+from.y)/2;
    pedina *prisoner = get_board_value(board,mid);
    pedina *soldier = get_board_value(board,from);

    /*printf("\n MX %d, MY %d, FX %d, FY %d, TX %d, TY %d\n", mid,from.x,from.y,to.x,to.y);
    printf("\n PRISONER %d, SOLDIER %d\n",prisoner->middle,prisoner->down );*/

    if(prisoner->middle || prisoner->down){ /*In questo ramo la pedina catturata ha pedine sottostanti*/
        /*printf("\n ENTRA NELL'IF CAPTURE ");*/
        if(get_id_player(prisoner->middle) == get_id_player(soldier) && prisoner->down && get_id_player(prisoner->down) == get_id_player(soldier)) {/*Se entrambe le pedine catturate dal prigioniero sono alleate*/
            /*printf("\n ENTRA NELL'IF 1.1 ");*/
            prisoner->middle->middle = prisoner->down;
            set_board_value(board,mid,prisoner->middle);
        }
        else if(get_id_player(prisoner->middle) == get_id_player(soldier) && !(prisoner->down)){/*Se la pedina prigioniera è ha solo un prigioniero, alleato, l'altra è vuota*/
            /*printf("\n ENTRA  NELL'IF 1.2\n");*/
            set_board_value(board,mid,prisoner->middle);
        }
        else if(get_id_player(prisoner->down) == get_id_player(soldier)){/*Se una delle pedine catturate dal prigioniero è alleata e l'altra è nemica*/
            prisoner->down->middle = prisoner->middle;
            set_board_value(board,mid,prisoner->down);
        }
        else{/*La pedina catturata ha sotto una pedina, nemica*/
            if(!(soldier->down))
                soldier->down = prisoner->middle;

            free(get_board_value(board,mid));
            set_board_value(board,mid,0);
        }

        if(soldier->middle){
            if(!soldier->down)
                soldier->down = prisoner;
        }else
            soldier->middle = prisoner;
        
        prisoner->middle = 0;
        prisoner->down = 0;
    }
    else{ /*In questo ramo la pedina catturata non ha pedine sottostanti*/
        set_board_value(board,mid,0);

        if(soldier->middle && !(soldier->down)){  /*Sistema la pedina catturata nella pedina del catturante*/
            soldier->down = prisoner;
        }
        else {
            soldier->middle = prisoner;
        }
    }

    set_board_value(board,from,0);
    set_board_value(board,to,soldier);
}

/* Verifica il grado della pedina mossa:
 * restituisce 1 se la mossa è consentita, 0 se non è consentita
*/
int gradeCheck(pedina **board, point from, point to){ /*IMPLEMENTA UP/DOWN*/

    int success = 1;
    if(get_board_value(board,from)) { /* controlla se la casella è piena o vuota*/
        if (!get_grade(get_board_value(board, from))) { /*controlla il grado della pedina*/

            if (!get_id_player(get_board_value(board, from))) {

                if (to.y > from.y){
                    success = 0;
                }

            } else { /*controlla se la pedina appartiene al giocatore 1*/
                if (to.y < from.y) {
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
int can_eat(pedina **board, point p){
    
    int success;
    success = 0;
    
        id_p current_player;
        gr current_grade;
    
        current_grade = get_grade(get_board_value(board,p));
        current_player = get_id_player(get_board_value(board,p));
    
        if(is_inside(p.x+2,p.y+2) && !get_board_value_immediate(board,p.x+2,p.y+2) && get_board_value_immediate(board,p.x+1,p.y+1) && right_path(Down,current_grade,current_player)){ /*Controllo (p.x+2,p.y+2)*/
            success = get_id_player(get_board_value_immediate(board,p.x + 1,p.y + 1)) != current_player;
        }
        else if(is_inside(p.x+2,p.y-2) && !get_board_value_immediate(board,p.x+2,p.y-2) && get_board_value_immediate(board,p.x+1,p.y-1) && right_path(Up,current_grade,current_player)){
            success = get_id_player(get_board_value_immediate(board,p.x + 1,p.y - 1)) != current_player;
        }
        else if(is_inside(p.x-2,p.y-2) && !get_board_value_immediate(board,p.x-2,p.y-2) && get_board_value_immediate(board,p.x-1,p.y-1) && right_path(Up,current_grade,current_player)){
            success = get_id_player(get_board_value_immediate(board,p.x - 1,p.y - 1)) != current_player;
        }
        else if(is_inside(p.x-2,p.y+2) && !get_board_value_immediate(board,p.x-2,p.y+2) && get_board_value_immediate(board,p.x-1,p.y+1) && right_path(Down,current_grade,current_player)){
            success = get_id_player(get_board_value_immediate(board,p.x - 1,p.y + 1)) != current_player;
        }
            
    return success;
}

/*
* Verifica che la pedina in x,y possa mangiare almeno una pedina avversaria
* Viene verificata prima l'esistenza della casella a distanza due, poi che questa sia libera e che la casella adiacente sia occupata.
* Poi viene verificata la possibilità di mangiare la pedina nella casella adiacente.
*/
int can_move(pedina **board, point p){

    int success = 0;
    id_p current_player;
    gr current_grade;
    
    current_grade = get_grade(get_board_value(board,p));
    current_player = get_id_player(get_board_value(board,p));

    
    if(is_inside(p.x+1,p.y+1) && !get_board_value_immediate(board,p.x+1,p.y+1) && right_path(Down,current_grade,current_player)){ /*Controllo (p.x+2,p.y+2)*/
        success = 1;
    }
    else if(is_inside(p.x+1,p.y-1) && !get_board_value_immediate(board,p.x+1,p.y-1) && right_path(Up,current_grade,current_player)){
        success = 1;
    }
    else if(is_inside(p.x-1,p.y-1) && !get_board_value_immediate(board,p.x-1,p.y-1) && right_path(Up,current_grade,current_player)){
        success = 1;
    }
    else if(is_inside(p.x-1,p.y+1) && !get_board_value_immediate(board,p.x-1,p.y+1) && right_path(Down,current_grade,current_player)){
        success = 1;
    }
    
    return success || can_eat(board,p);
        
}

/* Verifica se, nel caso di non cattura, esiste una cattur obbligatoria da fare
 * Restituisce 1 se esiste una mossa obbligatoria non tentata, altrimenti 0
 */
int existMandatory(pedina **board, point from, point to){

    int success;
    unsigned i, j;
    id_p current_player;
    
    success = 0;
    
    if(get_board_value(board,from)){ /*Controllo esistenza*/
        
        current_player = get_id_player(get_board_value(board,from));
        
        printf("\nPedina partenza:\tcan_eat: %d\nMosse obbligatorie:\n", can_eat(board,from));
    
        if(distance(from,to) != 2 || !can_eat(board,from)){/*Se la pedina di partenza non sta mangiando*/
            point p;
            for(i = 0; i < COL; i++){
                for(j = 0; j < ROW; j++){
                    p.x = i;
                    p.y = j;
                    if(get_board_value(board,p) && (get_id_player(get_board_value(board,p)) == current_player) && can_eat(board,p)){
                        printf("%d,%d \n",p);
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
