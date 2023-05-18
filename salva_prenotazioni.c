#include "Priority_Queue.h"


int Genera_Id_Prenotazione(char nomeutente[],int id){
    srand(time(NULL));
    FILE *fp = fopen("lista_prenotazioni.txt","r");
    char buffer[500], *res, nome[30], *n, *p;
    int prenotazione, controllo;
    if(fp != NULL){
        while(!feof(fp)){
                prenotazione = rand()%1000+1;
                res = fgets(buffer, 500, fp);
                if(res != NULL){
                    n = strtok(res, ",");
                    strcpy(nome,n);
                    p = strtok(NULL, ",");
                    controllo = atoi(p);
                    if(strcmp(nomeutente,nome) == 0 && prenotazione != controllo){
                        id = prenotazione;
                        fclose(fp);
                        return id;
                    }
                }
            }
    }else{
        srand(time(NULL));
        id = rand()%1000+1;
        fclose(fp);
        return id;
    }
}

int salva_prenotazioni_diretti(char nomeutente[], int id_prenotazione, char localita_partenza[], char localita_arrivo[], double prezzo, int saldo_punti){
    id_prenotazione = Genera_Id_Prenotazione(nomeutente,id_prenotazione);
    FILE *fp = fopen("lista_prenotazioni.txt","a");
    if(fp != NULL){
        fprintf(fp, "%s,%d,%s,%s,%lf,%d;\n",nomeutente, id_prenotazione, localita_partenza, localita_arrivo, prezzo, saldo_punti);
   }
   fclose(fp);
   return id_prenotazione;
}

double Estrai_Prezzo_diretto(Grafo *b, char localita_partenza[], char localita_arrivo[], double prezzo){
    int coordianta_partenza = 0;
    coordianta_partenza = Estrai_Indice_Localita_Arrivo(b, localita_partenza,coordianta_partenza);
    Arco *tmp = b->Connessioni[coordianta_partenza].arco;
    while(!(Arco_Vuoto(tmp))){
        if(strcmp(tmp->Localita_Collegata,localita_arrivo) == 0){
            prezzo = tmp->Prezzo;
            return prezzo;
        }
        tmp = tmp->next;
    }
}

int Estrai_Punti(char nome_utente[], int punti_ini){
    int id_prenotazione, saldo_punti;
    char  nome[30],localita_partenza[50], localita_arrivo[50], buffer[500], *res, *ip, *n, *sp, *p, *lp, *la;
    double prezzo;
    FILE *fp = fopen("lista_prenotazioni.txt","r");
    if(fp != NULL){
        while(!feof(fp)){
            res = fgets(buffer, 500, fp);
            if(res != NULL){
                 n = strtok(res, ",");
                strcpy(nome,n);
                ip = strtok(NULL, ",");
                id_prenotazione = atoi(ip);
                lp = strtok(NULL, ",");
                strcpy(localita_partenza,lp);
                la = strtok(NULL, ",");
                strcpy(localita_arrivo,la);
                p = strtok(NULL, ",");
                prezzo = atof(p);
                sp = strtok(NULL, ";");
                saldo_punti = atoi(sp);
                if(strcmp(nome,nome_utente) == 0){
                    punti_ini = saldo_punti;
                }
            }
        }
    }else{
        punti_ini = 0;
    }
    fclose(fp);
    return punti_ini;
}

void Leggi_Lista_Prenotazioni(char nome_utente[]){
    int id_prenotazione, saldo_punti;
    char  nome[30],localita_partenza[50], localita_arrivo[50], buffer[500], *res, *ip, *n, *sp, *p, *lp, *la;
    double prezzo;
    FILE *fp = fopen("lista_prenotazioni.txt","r");
    printf("\n=======================================================================================\n");
    SetColor(1);
    printf("\t\t\tLista Prenotazioni Di %s.", nome_utente);
    SetColor(0);
    if(fp != NULL){
        while(!feof(fp)){
            res = fgets(buffer, 500, fp);
            if(res != NULL){
                 n = strtok(res, ",");
                strcpy(nome,n);
                ip = strtok(NULL, ",");
                id_prenotazione = atoi(ip);
                lp = strtok(NULL, ",");
                strcpy(localita_partenza,lp);
                la = strtok(NULL, ",");
                strcpy(localita_arrivo,la);
                p = strtok(NULL, ",");
                prezzo = atof(p);
                sp = strtok(NULL, ";");
                saldo_punti = atoi(sp);
                if(strcmp(nome,nome_utente) == 0){
                    printf("\n=======================================================================================\n");
                    SetColor(2);
                    printf("Id Prenotazione: %d - Tratta: Citta' Di Partenza: %s -> Citta' Di Arrivo: %s - Prezzo: %.3lf Euro", id_prenotazione, localita_partenza, localita_arrivo, prezzo);
                    SetColor(0);
                }
            }
        }
    }
    printf("\n=======================================================================================\n");
    SetColor(4);
    printf("\t\t\tFine Lista Prenotazioni.");
    SetColor(0);
    printf("\n=======================================================================================\n\n");
    fclose(fp);
}

void Saldo_Punti(char nome_utente[]){
    int id_prenotazione, saldo_punti, preno_corr;
    char  nome[30],localita_partenza[50], localita_arrivo[50], buffer[500], *res, *ip, *n, *sp, *p, *lp, *la;
    double prezzo;
    FILE *fp = fopen("lista_prenotazioni.txt","r");
    printf("\n=======================================================================================\n");
    SetColor(1);
    printf("\t\t\tSaldo Punti Di %s.", nome_utente);
    SetColor(0);
    if(fp != NULL){
        while(!feof(fp)){
            res = fgets(buffer, 500, fp);
            if(res != NULL){
                 n = strtok(res, ",");
                strcpy(nome,n);
                ip = strtok(NULL, ",");
                id_prenotazione = atoi(ip);
                lp = strtok(NULL, ",");
                strcpy(localita_partenza,lp);
                la = strtok(NULL, ",");
                strcpy(localita_arrivo,la);
                p = strtok(NULL, ",");
                prezzo = atof(p);
                sp = strtok(NULL, ";");
                saldo_punti = atoi(sp);
                if(strcmp(nome,nome_utente) == 0 && id_prenotazione != preno_corr){
                    preno_corr = id_prenotazione;
                    printf("\n=======================================================================================\n");
                    SetColor(2);
                    printf("Per La Prenotazione %d Hai Guadagnato: %.0lf Punti;", id_prenotazione, prezzo);
                    SetColor(0);
                }
            }
        }
    }
    printf("\n=======================================================================================\n");
    SetColor(4);
    printf("\t\t\tI Suoi Punti Totali Sono %d.", saldo_punti);
    SetColor(0);
    printf("\n=======================================================================================\n\n");
    fclose(fp);
}
