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

/*---------------------------------SEZIONE FUNZIONI AUSILIARIE---------------------------------*/

/*! \fn set_id_player(pedina *p, id_p value)
*   \brief Imposta l'id_player \a value della pedina indicata dal puntatore \a *p
*   \param p puntatore ad una pedina 
*   \param value il valore da settare
* 
*	Imposta il proprietario della pedina.
*/
void set_id_player(pedina *p, id_p value);

/*! \fn id_p get_id_player(pedina *p);
*   \brief Ritorna \a id_player dalla pedina \a *p specificata
*   \param p puntatore ad una pedina 
* 
*	Ritorna il proprietario della pedina.
*/
id_p get_id_player(pedina *p);

/*! \fn set_board_value(pedina **board, unsigned x, unsigned y, pedina *value)
*   \brief Imposta la pedina \a value nella posizione \a x , \a y nella scacchiera \a board
*   \param board matrice linearizzata della scacchiera 
*	\param x coordinata x della cella desiderata 
*	\param y coordinata y della cella desiderata
*	\param value la pedina da inserire
* 
*	Imposta il valore value nella posizione indicata nella scacchiera.
*/
void set_board_value(pedina **board, unsigned x, unsigned y, pedina *value);

/*! \fn get_board_value(pedina **board, unsigned x, unsigned y)
*   \brief Ritorna la \a pedina contenuta nella posizione \a x , \a y di \a board
*   \param board matrice linearizzata della scacchiera 
*	\param x coordinata x della cella desiderata 
*	\param y coordinata y della cella desiderata 
* 
*	Ritorna il puntatore alla pedina nella posizione x,y di board.
*/
pedina* get_board_value(pedina **board, unsigned x, unsigned y);

/*! \fn get_board_value_middle(pedina **board, unsigned x, unsigned y)
*   \brief Ritorna la \a pedina "middle" contenuta nella posizione \a x , \a y di \a board
*   \param board matrice linearizzata della scacchiera 
*	\param x coordinata x della cella desiderata 
*	\param y coordinata y della cella desiderata 
* 
*	Ritorna il valore della pedina middle nella posizione x,y di board.
*/
pedina* get_board_value_middle(pedina **board, unsigned x, unsigned y);

/*! \fn get_board_value_down(pedina **board, unsigned x, unsigned y)
*   \brief Ritorna la \a pedina "down" contenuta nella posizione \a x, \a y di \a board
*   \param board matrice linearizzata della scacchiera 
*	\param x coordinata x della cella desiderata 
*	\param y coordinata y della cella desiderata
  
*	Ritorna il valore della pedina down nella posizione indicata nella scacchiera.
*/
pedina* get_board_value_down(pedina **board, unsigned x, unsigned y);

/*! \fn set_grade(pedina *p,gr value)
*   \brief Imposta il grado \a value della pedina indicata dal puntatore \a p
*   \param p puntatore ad una pedina 
*   \param value il valore da settare
* 
*   Imposta il grado di una pedina.
*/
void set_grade(pedina *p,gr value);

/*! \fn get_grade(pedina *p)
*   \brief Ritorna il grado \a value della pedina indicata dal puntatore \a p
*   \param p puntatore ad una pedina 
*
*	Ritorna il grado di una pedina.
*/
gr get_grade(pedina *p);


/*---------------------------------SEZIONE FUNZIONI GESTIONE MEMORIA---------------------------------*/

/*! \fn **createMatrix()
*   \brief Funzione che crea la matrice della scacchiera
* 
* 	Ritorna un puntatore di tipo \a pedina** ad una matrice bidimensionale di puntatori a pedina linearizzata.
*/
pedina **createMatrix();

/*! \fn destroyMatrix(pedina **p)
*   \brief Distrugge la matrice della scacchiera
*	\param p matrice linearizzata della scacchiera
* 
*	Funzione che dealloca la memoria della matrice della scacchiera.
*/
void destroyMatrix(pedina **p);

/*! \fn fillBoard(pedina **p)
*   \brief Riempie la scacchiera con le pedine
*	\param p matrice linearizzata della scacchiera
* 
*	Riempie la scacchiera con le pedine. Il giocatore 1 ( \a UserOne) sarà posizionato nella parte bassa della scacchiera.
*/
void fillBoard(pedina **p);

/*---------------------------------SEZIONE FUNZIONI INPUT---------------------------------*/

/*! \fn catchInput(int *cord)
*   \brief Legge l'input da tastiera
*	\param cord array contenente le coordinate di partenza e destinazione della pedina
* 
* 	Legge l'input dall'utente e traduce le coordinate in int, che vengono inseriti in un array apposito.
*/
int catchInput(int *cord);

/*---------------------------------SEZIONE FUNZIONI OUTPUT---------------------------------*/

/*! \fn printPedina(pedina *p)
*   \brief Stampa una lettera rappresentante la pedina
*	\param p puntatore alla pedina
* 
*	Stampa un carattere ASCII identificativo del contenuto della casella p:
* 	<ul>
* 		<li>b/n se il giocatore è bianco o nero ( \a UserOne / \a UserTwo).</li>
* 		<li>maiuscola/minuscola se la pedina è ufficiale/soldato.</li>
* 	</ul>
*/
void printPedina(pedina *p);

