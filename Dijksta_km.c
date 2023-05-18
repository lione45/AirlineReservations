#include "Priority_Queue.h"
#define INFINI 999999.0
Priority_Queue *head3 = NULL;
Priority_Queue *head4 = NULL;
Priority_Queue *head5 = NULL;

double Estrai_Priorita_km(Priority_Queue **testa, char localita[], double km){
	head3 = (*testa);
	while(!(Queue_Vuota(testa))){
		if(strcmp(localita,(*testa)->Localita) == 0){
			km = ((*testa)->Km);
			(*testa) = head3;
			return km;
		}
		(*testa) = (*testa)->next;
	}
	(*testa) = head3;
}

double Valore_Testa_Priorita_km(Priority_Queue **testa, double km){
	km = (*testa)->Km;
    return km;
}

Priority_Queue *Push_km(Priority_Queue **testa, char localita[], double prezzo, char localita_precedente[], double km){
	if(Queue_Vuota(testa)){
		(*testa)= Alloca_Queue(localita, prezzo, localita_precedente, km);
	}else{
    	Priority_Queue *inizio = (*testa);
    	Priority_Queue *tmp = Alloca_Queue(localita, prezzo, localita_precedente, km);
    	if((*testa)->Km > km) {
        	tmp->next = *testa;
        	(*testa) = tmp;
    	}else{
        	while (inizio->next != NULL && inizio->next->Km < km){
            	inizio = inizio->next;
        	}
        	tmp->next = inizio->next;
        	inizio->next = tmp;
    	}
	}
    return (*testa);
}

Priority_Queue *Ini_Coda_Priorita_Km(Grafo *f, Priority_Queue *m, char vertice_partenza[], int index){
	if(!(Grafo_Vuoto(f))){
		if(Verifica_Disponibilita(index, f)){
			int verify = 0;
			if(Esiste_Vertice(f,verify,vertice_partenza)){
				if(strcmp(f->Connessioni[index].Localita, vertice_partenza) != 0){
					m = Push_km(&m, f->Connessioni[index].Localita, INFINI, "NULL", INFINI);
					m = Ini_Coda_Priorita_Km(f, m, vertice_partenza, index + 1);
				}else{
					m = Push_km(&m, f->Connessioni[index].Localita, 0.0, "NULL", 0.0);
					m = Ini_Coda_Priorita_Km(f, m, vertice_partenza, index + 1);
				}
			}else{
				printf("La Localita' Inserita Non e' Presente.\n");
			}
		}
	}
	return m;
}

Priority_Queue *Dijkstra_Km(Grafo *g, char localita_partenza[], char localita_arrivo[]){
	Priority_Queue *Coda_ini = NULL;
	Priority_Queue *Coda_terminale = NULL;
	Priority_Queue *Percorso_min = NULL;
	Arco *tmp = NULL;
	char localita[50], loc[50], prec[50], prex[50];
	double prz = 0.0, n_prz = 0.0, o_prz = 0.0;
	double km =0.0, n_km = 0.0, o_km = 0.0;
    int index1 = 0;
    Coda_ini = Ini_Coda_Priorita_Km(g, Coda_ini, localita_partenza, index1);
    while(!(Queue_Vuota(&Coda_ini))){
        int index2 = 0;
        *localita = Valore_Testa_Localita((&Coda_ini), localita);
        *prec = Valore_Testa_Localita_Precedente((&Coda_ini), prec);
		prz = Valore_Testa_Priorita((&Coda_ini), prz);
		km = Valore_Testa_Priorita_km((&Coda_ini), km);
		tmp = Estrai_Arco(g,localita,index2);
		while(!(Arco_Vuoto(tmp))){
			if(Verifica_Coda_Terminati((&Coda_terminale), tmp->Localita_Collegata)){
				*loc = Estrai_Localita((&Coda_ini), tmp->Localita_Collegata, loc);
				*prex = Estrai_Localita_Precedente((&Coda_ini), tmp->Localita_Collegata, prex);
				o_prz = Estrai_Priorita((&Coda_ini), tmp->Localita_Collegata, o_prz);
				o_km = Estrai_Priorita_km((&Coda_ini), tmp->Localita_Collegata, o_km);
				n_km = km + tmp->Km;
				n_prz = prz + tmp->Prezzo;
				if(n_km < o_km){
					Coda_ini = Push_km((&Coda_ini), loc, n_prz, localita, n_km);
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
			Coda_terminale = Push_km((&Coda_terminale), localita, prz, prec, km);
		}else{
			Dealloca_Priority_Queue((&Coda_ini));
		}
    }
    if(!(Queue_Vuota(&Coda_terminale))){
        Percorso_min = Estrai_Localita_Arrivo_km((&Coda_terminale), Percorso_min, localita_arrivo);
        char local[50];
		char g = 'y';
		while(g == 'y'){
            *local = Estrai_Percorso_Minimo_km((&Coda_terminale), (&Percorso_min), local);
            if(strcmp(local,"NULL") == 0){
                g = 'n';
			}
		}
    }
	return Percorso_min;
}

Priority_Queue *Estrai_Localita_Arrivo_km(Priority_Queue **Coda_terminale, Priority_Queue *Percorso_min, char localita_arrivo[]){
        char localita[50], prec[50];
        double prz = 0.0, km = 0.0;
        head4 = (*Coda_terminale);
        while(!(Queue_Vuota(Coda_terminale))){
            if(strcmp(localita_arrivo,(*Coda_terminale)->Localita) == 0){
                *localita = Estrai_Localita(Coda_terminale, (*Coda_terminale)->Localita, localita);
                *prec = Estrai_Localita_Precedente(Coda_terminale, localita, prec);
                prz = Estrai_Priorita(Coda_terminale, localita, prz);
                km = Estrai_Priorita_km(Coda_terminale, localita, km);
                Percorso_min = Push_km((&Percorso_min), localita, prz, prec, km);
                (*Coda_terminale) = head4;
                return Percorso_min;
            }
		(*Coda_terminale) = (*Coda_terminale)->next;
        }
        (*Coda_terminale) = head4;
}

char Estrai_Percorso_Minimo_km(Priority_Queue **Coda_terminale, Priority_Queue **Percorso_min, char prec[]){
	char localita[50];
	double prz = 0.0, km = 0.0;
	head5 = (*Coda_terminale);
	*prec = Valore_Testa_Localita_Precedente(Percorso_min, prec);
	while(!(Queue_Vuota(Coda_terminale))){
		if(strcmp(prec,(*Coda_terminale)->Localita) == 0){
			*localita = Estrai_Localita(Coda_terminale, (*Coda_terminale)->Localita, localita);
			*prec = Estrai_Localita_Precedente(Coda_terminale, localita, prec);
			prz = Estrai_Priorita(Coda_terminale, localita, prz);
			km = Estrai_Priorita_km(Coda_terminale, localita, km);
			(*Percorso_min) = Push_km(Percorso_min, localita, prz, prec, km);
			(*Coda_terminale) = head5;
			return *prec;
		}
		(*Coda_terminale) = (*Coda_terminale)->next;
	}
	(*Coda_terminale) = head5;
}
