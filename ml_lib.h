#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*---------------------------------SEZIONE DEFINIZIONI---------------------------------*/

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

/*---------------------------------SEZIONE FUNZIONI AUSILIARIE---------------------------------*/

/* Imposta l'id_player della pedina indicata dal puntatore*/
void set_id_player(pedina *p, id_p value);

/* Ritorna il p->id_player della pedina specificata */
id_p get_id_player(pedina *p);

/* Imposta il valore value nella posizione indicata nella scacchiera*/
void set_board_value(pedina **board, unsigned x, unsigned y, pedina *value);

/* Ritorna il valore nella posizione indicata nella scacchiera*/
pedina* get_board_value(pedina **board, unsigned x, unsigned y);

/* Ritorna il valore della pedina middle nella posizione indicata nella scacchiera*/
pedina* get_board_value_middle(pedina **board, unsigned x, unsigned y);

/* Ritorna il valore della pedina down nella posizione indicata nella scacchiera*/
pedina* get_board_value_down(pedina **board, unsigned x, unsigned y);

/* Imposta il grado di una pedina*/
void set_grade(pedina *p,gr value);

/* Ritorna il grado di una pedina*/
gr get_grade(pedina *p);

/*---------------------------------SEZIONE FUNZIONI LOGICHE DI GIOCO---------------------------------*/

/* Verifica che il giocatore idPlayer abbia vinto
 * Restituisce 1 se idPlayer ha vinto, altrimenti 0
*/
int isWinner(pedina **p, id_p player);

/*
 * Restituisce 1 se la cella non è accessibile (si possono usare solo le celle bianche della scacchiera), altirmenti 0
*/
int isForbiddenCell(unsigned x,unsigned y);

/*---------------------------------SEZIONE FUNZIONI GESTIONE MEMORIA---------------------------------*/

/*
 * Funzione che crea la matrice della scacchiera
*/
pedina **createMatrix();

/*
 * Funzione che distrugge la matrice della scacchiera
*/
void destroyMatrix(pedina **p);

/*
 * Riempie la scacchiera
*/
void fillBoard(pedina **p);

/*---------------------------------SEZIONE FUNZIONI OUTPUT---------------------------------*/

/*
 * Stampa un carattere ASCII identificativo del contenuto della casella p
*/
void printPedina(pedina *p);

/*
 * Funzione che stampa la scacchiera in base al posizionamento delle pedine.
*/
void printMatrix(pedina **p);

/*
 * Stampa lo status del gioco (numero del turno, e giocatore che deve muovere)
 */
void printStatus(unsigned turn);

/*
 * Stampa le regole del gioco
*/
void printRules();

/*
 * Stampa il vincitore del gioco
*/
void victory(id_p winner);

/*
 * Fornisce informazioni in caso di inserimento dati scorretto
*/
void inputError();

/*---------------------------------SEZIONE FUNZIONI MOVE---------------------------------*/

/*
 * Legge l'input dall'utente e traduce le coordinate in int, che vengono inseriti in un array apposito
*/
int catchInput(int *cord);

/*
 * Restituisce 1 se la mossa è stata fatta, 0 se non è stato possibile
 *
 * Le coordinate inserite sono corrette in fase di input (sono all'interno della scacchiera e non sono caselle proibite)
 * Verifica che la distanza ed il grado siano compatibili con la mossa
*/
int move(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, id_p first, unsigned turn); /*TODO: Aggiungere controllo giocatore legittimo*/

/*
 * Restituisce la distanza in modulo tra due punti nella matrice:
 * Se è maggiore di 2, uguale a 0, o la destinazione è in una casella non accessibile restituisce il codice errore -1
 *
 * Le coordinate inserite sono corrette (la destinazione non è una casella proibita)
*/
int distance(int from_x, int from_y, int to_x, int to_y);

/*
 * Questa funzione si occupa di catturare le pedine indicate.
 * Si assume la correttezza delle coordinate inserite, la legalità della mossa è verificata nella funzione move(...).
*/
void capture(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y);

/*
 * Verifica il grado della pedina mossa:
 * restituisce 1 se la mossa è consentita, 0 se non è consentita
*/
int gradeCheck(pedina **p, unsigned from_x, unsigned from_y, unsigned to_y);

/*
 * Verifica se, nel caso di non cattura, esiste una cattur obbligatoria da fare
 * Restituisce 1 se esiste una mossa obbligatoria non tentata, altrimenti 0
 */
int existMandatory(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y); /*Verifica se esiste una mossa (obbligatoria) diversa che da quella tentata */


/*TODO: DA IMPLEMENTARE*/

