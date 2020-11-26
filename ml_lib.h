#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ROW 7
#define COL 7

typedef enum {User, Pc} id_p;
typedef enum {Soldier, Officer} gr;

typedef struct cella pedina;

/*Definizione del tipo pedina*/
 struct cella{
    id_p id_player; /*BIANCHI = 0, NERI = 1*/
    int id_pedina;
    gr grado; /*SOLDATO = 0, UFFICIALE = 1*/
    pedina *middle;
    pedina *down;
};

int isForbiddenCell(int x,int y);

pedina ***createPedine();

void destroyPedine(pedina ***p);

pedina ***createMatrix();

void destroyMatrix(pedina ***board);

void setValuesMatrix(pedina ***board, pedina ***players);

void printPedina(pedina *p);

void printMatrix(pedina ***m);

int catchInput(int *cord);

int move(pedina ***p, int from_x, int from_y, int to_x, int to_y, id_p first, int turn); /*TODO: Aggiungere controllo giocatore legittimo*/

int distance(int from_x, int from_y, int to_x, int to_y);

void capture(pedina ***p, int from_x, int from_y, int to_x, int to_y);

int gradeCheck(pedina ***p, int from_x, int from_y, int to_y);

int isWinner(pedina ***board,int player);

int existMandatory(pedina ***p, int from_x, int from_y, int to_x, int to_y); /*Verifica se esiste una mossa (obbligatoria) diversa che da quella tentata */

/*TODO: DA IMPLEMENTARE*/

void printStatus(int turn);

