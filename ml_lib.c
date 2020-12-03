#include<stdio.h>
#include<stdlib.h>
#include "ml_lib.h"

/*---------------------------------SEZIONE FUNZIONI AUSILIARIE---------------------------------*/

void set_id_player(pedina *p, id_p value){
	if(p)
		p->id_player = value;
}

id_p get_id_player(pedina *p){
	return p->id_player;
}

void set_board_value(pedina **board, unsigned x, unsigned y, pedina *value){
    board[x * COL + y] = value;
}

pedina* get_board_value(pedina **board, unsigned x, unsigned y){
    return board[x * COL + y];
}

pedina* get_board_value_middle(pedina **board, unsigned x, unsigned y){
    if(!get_board_value(board,x,y))
        return 0;
    else
        return board[x * COL + y]->middle;
}

pedina* get_board_value_down(pedina **board, unsigned x, unsigned y){
    if(!get_board_value(board,x,y))
        return 0;
    else
        return board[x * COL + y]->down;
}

void set_grade(pedina *p,gr value){
	if(p)
		p->grado = value;
}

gr get_grade(pedina *p){
    return p->grado;
}

/*---------------------------------SEZIONE FUNZIONI LOGICHE DI GIOCO---------------------------------*/

int isWinner(pedina **p, id_p idPlayer) {

    int i,j,c=0;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (!c) {
                if (get_id_player(get_board_value(p,i,j)) == idPlayer)
                    c++;
            } else
                return 0;
        }
    }

    return 1;
}

int isForbiddenCell(unsigned x, unsigned y){
    if((x % 2 && !(y % 2)) || (!(x % 2) && (y % 2)))
        return 1;
    else
        return 0;
}

/*---------------------------------SEZIONE FUNZIONI GESTIONE MEMORIA---------------------------------*/

pedina **createMatrix(){

    pedina** board = (pedina **) malloc(ROW*COL*sizeof(pedina *));

    if(!board){
        printf("createMatrix failed malloc");
        return 0;
    }
    else
        return board;
}

void destroyMatrix(pedina **p){
    free(p);
}

void fillBoard(pedina **p){
	
	unsigned i,j;
	
	for(i = 0; i < COL; i++){
            for(j = 0; j < COL; j++){
				printf("\t\ti: %d, j:%d\n",i,j);
				if(isForbiddenCell(i,j) || i == 3){
					set_board_value(p,i,j,0);
				}
				else{
					pedina *a = NULL;
					a = (pedina*) malloc(sizeof(pedina));
					set_grade(a,Soldier);
					if(i < 3)
						set_id_player(a, UserTwo);
					else
						set_id_player(a, UserOne);

					set_board_value(p,i,j,a);
				}
            }
        }
}

/*---------------------------------SEZIONE FUNZIONI OUTPUT---------------------------------*/

void printPedina(pedina *p){
    if(!p)
        printf(" ");
    else if(get_id_player(p) && get_grade(p))
        printf("N");
    else if(get_id_player(p) && !get_grade(p))
        printf("n");
    else if(!get_id_player(p) && get_grade(p))
        printf("B");
    else
        printf("b");
}

