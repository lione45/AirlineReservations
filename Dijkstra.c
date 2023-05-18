#include "Priority_Queue.h"
Priority_Queue *head = NULL;
Priority_Queue *head2 = NULL;

Priority_Queue *Dijkstra(Grafo *g, char localita_partenza[], char localita_arrivo[]){
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
        Percorso_min = Estrai_Localita_Arrivo((&Coda_terminale), Percorso_min, localita_arrivo);
        char local[50];
		char g = 'y';
		while(g == 'y'){
            *local = Estrai_Percorso_Minimo((&Coda_terminale), (&Percorso_min), local);
            if(strcmp(local,"NULL") == 0){
                g = 'n';
			}
		}
    }
	return Percorso_min;
}

Arco *Estrai_Arco(Grafo *u, char vertice[], int index){
	if(!(Grafo_Vuoto(u))){
		int verifica = 0;
		if(Esiste_Vertice(u, verifica, vertice)){
			if(Verifica_Disponibilita(index, u)){
				if(strcmp(vertice,u->Connessioni[index].Localita) == 0){
					return u->Connessioni[index].arco;
				}else{
					Estrai_Arco(u, vertice, index + 1);
				}
			}
		}
	}
}

char Estrai_Localita(Priority_Queue **testa, char localita[], char localita_estratta[]){
	head = (*testa);
	while(!(Queue_Vuota(testa))){
		if(strcmp(localita,(*testa)->Localita) == 0){
			strcpy(localita_estratta, (*testa)->Localita);
			(*testa) = head;
			return *localita_estratta;
		}
		(*testa) = (*testa)->next;
	}
	(*testa) = head;
}

char Estrai_Localita_Precedente(Priority_Queue **testa, char localita[], char localita_estratta[]){
	head = (*testa);
	while(!(Queue_Vuota(testa))){
		if(strcmp(localita,(*testa)->Localita) == 0){
			strcpy(localita_estratta, (*testa)->Localita_Precedente);
			(*testa) = head;
			return *localita_estratta;
		}
		(*testa) = (*testa)->next;
	}
	(*testa) = head;
}


double Estrai_Priorita(Priority_Queue **testa, char localita[], double prezzo){
	head = (*testa);
	while(!(Queue_Vuota(testa))){
		if(strcmp(localita,(*testa)->Localita) == 0){
			prezzo = ((*testa)->prezzo);
			(*testa) = head;
			return prezzo;
		}
		(*testa) = (*testa)->next;
	}
	(*testa) = head;
}

bool Verifica_Coda_Terminati(Priority_Queue **testa,char localita[]){
	head = (*testa);
	while(!(Queue_Vuota(testa))){
		if(strcmp(localita, (*testa)->Localita) == 0){
			(*testa) = head;
			return false;
		}
		(*testa) = (*testa)->next;
	}
	(*testa) = head;
	return true;
}

Priority_Queue *Estrai_Localita_Arrivo(Priority_Queue **Coda_terminale, Priority_Queue *Percorso_min, char localita_arrivo[]){
        char localita[50], prec[50];
        double prz = 0.0, km = 0.0;
        head2 = (*Coda_terminale);
        while(!(Queue_Vuota(Coda_terminale))){
            if(strcmp(localita_arrivo,(*Coda_terminale)->Localita) == 0){
                *localita = Estrai_Localita(Coda_terminale, (*Coda_terminale)->Localita, localita);
                *prec = Estrai_Localita_Precedente(Coda_terminale, localita, prec);
                prz = Estrai_Priorita(Coda_terminale, localita, prz);
                km = Estrai_Priorita_km(Coda_terminale, localita, km);
                Percorso_min = Push((&Percorso_min), localita, prz, prec, km);
                (*Coda_terminale) = head2;
                return Percorso_min;

            }
		(*Coda_terminale) = (*Coda_terminale)->next;
        }
        (*Coda_terminale) = head2;
}

void Stampa_Queue(Priority_Queue **testa, int i){
	head = (*testa);
	int count = 0;
    count = Conta_Queue(testa, count);
	while(!(Queue_Vuota(testa))){
        if(i == 0){
            i++;
            (*testa) = (*testa)->next;
        }else{
            printf("\n============================================================");
            printf("\nTratta Scalo %d:\nCitta' Di Partenza: %s -> Citta' Di Arrivo: %s.", i,(*testa)->Localita_Precedente, (*testa)->Localita);
            if(i == count-1){
                printf("\n============================================================");
                SetColor(2);
                printf("\n\t\tPrezzo Totale: %.3lf Euro.\n",(*testa)->prezzo);
                SetColor(0);
                printf("============================================================\n\n");
            }
            i++;
            (*testa) = (*testa)->next;
        }

	}
	(*testa) = head;
}

char Estrai_Percorso_Minimo(Priority_Queue **Coda_terminale, Priority_Queue **Percorso_min, char prec[]){
	char localita[50];
	double prz = 0.0, km = 0.0;
	head2 = (*Coda_terminale);
	*prec = Valore_Testa_Localita_Precedente(Percorso_min, prec);
	while(!(Queue_Vuota(Coda_terminale))){
		if(strcmp(prec,(*Coda_terminale)->Localita) == 0){
			*localita = Estrai_Localita(Coda_terminale, (*Coda_terminale)->Localita, localita);
			*prec = Estrai_Localita_Precedente(Coda_terminale, localita, prec);
			prz = Estrai_Priorita(Coda_terminale, localita, prz);
			km = Estrai_Priorita_km(Coda_terminale, localita, km);
			(*Percorso_min) = Push(Percorso_min, localita, prz, prec, km);
			(*Coda_terminale) = head2;
			return *prec;

		}
		(*Coda_terminale) = (*Coda_terminale)->next;
	}
	(*Coda_terminale) = head2;
}

int Conta_Queue(Priority_Queue **testa, int i){
	head = (*testa);
	while(!(Queue_Vuota(testa))){
        i++;
        (*testa) = (*testa)->next;
	}
    (*testa) = head;
    return i;
}
