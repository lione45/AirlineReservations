#include "Priority_Queue.h"
Priority_Queue *head6 = NULL;
Priority_Queue *head7 = NULL;
Priority_Queue *head8 = NULL;

Priority_Queue *Dijkstra_Partenza_Economica(Grafo *g, char localita_partenza[], char localita_arrivo[], double spesa){
	Priority_Queue *Coda_ini = NULL;
	Priority_Queue *Coda_terminale = NULL;
	Priority_Queue *Percorso_min = NULL;
	Arco *tmp = NULL;
	char localita[50], loc[50], prec[50], prex[50];
	double prz = 0.0, n_prz = 0.0, o_prz = 0.0;
	double km = 0.0;
    int index1 = 0;
    Coda_ini = Ini_Coda_Priorita(g, Coda_ini, localita_partenza, index1);
    while(!(Queue_Vuota(&Coda_ini))){
        int index2 = 0;
        *localita = Valore_Testa_Localita((&Coda_ini), localita);
        *prec = Valore_Testa_Localita_Precedente((&Coda_ini), prec);
		prz = Valore_Testa_Priorita((&Coda_ini), prz);
		tmp = Estrai_Arco(g,localita,index2);
		while(!(Arco_Vuoto(tmp))){
			if(Verifica_Coda_Terminati((&Coda_terminale), tmp->Localita_Collegata)){
				*loc = Estrai_Localita((&Coda_ini), tmp->Localita_Collegata, loc);
				*prex = Estrai_Localita_Precedente((&Coda_ini), tmp->Localita_Collegata, prex);
				o_prz = Estrai_Priorita((&Coda_ini), tmp->Localita_Collegata, o_prz);
				n_prz = prz + tmp->Prezzo;
				if(n_prz < o_prz){
					Coda_ini = Push((&Coda_ini), loc, n_prz, localita,km);
					tmp = tmp->next;
				}else{
					tmp = tmp->next;
				}
			}else{
				tmp = tmp->next;
			}
		}
		if(Verifica_Coda_Terminati((&Coda_terminale), localita)){
			Dealloca_Priority_Queue((&Coda_ini));
			Coda_terminale = Push((&Coda_terminale), localita, prz, prec,km);
		}else{
			Dealloca_Priority_Queue((&Coda_ini));
		}
    }
    if(!(Queue_Vuota(&Coda_terminale))){
        *localita_arrivo = Estrai_Localita_Prezzo_Piu_Basso((&Coda_terminale), localita_arrivo, spesa);
        Percorso_min = Estrai_Localita_Arrivo_Prezzo_Minore((&Coda_terminale), Percorso_min, localita_arrivo);
        char local[50];
		char g = 'y';
		while(g == 'y'){
            *local = Estrai_Percorso_Minimo_Prezzo((&Coda_terminale), (&Percorso_min), local);
            if(strcmp(local,"NULL") == 0){
                g = 'n';
			}
		}
    }
	return Percorso_min;
}

char Estrai_Localita_Prezzo_Piu_Basso(Priority_Queue **testa, char localita_arrivo[], double spesa){
    head6 = (*testa);
    double i = 0.0;
    int index = 0;
    while(!(Queue_Vuota(testa))){
            if(index == 0){
                        i = (*testa)->prezzo;
                        strcpy(localita_arrivo,(*testa)->Localita);
            }
                if(((*testa)->prezzo > i)){
                        i = (*testa)->prezzo;
                        if(i <= spesa){
                            strcpy(localita_arrivo,(*testa)->Localita);
                        }
                }
        index ++;
        (*testa) = (*testa)->next;
    }
    (*testa) = head6;
    return *localita_arrivo;
}

Priority_Queue *Estrai_Localita_Arrivo_Prezzo_Minore(Priority_Queue **Coda_terminale, Priority_Queue *Percorso_min, char localita_arrivo[]){
        char localita[50], prec[50];
        double prz = 0.0, km = 0.0;
        head7 = (*Coda_terminale);
        while(!(Queue_Vuota(Coda_terminale))){
            if(strcmp(localita_arrivo,(*Coda_terminale)->Localita) == 0){
                *localita = Estrai_Localita(Coda_terminale, (*Coda_terminale)->Localita, localita);
                *prec = Estrai_Localita_Precedente(Coda_terminale, localita, prec);
                prz = Estrai_Priorita(Coda_terminale, localita, prz);
                km = Estrai_Priorita_km(Coda_terminale, localita, km);
                Percorso_min = Push((&Percorso_min), localita, prz, prec, km);
                (*Coda_terminale) = head7;
                return Percorso_min;

            }
		(*Coda_terminale) = (*Coda_terminale)->next;
        }
        (*Coda_terminale) = head7;
}

char Estrai_Percorso_Minimo_Prezzo(Priority_Queue **Coda_terminale, Priority_Queue **Percorso_min, char prec[]){
	char localita[50];
	double prz = 0.0, km = 0.0;
	head8 = (*Coda_terminale);
	*prec = Valore_Testa_Localita_Precedente(Percorso_min, prec);
	while(!(Queue_Vuota(Coda_terminale))){
		if(strcmp(prec,(*Coda_terminale)->Localita) == 0){
			*localita = Estrai_Localita(Coda_terminale, (*Coda_terminale)->Localita, localita);
			*prec = Estrai_Localita_Precedente(Coda_terminale, localita, prec);
			prz = Estrai_Priorita(Coda_terminale, localita, prz);
			km = Estrai_Priorita_km(Coda_terminale, localita, km);
			(*Percorso_min) = Push(Percorso_min, localita, prz, prec, km);
			(*Coda_terminale) = head8;
			return *prec;

		}
		(*Coda_terminale) = (*Coda_terminale)->next;
	}
	(*Coda_terminale) = head8;
}
