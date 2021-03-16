/*! \file ml_main.c
*   \brief Il main di MiniLaska
*
*    Questo file contiene il programma del gioco MiniLaska, che utilizza la libreria ml_lib
*/

#include <stdio.h>
#include <stdlib.h>
#include "Autoplay.h"



pedina **board = NULL; /*!< La scacchiera */

t_node database_mosse[NUMERO_PEDINE]; /*!< La situazione*/

int coordinate[4]; /*!< Array contenente le coordinate di partenza e di arrivo di ogni mossa */


int success_move = 1; /*!< Flag che verifica la legalità di una mossa */


int success_input = 1; /*!< Flag che verifica la correttezza dell'input */


int turn = 0; /*!< Contatore del turno corrente */

int mode;  /*!< Modalità di gioco*/

point from,to; /*!< Segnaposto dei punti di partenza e arrivo di ogni mossa */


/*! \fn main()
*
*    Funzione principale del gioco
*/
int main(){

    /*Inizializzazione campo di gioco*/
    printf("Creazione campo di gioco...\n");

    board = createMatrix();

    printf("Riempimento campo di gioco...\n");

    fillBoard(board);
    
    create_db(database_mosse);
    
    fill_db(database_mosse, board);

    printRules();

    /*TODO: Menu
     * 1) istruzioni --> printf
     * 2) gioca --> selezione modalità --> gioco
     * 3) credits --> printf
     * 4) exit
    */
    
    scanf("%d",&mode);
    
    
    do{
        if(mode == 1){
            /*1vs1*/
            do{
                do{

                    printStatus(turn); /*Status giocatore + n°turno */
                    printMatrix(board); /*Status scacchiera */

                    if(!success_move || !success_input){
                        inputError();
                    }
                    
                    success_input = catchInput(coordinate/*,board*/);
                    
                    from.x = coordinate[1];
                    from.y = coordinate[0];
                    to.x = coordinate[3];
                    to.y = coordinate[2];
                    
                    success_move = my_move(board,from,to,turn);
                }while(!(success_input && success_move));/*Inserimento dati e mossa*/
                turn++;
            }while(!(isWinner(board,UserOne)||isWinner(board,UserTwo))); /*Controllo esistenza vincitore*/

            if(isWinner(board,UserOne))
                victory(UserOne);
            else{
                victory(UserTwo);
            }
            
        }
        else if(mode == 2){
            /*1vsCPU*/ /*TODO: ADATTARE AD AUTOPLAY*/
            do{
                do{

                    printStatus(turn); /*Status giocatore + n°turno */
                    printMatrix(board); /*Status scacchiera */

                    if(!success_move || !success_input){
                        inputError();
                    }
                    
                    if(turn%2){
                       /* printf("\n INSIDE TURNO 2 IF\n");
                        printf("\n Prima\n");
                        print_coord(coordinate);*/
                        
                        /*Input autoplay*/catchInput_Autoplay(board, coordinate, database_mosse, turn);
                       
                        /* printf("\n Dopo");
                        print_coord(coordinate);
                        print_datab(database_mosse);
                        printf("\nAuto main: from.x %d, from.y %d, to.x %d, to.y %d\n",from.x,from.y,to.x,to.y );*/
                    }
                    else
                        success_input = catchInput(coordinate/*,board*/);
                    
                    
                    from.x = coordinate[1];
                    from.y = coordinate[0];
                    to.x = coordinate[3];
                    to.y = coordinate[2];
                    
                    
                    success_move = my_move(board,from,to,turn);
                }while(!(success_input && success_move));/*Inserimento dati e mossa*/
                turn++;
            }while(!(isWinner(board,UserOne)||isWinner(board,UserTwo))); /*Controllo esistenza vincitore*/

            if(isWinner(board,UserOne))
                victory(UserOne);
            else{
                victory(UserTwo);
            }
            
            
        }else if(mode == 3){
            /*Credits*/
            exit(0);
        }
        else{
            /*Exits*/
            printf("Esco...\n");
            exit(0);
        }
        
    }while(mode != 4);
    

    /*Liberazione memoria*/
    destroyMatrix(board);

    return 0;
}