void printMatrix(pedina **p){

    unsigned i,j;

    for(i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if ((i % 2 && !(j % 2)) || (!(i % 2) && (j % 2))) /*Caselle oscurate*/
                printf("# ");
            else if(!get_board_value(p,i,j)){
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
    if(winner == UserOne)
        printf("\tComplimenti umano, grande vittoria!!!");
    else
        printf("\tComplimenti UserTwo, grande vittoria!!!");
}

void inputError(){
    printf("\tNon puoi spostarti in quella casella!");
}

/*---------------------------------SEZIONE FUNZIONI MOVE---------------------------------*/

int catchInput(int *cord){
    char *a;
    size_t bufsize = 10;
    int success = 1;

    a=(char *)malloc(bufsize*sizeof(char));

    if(!a){
        perror("Malloc error");
        exit(1);
    }

    /*acquisizione stringa dall'input*/
    if(getline(&a,&bufsize,stdin) != 1){
		perror("Getline erroe");
		exit(1);
	}
		

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

int move(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, id_p first, unsigned turn){
    int success = 1, d = distance(from_x,from_y,to_x,to_y), grade_control = gradeCheck(p,from_x,from_y,to_y), existM = existMandatory(p,from_x,from_y,to_x,to_y), legal_player = first == (turn %2);
    if(!legal_player || get_board_value(p,to_x,to_y) || d == -1 || !grade_control || existM)
        success = 0;
    else{
        if(d == 1){
            set_board_value(p,to_x,to_y,get_board_value(p,from_x,from_y));
            set_board_value(p,from_x,from_y,0);
        }
        else if(d == 2){
            unsigned middle_x = (from_x + to_x)/2, middle_y = (from_y+to_y)/2;
            if(get_board_value(p,middle_x,middle_y)){ /*verifica esistenza pedina in mezzo*/
                if(get_id_player(get_board_value(p,middle_x,middle_y)) == get_id_player(get_board_value(p,from_x,from_y)))
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

int distance(int from_x, int from_y, int to_x, int to_y){
    int result, dx = abs(to_x - from_x), dy = abs(to_y - from_y);

    if(dx == dy && dx && dx < 3)
        result = dx;
    else
        result = -1;

    return result;
}

void capture(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y){ /*Correggi con funzioni ausiliarie*/

    unsigned middle_x = (from_x+to_x)/2, middle_y = (to_y+from_y)/2;
    pedina *prisoner = get_board_value(p,middle_x,middle_y);
    pedina *soldier = get_board_value(p,from_x,from_y);

    if(prisoner->middle || prisoner->down){ /*In questo ramo la pedina catturata ha pedine sottostanti*/
        if(get_id_player(prisoner->middle) == get_id_player(soldier) && get_id_player(prisoner->down) == get_id_player(soldier)) {/*Se entrambe le pedine catturate dal prigioniero sono alleate*/
            prisoner->middle->middle = prisoner->down;
            set_board_value(p,middle_x,middle_y,prisoner->middle);
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
			
			free(get_board_value(p,middle_x,middle_y));
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

int gradeCheck(pedina **p, unsigned from_x, unsigned from_y, unsigned to_y){
    int success = 1;

    if(!get_grade(get_board_value(p,from_x,from_y)) && (to_y - from_y) > 0) /*get_board_value al posto di p[from_x][from_y]*/
        success = 0;

    return success;
}

int existMandatory(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y){

    int success = 0, dx = to_x - from_x, dy = to_y - from_y;

    if(distance(from_x,from_y,to_x,to_y) == 2){
        success = 0;
    }
    else{
        if(get_board_value(p,from_x-dx,from_y-dy) || get_board_value(p,from_x+dx,from_y-dy) || get_board_value(p,from_x-dx,from_y+dy)) { /*Verifico l'esitenza di pedine intorno alla posizione di partenza*/
            if(get_board_value(p,from_x-dx,from_y-dy)){
                if(get_id_player(get_board_value(p,from_x-dx,from_y-dy)) != get_id_player(get_board_value(p,from_x,from_y)) && !get_board_value(p,from_x-2*dx,from_y-2*dy)) /*Verifico che siano nemiche e che la casella successiva sia libera*/
                    success = 1;
            }
            else if(get_board_value(p,from_x+dx,from_y-dy)){
                if(get_id_player(get_board_value(p,from_x+dx,from_y-dy)) != get_id_player(get_board_value(p,from_x,from_y)) && !get_board_value(p,from_x+2*dx,from_y-2*dy))
                    success = 1;
            }
            else{
                if(get_id_player(get_board_value(p,from_x-dx,from_y+dy)) != get_id_player(get_board_value(p,from_x,from_y)) && !get_board_value(p,from_x-2*dx,from_y+2*dy))
                    success = 1;
            }
        }
        else
            success = 0;
    }

    return success;
}
