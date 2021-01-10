#include <stdio.h>
#include<stdlib.h>
#include "ml_lib.h"

int main(){

    pedina **board = NULL;
    int coordinate[4]; /*Contiene le coordinate di partenza e arrivo di ogni mossa*/
    int success_move = 1, success_input = 1; /*Verifica che la mossa sia possibile*/
    unsigned turn = 0;

    /*Inizializzazione campo di gioco*/
    printf("\nCreazione campo di gioco...\n\n");

    board = createMatrix();

    printf("Riempimento campo di gioco...\n\n\n");

    fillBoard(board);

    printRules();

    /*TODO: Menu
     * 1) istruzioni --> printf
     * 2) gioca --> selezione modalità --> gioco
     * 3) credits --> printf
     * 4) exit
    */

    /*Gioco 1v1*/
    do{
        do{
            printMatrix(board); /*Status scacchiera */
            printStatus(turn); /*Status giocatore + n°turno */

            if(!success_move || !success_input){
                inputError();
            }
            success_input = catchInput(coordinate, board);
            printf("\nsuccess input %d\n",success_input);
            success_move = move(board,coordinate[0],coordinate[1],coordinate[2],coordinate[3],turn);
            printf("\nsuccess move %d\n", success_move);
        }while(!(success_input && success_move));/*Inserimento dati e mossa*/
        turn++;
    }while((isWinner(board,UserOne)||(isWinner(board,UserTwo)))); /*Controllo esistenza vincitore*/

    printf("\nsecondo while esce\n");

    if(isWinner(board,UserOne))
        victory(UserOne);
    else{
        victory(UserTwo);
    }

    /*Liberazione memoria*/
    destroyMatrix(board);

    return 0;
}
