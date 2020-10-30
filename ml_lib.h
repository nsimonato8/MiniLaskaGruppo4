#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ROW 7
#define COL 7

/*Definizione del tipo pedina*/
struct cella{
    int id_player; /*BIANCHI = 0, NERI = 1*/
    int id_pedina;
    int grado;
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
