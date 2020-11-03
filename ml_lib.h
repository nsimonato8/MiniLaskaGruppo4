#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ROW 7
#define COL 7

/*Definizione del tipo pedina*/
struct cella{
    int id_player; /*BIANCHI = 0, NERI = 1*/
    int id_pedina; /*UTENTE = 0, PC = 1*/
    int grado; /*SOLDATO = 0, UFFICIALE = 1*/
    pedina *middle;
    pedina *down;
};

typedef struct cella pedina;

pedina **createPedine();

void destroyPedine(pedina **p);

pedina **createMatrix(const pedina r, const pedina c);

void destroyMatrix(pedina **board)

void setValuesMatrix(pedina **board, pedina **players);

void printPedina(pedina *p);

void printMatrix(int **m);

int move(pedina **p, int from_x, int from_y, int to_x, int to_y);

int distance(int from_x, int from_y, int to_x, int to_y);

void capture(pedina **p, int from_x, int from_y, int to_x, int to_y);

int gradeCheck(pedina **p, int from_y, int to_y);
