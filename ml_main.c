#include<stdio.h>
#include "ml_lib.h"

int main(){
	
	pedina ***board, ***players;

	/*Inizializzazione campo di gioco*/
	board = createMatrix();
	players = createPedine();
	
	setValuesMatrix(board,players);

	/*Gioco*/
	printMatrix(board);


	/*Liberazione memoria*/
	destroyMatrix(board);
	destroyPedine(players);
	
	return 0;
}
