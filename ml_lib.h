/*! \file ml_lib.h
    \brief Header della libreria ml_lib
	 *
    Questo file contiene le definizioni di tutte le strutture e delle funzioni che compongono la libreria ml_lib
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*---------------------------------SEZIONE DEFINIZIONI---------------------------------*/

#define ROW 7
#define COL 7

/*! Definizione dei due giocatori esistenti */
typedef enum {UserOne, UserTwo} id_p;

/*! Definizione dei due possibili gradi della pedina */
typedef enum {Soldier, Officer} gr;

/*! Rinominazione del tipo struct cella in pedina, per praticità di scrittura */
typedef struct cella pedina;

/*!Definizione del tipo pedina*/
struct cella{
    id_p id_player; /*!< ID del giocatore proprietario della pedina */  /*BIANCHI = 0, NERI = 1*/
    gr grado; /*!< Grado della pedina *//*SOLDATO = 0, UFFICIALE = 1*/
    pedina *middle; /*!< Puntatore alla pedina di mezzo della colonna */
    pedina *down; /*!< Puntatore alla pedina in fondo alla colonna */
};

/*
* ASSUNZIONI LOGICHE FONDAMENTALI:
*     L'utente muove sempre per primo
*     Se il giocatore ha la possibilità di catturare una pedina, è obbligato a farlo
*/

int isForbiddenCell(unsigned x,unsigned y);

pedina **createMatrix();

void destroyMatrix(pedina **board);

void fillBoard(pedina **board);

void printPedina(pedina *p);

void printMatrix(pedina **board);

int catchInput(int *cord, pedina **board);

int move(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, unsigned turn); /*TODO: Aggiungere controllo giocatore legittimo*/

int distance(unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y);

void capture(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y);

int gradeCheck(pedina **board, unsigned from_x, unsigned from_y, unsigned to_y);

int isWinner(pedina **board, id_p player);

int existMandatory(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y); /*Verifica se esiste una mossa (obbligatoria) diversa che da quella tentata */

void printStatus(unsigned turn);

void printRules();

void victory(id_p winner);

void inputError();

/*TODO: DA IMPLEMENTARE*/
