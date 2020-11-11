#include<stdio.h>
#include "ml_lib.h"

int main(){
	
	pedina ***board, ***players;
	int coordinate[4];

	/*Inizializzazione campo di gioco*/
	board = createMatrix();
	players = createPedine();
	
	setValuesMatrix(board,players);

	/*Gioco*/

	do{
        printMatrix(board); /*Status / esito mossa precedente*/
        do{
            catchInput(coordinate);
        }while(move())/*Inserimento dati e mossa*/

	}while(!(isWinner(board,0)||isWinner(board,1))); /*Controllo esistenza vincitore*/

    /*TODO: Schermata vittoria*/

	/*Liberazione memoria*/
	destroyMatrix(board);
	destroyPedine(players);
	
	return 0;
}
