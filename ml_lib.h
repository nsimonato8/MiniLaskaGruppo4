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

int move(pedina ***p, int from_x, int from_y, int to_x, int to_y); /*TODO: Aggiungere controllo giocatore legittimo, aggiungere controllo mossa obbligatoria*/

int distance(int from_x, int from_y, int to_x, int to_y);

void capture(pedina ***p, int from_x, int from_y, int to_x, int to_y);

int gradeCheck(pedina ***p, int from_x, int from_y, int to_y);

/*TODO: DA IMPLEMENTARE*/

int isWinner(pedina ***board,int player);

int isMandatory(pedina ***p, int from_x, int from_y, int to_x, int to_y); /*Verifica se una mossa è obbligatoria*/

int printStatus(int turn);

