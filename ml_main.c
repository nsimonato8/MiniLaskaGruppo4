#include<stdio.h>
#include "ml_lib.h"

int main(){
	
	pedina ***board, ***players;
	int coordinate[4]; /*Contiene le coordinate di partenza e arrivo di ogni mossa*/
	int success_move = 1, success_input = 1, turn = 0; /*Verifica che la mossa sia possibile*/

	/*Inizializzazione campo di gioco*/
	board = createMatrix();
	players = createPedine();
	
	setValuesMatrix(board,players);



	/*TODO: Menu
	 * 1) istruzioni --> printf
	 * 2) gioca --> selezione modalità --> gioco
	 * 3) credits --> printf
	 * 4) exit
	*/

    /*Gioco 1v1*/
	do{
        printMatrix(board); /*Status scacchiera */
        printStatus(turn); /*Status giocatore + n°turno */
        do{
            if(!success_move || !success_input){
                /*TODO: Schermata di errore di input*/
            }
            success_input = catchInput(coordinate);
            success_move = move(board,coordinate[0],coordinate[1],coordinate[2],coordinate[3]);
        }while(!(success_input && success_move));/*Inserimento dati e mossa*/
        turn++;
	}while(!(isWinner(board,0)||isWinner(board,1))); /*Controllo esistenza vincitore*/

        /*TODO: Schermata vittoria*/

	/*Liberazione memoria*/
	destroyMatrix(board);
	destroyPedine(players);
	
	return 0;
}
