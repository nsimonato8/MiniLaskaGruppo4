/*! \file ml_main.c
*   \brief Il main di MiniLaska
*	
*	Questo file contiene il programma del gioco MiniLaska, che utilizza la libreria ml_lib
*/

#include <stdio.h>
#include <stdlib.h>
#include "ml_lib.h"



pedina **board = NULL; /*!< La scacchiera */
	

int coordinate[4]; /*!< Array contenente le coordinate di partenza e di arrivo di ogni mossa */
	

int success_move = 1; /*!< Flag che verifica la legalità di una mossa */
	

int success_input = 1; /*!< Flag che verifica la correttezza dell'input */
	

unsigned turn = 0; /*!< Contatore del turno corrente */


/*! \fn main()
* 
*	Funzione principale del gioco 
*/
int main(){

	/*Inizializzazione campo di gioco*/
	printf("Creazione campo di gioco...\n");
	
	board = createMatrix();
	
	printf("Riempimento campo di gioco...\n");
	
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
		printStatus(turn); /*Status giocatore + n°turno */
        printMatrix(board); /*Status scacchiera */
        do{
            if(!success_move || !success_input){
                inputError();
            }
            success_input = catchInput(coordinate);
            success_move = move(board,coordinate[0],coordinate[1],coordinate[2],coordinate[3],turn);
        }while(!(success_input && success_move));/*Inserimento dati e mossa*/
        turn++;
	}while(!(isWinner(board,UserOne)||isWinner(board,UserTwo))); /*Controllo esistenza vincitore*/

    if(isWinner(board,UserOne))
        victory(UserOne);
    else{
		victory(UserTwo);
	}       

	/*Liberazione memoria*/
	destroyMatrix(board);
	
	return 0;
}
