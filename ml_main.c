#include<stdio.h>
#include "ml_lib.h"

int main(){
	
	pedina ***board, ***players;
	int coordinate[4]; /*Contiene le coordinate di partenza e arrivo di ogni mossa*/
	int success_move = 1, success_input = 1; /*Verifica che la mossa sia possibile*/
	unsigned turn = 0;
	id_p first = UserOne;

	/*Inizializzazione campo di gioco*/
	board = createMatrix();
	players = createPedine();
	
	setValuesMatrix(board,players);

    printRules();

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
                inputError();
            }
            success_input = catchInput(coordinate);
            success_move = move(board,coordinate[0],coordinate[1],coordinate[2],coordinate[3],first,turn);
        }while(!(success_input && success_move));/*Inserimento dati e mossa*/
        turn++;
	}while(!(isWinner(board,UserOne)||isWinner(board,UserTwo))); /*Controllo esistenza vincitore*/

    if(isWinner(board,UserOne))
        victory(UserOne);
    else
        victory(UserTwo);

	/*Liberazione memoria*/
	destroyMatrix(board);
	destroyPedine(players);
	
	return 0;
}
