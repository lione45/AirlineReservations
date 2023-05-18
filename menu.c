#include "menu.h"

int menu_iniziale(int a){
	printf("============");
	SetColor(2);
	printf(" Benvenuto Nella Schermata Di Login. ");
    SetColor(0);
	printf("============\n");
	printf("=============================================================\n");
	printf(" ____________________________________________________________\n|");
	SetColor(6);
	printf("Con Quale Profilo Effettuare Il Login:");
	SetColor(0);
	printf("\t\t\t     |\n");
    printf("|____________________________________________________________|\n|\t\t\t\t\t\t\t     |\n|");
    SetColor(9);
	printf("1)Utente;");
	SetColor(0);
	printf("\t\t\t\t\t\t     |\n|");
	SetColor(8);
	printf("2)Admin;");
	SetColor(0);
	printf("\t\t\t\t\t\t     |\n|");
    SetColor(12);
	printf("3)Esci;");
	SetColor(0);
	printf("\t\t\t\t\t\t     |");
	printf("\n|____________________________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&a);
	printf("\n");
	return a;
}


int primo_menu_utente(int d){
	printf("=======");
	SetColor(9);
	printf(" Benvenuto Utente. ");
	SetColor(0);
	printf("=======\n");
	printf("=================================\n");
	printf(" __________________________________________\n|");
	SetColor(6);
	printf("Sei Nuovo O Sei Gia' Cliente:");
	SetColor(0);
	printf("\t\t   |");
	printf("\n|__________________________________________|\n|\t\t\t\t\t   |\n|");
	SetColor(9);
	printf("1)Accedi;");
	SetColor(0);
	printf("\t\t\t\t   |\n|");
	SetColor(13);
	printf("2)Registrati;");
	SetColor(0);
	printf("\t\t\t\t   |\n|");
	SetColor(12);
	printf("3)Torna Indietro;");
	SetColor(0);
	printf("\t\t\t   |\n");
	printf("|__________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&d);
	return d;
}

int primo_menu_admin(int g){
    printf("\n\n=======");
	SetColor(8);
	printf(" Benvenuto Nuovo Admin. ");
	SetColor(0);
	printf("=======\n");
	printf("=====================================\n");
	printf(" __________________________________________\n|");
	SetColor(6);
	printf("Cosa Vuoi Fare?");
	SetColor(0);
	printf("\t\t\t   |");
	printf("\n|__________________________________________|\n|\t\t\t\t\t   |\n|");
	SetColor(13);
	printf("1)Registrati;");
	SetColor(0);
	printf("\t\t\t\t   |\n|");
	SetColor(12);
	printf("2)Logout;");
	SetColor(0);
	printf("\t\t\t\t   |\n");
	printf("|__________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&g);
	return g;
}

int menu_utente(int d, char nome_ut[]){
	printf("=======");
	SetColor(9);
	printf(" Benvenuto %s. ", nome_ut);
	SetColor(0);
	printf("=======\n");
	printf("=================================\n");
	printf(" __________________________________________\n|");
	SetColor(6);
	printf("Cosa Vuoi Fare Oggi:");
	SetColor(0);
	printf("\t\t\t   |");
	printf("\n|__________________________________________|\n|\t\t\t\t\t   |\n|");
	SetColor(9);
	printf("1)Prenota Volo;");
	SetColor(0);
	printf("\t\t\t   |\n|");
	SetColor(10);
	printf("2)Lista Prenotazioni;");
	SetColor(0);
	printf("\t\t\t   |\n|");
    SetColor(3);
	printf("3)Saldo Punti;");
	SetColor(0);
	printf("\t\t\t\t   |\n|");
	SetColor(5);
    printf("4)Cancella Prenotazione;");
    SetColor(0);
	printf("\t\t   |\n|");
	SetColor(12);
	printf("5)Logout;");
	SetColor(0);
	printf("\t\t\t\t   |\n");
	printf("|__________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&d);
	return d;
}

int menu_admin(int d, char nome_ut[]){
	printf("=======");
	SetColor(9);
	printf(" Benvenuto %s. ", nome_ut);
	SetColor(0);
	printf("=======\n");
	printf("=================================\n");
	printf(" __________________________________________\n|");
	SetColor(6);
	printf("Cosa Vuoi Fare Oggi:");
	SetColor(0);
	printf("\t\t\t   |");
	printf("\n|__________________________________________|\n|\t\t\t\t\t   |\n|");
	SetColor(9);
	printf("1)Aggiungi;");
	SetColor(0);
	printf("\t\t\t\t   |\n|");
	SetColor(5);
	printf("2)Elimina;");
	SetColor(0);
	printf("\t\t\t\t   |\n|");
	SetColor(8);
	printf("3)Stampa Tratte Disponibili;");
	SetColor(0);
	printf("\t\t   |\n|");
	SetColor(12);
	printf("4)Logout;");
	SetColor(0);
	printf("\t\t\t\t   |\n");
	printf("|__________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&d);
	return d;
}
