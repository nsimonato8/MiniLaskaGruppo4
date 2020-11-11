#include<stdio.h>
#include "ml_lib.h"

int main(){
	
	pedina ***board, ***players;

	/*Inizializzazione campo di gioco*/
	board = createMatrix();
	players = createPedine();
	
	setValuesMatrix(board,players);

	/*Gioco*/
<<<<<<< Updated upstream
	printMatrix(board);
	do{

	}while(!(isWinner(board,0)||isWinner(board,1)));
=======
	do{
        printMatrix(board); /*Status / esito mossa precedente*/
        do{
            catchInput();
        }while(move())/*Inserimento dati e mossa*/
>>>>>>> Stashed changes

	}while(!(isWinner(board,0)||isWinner(board,1))); /*Controllo esistenza vincitore*/

    /*TODO: Schermata vittoria*/

	/*Liberazione memoria*/
	destroyMatrix(board);
	destroyPedine(players);
	
	return 0;
}
