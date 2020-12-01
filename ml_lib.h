#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ROW 7
#define COL 7

typedef enum {UserOne, UserTwo} id_p;
typedef enum {Soldier, Officer} gr;

typedef struct cella pedina;

/*Definizione del tipo pedina*/
 struct cella{
    id_p id_player; /*BIANCHI = 0, NERI = 1*/
    gr grado; /*SOLDATO = 0, UFFICIALE = 1*/
    pedina *middle;
    pedina *down;
};
 
 /*
  * ASSUNZIONI LOGICHE FONDAMENTALI:
  *     L'utente muove sempre per primo
  *     Se il giocatore ha la possibilità di catturare una pedina, è obbligato a farlo
  * */

int isForbiddenCell(unsigned x,unsigned y);

pedina*(*)[COL] createMatrix();

void destroyMatrix(pedina* p[ROW][COL]);

void fillBoard(pedina* p[ROW][COL]);

void printPedina(pedina *p);

void printMatrix(pedina* p[ROW][COL]);

int catchInput(int *cord);

int move(pedina* p[ROW][COL], unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, id_p first, unsigned turn); /*TODO: Aggiungere controllo giocatore legittimo*/

int distance(unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y);

void capture(pedina* p[ROW][COL], unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y);

int gradeCheck(pedina* p[ROW][COL], unsigned from_x, unsigned from_y, unsigned to_y);

int isWinner(pedina* p[ROW][COL], id_p player);

int existMandatory(pedina* p[ROW][COL], unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y); /*Verifica se esiste una mossa (obbligatoria) diversa che da quella tentata */

void printStatus(unsigned turn);

void printRules();

void victory(id_p winner);

void inputError();

/*TODO: DA IMPLEMENTARE*/

