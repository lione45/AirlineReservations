#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
    char nome_utente[50];
    int id_prenotazione;
    char localita_partenza[50];
    char localita_arrivo[50];
    double Prezzo;
    int saldo_punti;
    struct lista *next;
}Prenotazioni;

Prenotazioni *alloca_prenotazione(char [], int, char[], char[], double, int);
Prenotazioni *inserisci_prenotazione(Prenotazioni*, char [], int, char[], char[], double, int);
Prenotazioni *dealloca_prenotazione(Prenotazioni *);
void salva_prenotazioni(Prenotazioni *);
int cancella_prenotazione(char [], int, int);
int conta_prenotazioni(int);
void modifica_saldo_punti(Prenotazioni *, int);