/*! \fn printMatrix(pedina **p)
*   \brief Stampa la scacchiera
*	\param p matrice linearizzata della scacchiera
* 
*	Funzione che stampa la scacchiera con una cornice che definisce le coordinate.
*/
void printMatrix(pedina **p);

/*! \fn printStatus(unsigned turn)
*   \brief Stampa lo stato del gioco
*	\param turn numero dei turni passati
* 
*	Stampa lo status del gioco (numero del turno e giocatore che deve muovere).
*/
void printStatus(unsigned turn);

/*! \fn printRules()
*	\brief Stampa le regole del gioco
* 
*	Stampa le regole del gioco.
*/
void printRules();

/*! \fn victory(id_p winner)
*	\brief Schermata di vittoria
* 
*	Stampa il vincitore del gioco.
*/
void victory(id_p winner);

/*! \fn inputError()
*	\brief Schermata di errore di input
* 
*	Fornisce informazioni in caso di inserimento dati scorretto.
*/
void inputError();

/*---------------------------------SEZIONE FUNZIONI LOGICHE DI GIOCO---------------------------------*/

/*! \fn isWinner(pedina **p, id_p player)
*   \brief Verifica che il giocatore \a player abbia vinto
*   \param p matrice linearizzata della scacchiera
*   \param idPlayer giocatore selezionato 
* 
*	Verifica che il giocatore \a idPlayer abbia vinto.
*	Restituisce 1 se idPlayer ha vinto, altrimenti 0.
*/
int isWinner(pedina **p, id_p player);

/*! \fn isForbiddenCell(unsigned x,unsigned y)
*   \brief Verifica che la cella sia accessibile
*   \param x coordinata x della cella
*   \param y coordinata y della cella
* 
*	Restituisce 1 se la cella non è accessibile (si possono usare solo le celle bianche della scacchiera), altrimenti 0.
*/
int isForbiddenCell(unsigned x,unsigned y);

/*! \fn move(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, id_p first, unsigned turn)
*   \brief Verifica che la mossa selezionata sia legale e la esegue
*   \param p matrice linearizzata della scacchiera 
*   \param from_x coordinata x della cella di partenza
*   \param from_y coordinata y della cella di partenza
*   \param to_x coordinata x della cella di destinazione
*   \param to_y coordinata y della cella di destinazione
* 	\param first giocatore di partenza
*   \param turn numero del turno corrente
* 
* 	Restituisce 1 se la mossa è stata fatta, 0 se non è stato possibile.
*
* 	Le coordinate inserite sono corrette in fase di input (sono all'interno della scacchiera e non sono caselle proibite).
* 	Verifica che la distanza ed il grado siano compatibili con la mossa.
*/
int move(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, unsigned turn); /*TODO: Aggiungere controllo giocatore legittimo*/

/*! \fn distance(int from_x, int from_y, int to_x, int to_y)
*   \brief Restituisce un codice che descrive la lunghezza della mossa
*   \param board matrice linearizzata della scacchiera 
*   \param from_x coordinata x della cella di partenza
*   \param from_y coordinata y della cella di partenza
*   \param to_x coordinata x della cella di destinazione
*   \param to_y coordinata y della cella di destinazione
* 
*	Restituisce la distanza in modulo tra due punti nella matrice:
*	Se è maggiore di 2, uguale a 0, o la destinazione è in una casella non accessibile restituisce il codice errore -1.
*
*	Le coordinate inserite sono corrette (la destinazione non è una casella proibita).
*/
int distance(int from_x, int from_y, int to_x, int to_y);

/*! \fn capture(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y)
*   \brief Esegue la cattura delle pedine 
*   \param from_x coordinata x della cella di partenza
*   \param from_y coordinata y della cella di partenza
*   \param to_x coordinata x della cella di destinazione
*   \param to_y coordinata y della cella di destinazione
* 
* 	Questa funzione si occupa di catturare le pedine indicate.
* 	Si assume la correttezza delle coordinate inserite, la legalità della mossa è verificata nella funzione move().
*/
void capture(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y);

/*! \fn gradeCheck(pedina **board, unsigned from_x, unsigned from_y, unsigned to_y)
*   \brief Verifica che la mossa selezionata sia compatibile con il grado della pedina
*   \param board matrice linearizzata della scacchiera 
*   \param from_x coordinata x della cella di partenza
*   \param from_y coordinata y della cella di partenza
*   \param to_y coordinata y della cella di destinazione
* 
*	Verifica il grado della pedina mossa:
*	restituisce 1 se la mossa è consentita, 0 se non è consentita.
*/
int gradeCheck(pedina **board, unsigned from_x, unsigned from_y, unsigned to_y);

/*! \fn existMandatory(pedina **p, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y)
*   \brief Controlla la presenza di mosse obbligatorie
*   \param board matrice linearizzata della scacchiera 
*   \param from_x coordinata x della cella di partenza
*   \param from_y coordinata y della cella di partenza
*   \param to_x coordinata x della cella di destinazione
*   \param to_y coordinata y della cella di destinazione
* 
*	Verifica se, nel caso di non cattura, esiste una cattura obbligatoria da fare.
*	Restituisce 1 se esiste una mossa obbligatoria non tentata, altrimenti 0.
*/
int existMandatory(pedina **board, unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y); /*Verifica se esiste una mossa (obbligatoria) diversa che da quella tentata */

