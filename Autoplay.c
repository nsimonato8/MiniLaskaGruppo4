#include<stdio.h>
#include<limits.h>
#include "Autoplay.h"

#define NUMERO_PEDINE 11
#define DIFFICOLTA 5

/*
* Legge i valori da db_mosse e li passa a cord
* Invoca select_pedina e traduce from->to
*/

void print_datab(t_node *db){
    for(int i=0;i<NUMERO_PEDINE;i++){
        printf("\nAlfa: %d",db[i].alfa);
        printf("\nStart.x: %d",db[i].start.x);
        printf("\nStart.y: %d",db[i].start.y);
        printf("\nEnd.x: %d",db[i].end.x);
        printf("\nEnd.y: %d",db[i].end.y);
        printf("\n");
    }
}

void create_db(t_node *db){
    db = (t_node*) malloc (sizeof(t_node)*NUMERO_PEDINE);
}

void fill_db(t_node *db, pedina **board){
    int i=0;
    int j;
    int k;
    int f=0;
    
    for(i=0;i<3;i++){
        
        if(i%2!=0) k=1;
        else k=0;
        
        for(j=k;j<7;j=j+2){
            t_node *app_db = (t_node*) malloc(sizeof(t_node));
            pedina *p = get_board_value_immediate(board, j, i);
            printf("\nI: %d, J: %d\n", i,j);
            
            app_db->alfa=0;
            app_db->start.x=i;
            app_db->start.y=j;
            app_db->end.x=0;
            app_db->end.y=0;
            app_db->data=p;
            
            db[f++]= *app_db;
        }
    }

}

void catchInput_Autoplay(pedina **board, int *cord, t_node *db, int turn){
    
    int i;
    for(i = 0; i < NUMERO_PEDINE; i++){
        //db[i] = minimax(board, db[i], DIFFICOLTA, turn);
    }
    
    t_node result = select_pedina(db);
    
    cord[1] = result.start.x ;
    cord[0] = result.start.y ;
    cord[3] = result.end.x ;
    cord[2] = result.end.y;
    
}

int can_be_eaten(pedina **board, point p){
    int success;
    pedina *avversario;
    
    success = 0;
    
    avversario = get_board_value_immediate(board,p.x-1,p.y-1);
    if(is_inside(p.x+1,p.y+1) && !get_board_value_immediate(board,p.x+1,p.y+1) && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (p.x+2,p.y+2)*/
        success = 1;
    }
    
    avversario = get_board_value_immediate(board,p.x-1,p.y+1);
    if(is_inside(p.x+1,p.y-1) && !get_board_value_immediate(board,p.x+1,p.y-1) && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (p.x+2,p.y+2)*/
        success = 1;
    }
    
    avversario = get_board_value_immediate(board,p.x+1,p.y+1);
    if(is_inside(p.x-1,p.y-1) && !get_board_value_immediate(board,p.x-1,p.y-1) && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (p.x+2,p.y+2)*/
        success = 1;
    }
    
    avversario = get_board_value_immediate(board,p.x+1,p.y-1);
    if(is_inside(p.x-1,p.y+1) && !get_board_value_immediate(board,p.x-1,p.y+1) && avversario && right_path(Up,avversario->grado,avversario->id_player)){ /*Controllo (p.x+2,p.y+2)*/
        success = 1;
    }
    
    return success;
}

void check_son(pedina **board, t_node *res, int x, int y, t_node *node, int *alfa, int depth, int turn){
    (*res).end.x = (*node).end.x + x;
    (*res).end.y = (*node).end.y + y;
    if (can_eat(board,(*res).end) || can_move(board,(*res).end)){
        *res = minimax(board,(*res),depth-1,turn+1);
        if(*alfa < res->alfa)
            *alfa = res->alfa;
    }
}

int evaluate(pedina **board, t_node node){
    if(can_eat(board,node.end))
        return 1;
    else if(can_be_eaten(board,node.end))
        return -1;
    else
        return 0;
    
}


/*
function minimax(nodo, profondità)

    SE nodo è un nodo terminale OPPURE profondità = 0
        return il valore euristico del nodo
        
    SE l'avversario deve giocare
        α := +∞
        PER OGNI figlio di nodo
            α := min(α, minimax(figlio, profondità-1))
            
            
    ALTRIMENTI dobbiamo giocare noi
        α := -∞
        PER OGNI figlio di nodo
            α := max(α, minimax(figlio, profondità-1))
            
            
    return α
*/
t_node minimax(pedina **board, t_node node, int depth, int turn){
    
    t_node res;
    if(!depth){
        res.alfa = evaluate(board, node);
    }else{
        int alfa;
        if(turn%2){ /*Gioca AI*/
            alfa = INT_MIN;
            
            /*+1,+1*/  /*void check_son(pedina **board, t_node *res, int x, int y, t_node *node, int *alfa, int depth, int turn)*/
            check_son(board, &res, +1, +1, &node, &alfa, depth, turn);
            
            /*-1,+1*/
            check_son(board, &res, -1, +1, &node, &alfa, depth, turn);
            
            if(get_grade(node.data) == Officer){
                /*+1,-1*/
                check_son(board, &res, +1, -1, &node, &alfa, depth, turn);
                /*-1,-1*/
                check_son(board, &res, -1, -1, &node, &alfa, depth, turn);
            }
            
        }else{ /*Gioca UMANO*/
            alfa = INT_MAX;
            /*-1,+1*/
            check_son(board, &res, +1, +1, &node, &alfa, depth, turn);
            
            /*-1,+1*/
            check_son(board, &res, -1, +1, &node, &alfa, depth, turn);
            
            if(get_grade(node.data) == Officer){
                /*+1,-1*/
                check_son(board, &res, +1, -1, &node, &alfa, depth, turn);
                
                /*-1,-1*/
                check_son(board, &res, -1, -1, &node, &alfa, depth, turn);
            }
            
        }
        
    }
    return res;
}

/*
* 1) Selezione riga
* 2) Selezione max alfa;
* 3) Ritorno pedina,mossa (t_node)
*/
t_node select_pedina(t_node db[NUMERO_PEDINE]){
    int i, max = INT_MIN;
    t_node res;
    for(i = 0; i < NUMERO_PEDINE; i++){
        if(db[i].alfa > max){
            res = db[i];
            max = db[i].alfa;
        }
    }
    return res;
}

