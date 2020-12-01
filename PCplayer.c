#include<stdio.h>
#include<stdlib.h>
#include "ml_lib.h"

/*---------------------------------SEZIONE DEFINIZIONI---------------------------------*/

typedef struct {
    unsigned x;
    unsigned y;
} position;

typedef enum {DownRight, DownLeft, UpRight, UpLeft} direction;

typedef struct {
    position pos;
    int legal;
    int occupied;
    int enemy;
} cell_status;

/*---------------------------------SEZIONE FUNZIONI AUSILIARIE---------------------------------*/

int is_position_legal(position pos){
    if (pos.x > 0 && pos.y > 0 && pos.y < ROW && pos.x < COL)
        return 1;
    else
        return 0;
}

int isOccupied(pedina ***board, position pos){
    if(get_board_value(board, pos.x, pos.y))
        return 1;
    else
        return 0;
}

/*Restituisce la posizione modificata nella direzione indicata*/
pos change_position(position p, direction d){

    switch(d){
        case UpLeft:
            pos.x += -1;
            pos.y += -1;
            break;
        case UpRight:
            pos.x += 1;
            pos.y += -1;
            break;
        case DownLeft:
            pos.x += -1;
            pos.y += 1;
            break;
        case DownRight:
            pos.x += 1;
            pos.y += 1;
            break;
    }

    return pos;

}

int min(int x, int y){
    if(x > y)
        return y;
    else
        return x;
}

int max(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

/*
 * Restituisce lo stato delle cellule adiacenti
 * con distance = 0 restituisce lo status delle cellule a distanza 1, con distance = 1 restituisce quello di quelle a distanza 2
 */
cell_status* create_status(position pos, int distance, pedina ***board){

    cell_status  *result = (cell_status*) malloc(sizeof(cell_status)*4);
    id_p me = get_id_player(get_board_value(board, pos.x, pos.y));

    if(!result){
        exit(0);
    }
    else{
        int i;
        for(i = 0; i < 4; i++){
            result[i].pos = change_position(pos, i);
            result[i].legal = is_position_legal(result[i].pos);
            result[i].occupied = result[i].legal && isOccupied(board, result[i].pos);
            if(result[i].occupied)
                result[i].enemy = me != get_id_player(get_board_value(board, result[i].pos.x, result[i].pos.y));
        }
    }

    return result;
}

void destroy_status(cell_status *p){
    free(p);
}

/*---------------------------------SEZIONE FUNZIONI MINIMAX---------------------------------*/


/*
 * Restituisce un numero positivo se mangia, 0 se non succede niente, un numero negativo se viene mangiata
 * Intervallo del risultato è [-4,4]
 * Assumo che la pedina in pos sia soldato
 *
 */
int evaluate_position(position pos, pedina ***board){
    int result = 0, i;
    cell_status *stat = create_status(pos, board);

    for(i = 0; i < 4; i++){
        if(stat[i])
    }


    destroy_status(stat);
    return result;
}

/*
 * Versione per soldati, due possibilità contemplate.
 * Il Pc si troverà nella parte alta dello schermo, quindi andrà verso il basso secondo il punto di vista dell'utente
 * L'origine si trova in alto a sinistra,  i rami positivi di x e y sono rispettivamente verso destra e verso il basso
 * */
int minimax(position pos, int depth, id_p player, pedina ***board){
    int a = 0;
    position next[4] = {change_position(pos, DownRight), change_position(pos, DownLeft), change_position(pos, UpRight), change_position(pos, UpLeft)};
    if(!depth)
        return evaluate_position(pos);
    if(player){
        if(is_position_legal(next[0])){
            a = INT_MAX;
            a = min(a, minimax(next[0], depth - 1, !player, board));
        }
        if(is_position_legal(next[1])){
            a = min(a, minimax(next[1], depth - 1, !player, board));
        }

    }
    else{
        if(is_position_legal(next[0])) {
            a = INT_MIN;
            a = max(a, minimax(next[0], depth - 1, !player, board));
        }
        if(is_position_legal(next[1])) {
            a = max(a, minimax(next[1], depth - 1, !player, board));
        }
    }
    return a;
}

