#include "lista_preno.h"

Prenotazioni *alloca_prenotazione(char nome[], int id, char partenza[], char arrivo[], double prezzo, int punti){
    Prenotazioni *p = (Prenotazioni *)malloc(sizeof(Prenotazioni));
    strcpy(p->nome_utente,nome);
    p->id_prenotazione = id;
    strcpy(p->localita_partenza,partenza);
    strcpy(p->localita_arrivo,arrivo);
    p->Prezzo = prezzo;
    p->saldo_punti = punti;
    p->next = NULL;
    return p;
}

Prenotazioni *inserisci_prenotazione(Prenotazioni * i, char nome[], int id, char partenza[], char arrivo[], double prezzo, int punti){
    if(i == NULL){
        i = alloca_prenotazione(nome, id, partenza, arrivo, prezzo, punti);
    }else{
        i->next = inserisci_prenotazione(i->next, nome, id, partenza, arrivo, prezzo, punti);
    }
    return i;
}

Prenotazioni *dealloca_prenotazione(Prenotazioni *d){
    if(d != NULL){
        d->next = dealloca_prenotazione(d->next);
        d->next = NULL;
        free(d);
    }
    return d;
}

void salva_prenotazioni(Prenotazioni *c){
    FILE *fp = fopen("lista_prenotazioni.txt","w");
    if(fp != NULL){
       while(c != NULL){
            fprintf(fp, "%s,%d,%s,%s,%lf,%d;\n",c->nome_utente, c->id_prenotazione, c->localita_partenza, c->localita_arrivo, c->Prezzo, c->saldo_punti);
            c = c->next;
        }
   }
   fclose(fp);
}

int cancella_prenotazione(char nome_utente[], int id, int verifica){
    int id_prenotazione, id_corrente, saldo_punti, punti_correnti = 0, fg = verifica;
    char  nome[30],localita_partenza[50], localita_arrivo[50], buffer[500], *res, *ip, *n, *sp, *p, *lp, *la;
    double prezzo;
    Prenotazioni *r = NULL;
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
                prezzo = atoi(p);
                sp = strtok(NULL, ";");
                saldo_punti = atoi(sp);
                if((strcmp(nome,nome_utente) != 0 && id != id_prenotazione) || (strcmp(nome,nome_utente) == 0 && id != id_prenotazione)){
                        r = inserisci_prenotazione(r, nome, id_prenotazione, localita_partenza, localita_arrivo, prezzo, saldo_punti);
                }else{
                    verifica -= 1;
                    if(id_prenotazione != id_corrente){
                        id_corrente = id_prenotazione;
                        punti_correnti = saldo_punti - prezzo;
                    }
                }
            }
        }
    }
    fclose(fp);
    if(fg != verifica){
        modifica_saldo_punti(r, punti_correnti);
    }
    salva_prenotazioni(r);
    r = dealloca_prenotazione(r);
    return verifica;
}

int conta_prenotazioni(int count){
    FILE *fp = fopen("lista_prenotazioni.txt","r");
    char buffer[500], *res;
    if(fp != NULL){
        while(!feof(fp)){
            res = fgets(buffer, 500, fp);
            if(res != NULL){
                    count ++;
            }
        }
    }
    fclose(fp);
    return count;
}

void modifica_saldo_punti(Prenotazioni *a, int punti){
        while(a != NULL){
            a->saldo_punti = punti;
            a = a->next;
        }
}
