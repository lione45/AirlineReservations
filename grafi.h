#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "colori.h"


typedef struct n_arc{
	char Localita_Collegata[50];
	double Prezzo;
	double Km;
	struct n_arc *next;
}Arco;

typedef struct arc{
	char Localita[50];
	int Notorieta;
	Arco *arco;
}Lista_Archi;


typedef struct node{
	int Numero_Localita;
	Lista_Archi *Connessioni;
}Grafo;

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE grafi.c
Arco *Alloca_Arco(char [],double, double);
Grafo *Crea_Grafo(Grafo *, int);
Grafo *Inizializza_Grafo(int);
Grafo *Crea_Archi(Grafo *, int);
Grafo *Inserisci_Arco(Grafo *, int, int, int);
Lista_Archi *Inizializza_Lista_Archi(Grafo *, int);
void Stampa_Grafo(Grafo *,int);
void Stampa_Arco(Arco *);
Grafo *Dealloca_Grafo(Grafo *, int );
Arco *Dealloca_Arco(Arco *);
void Salva_Grafo_Su_File(Grafo *, int);
void Salva_Arco_Su_File(Arco *, FILE *);

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE grafi2.c
Grafo *Aggiungi_Vertice(Grafo *, char []);
void pulisci_file();
Grafo *Inserisci_Arco_Dopo_Aggiunta_Vertice(Grafo *, int, int, int);
Grafo *Crea_Archi_Dopo_Aggiunta_Vertice(Grafo *, int);
Grafo *Inserisci_Archi_Per_Tutti(Grafo *, int, int, int);
int Estrai_Indice_Localita_Arrivo(Grafo *, char [], int);
Grafo *Aggiungi_Tratta(Grafo *, char [], char []);
Grafo *Elimina_Tratta(Grafo *, char [], char []);
Arco* Rimuovi_Arco(Arco*, char []);
Grafo *Cancella_Meta(Grafo *, char [], int);
Arco* Rimuovi_Tutti_Archi(Arco*);

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE controlli_grafo.c
char pulisci_buffer_localita(char []);
bool Grafo_Vuoto(Grafo *);
bool Arco_Vuoto(Arco *);
bool Verifica_Disponibilita(int, Grafo *);
bool Esiste_Vertice(Grafo *, int, char []);
bool Esiste_Volo_Diretto(Grafo *, char [], char [], int);
bool Esiste_Tratta(Grafo *, char [], char [], int);

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE leggi.c
int conta_vertici(int);
Grafo *leggi_grafo_da_file(Grafo *, int);
Grafo *Inizializza_Grafo_Per_File(int);
Lista_Archi *Inizializza_Lista_Archi_Per_File(Grafo *, int);
Grafo *Crea_Grafo_Per_File(Grafo *, int);
Grafo *Inserisci_Arco_Da_File(Grafo *, int, char [], double, double);
double trova_spesa_minima(Grafo *, char [], int , double);

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE salva_prenotazione.c
int Genera_Id_Prenotazione(char [],int );
int salva_prenotazioni_diretti(char [], int , char [], char [], double, int);
double Estrai_Prezzo_diretto(Grafo *, char [], char [], double);
int Estrai_Punti(char [], int );
void Leggi_Lista_Prenotazioni(char []);
void Saldo_Punti(char []);

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE Sconto.c
double Sconto(int *, double , double );
void Aggiorna_notorieta(Grafo *, char []);
char Gettonata(Grafo *, int, char []);
