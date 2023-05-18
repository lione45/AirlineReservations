#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grafi.h"


typedef struct nodo{
    char Localita[50];
    double prezzo;
    double Km;
	char Localita_Precedente[50];
    struct nodo* next;
}Priority_Queue;


///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE Priority_Queue.c
Priority_Queue *Alloca_Queue(char [], double, char[], double);
void Dealloca_Priority_Queue(Priority_Queue **);
Priority_Queue *Push(Priority_Queue **, char [], double, char [], double);
bool Queue_Vuota(Priority_Queue **);
char Valore_Testa_Localita(Priority_Queue **, char []);
Priority_Queue *Ini_Coda_Priorita(Grafo *, Priority_Queue *, char [], int);
char Valore_Testa_Localita_Precedente(Priority_Queue **, char []);
double Valore_Testa_Priorita(Priority_Queue **, double);
Priority_Queue *Pop(Priority_Queue **, char []);
int salva_prenotazioni_economiche(char [], int , Priority_Queue **, double, int);

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE Dijkstra.c
Priority_Queue *Dijkstra(Grafo *, char [], char []);
Arco *Estrai_Arco(Grafo *, char [] , int);
char Estrai_Localita(Priority_Queue **, char [], char []);
char Estrai_Localita_Precedente(Priority_Queue **, char [], char []);
double Estrai_Priorita(Priority_Queue **, char [], double);
bool Verifica_Coda_Terminati(Priority_Queue **,char []);
Priority_Queue *Estrai_Localita_Arrivo(Priority_Queue **, Priority_Queue *, char []);
void Stampa_Queue(Priority_Queue **, int);
char Estrai_Percorso_Minimo(Priority_Queue **, Priority_Queue **, char []);
int Conta_Queue(Priority_Queue **, int);

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE Dijkstra_km.c
Priority_Queue *Dijkstra_Km(Grafo *, char [], char []);
Priority_Queue *Ini_Coda_Priorita_Km(Grafo *, Priority_Queue *, char [], int);
Priority_Queue *Push_km(Priority_Queue **, char [], double, char [], double);
double Valore_Testa_Priorita_km(Priority_Queue **, double );
double Estrai_Priorita_km(Priority_Queue **, char [], double);
Priority_Queue *Estrai_Localita_Arrivo_km(Priority_Queue **, Priority_Queue *, char []);
char Estrai_Percorso_Minimo_km(Priority_Queue **, Priority_Queue **, char []);

///PER L'IMPLEMNTAZIONE DELLE SEGUENTI FUNZIONI CONTROLLARE IL FILE Dijkstra_solo_parternza.c
char Estrai_Localita_Prezzo_Piu_Basso(Priority_Queue **, char [], double);
Priority_Queue *Dijkstra_Partenza_Economica(Grafo *, char [], char [], double);
Priority_Queue *Estrai_Localita_Arrivo_Prezzo_Minore(Priority_Queue **, Priority_Queue *, char []);
char Estrai_Percorso_Minimo_Prezzo(Priority_Queue **, Priority_Queue **, char []);
