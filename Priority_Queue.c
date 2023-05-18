#include "Priority_Queue.h"
#define INFINI 999999.0

Priority_Queue *Alloca_Queue(char localita[], double prezzo, char localita_precedente[], double km){
    Priority_Queue *queue = (Priority_Queue *)malloc(sizeof(Priority_Queue));
    strcpy(queue->Localita, localita);
    queue->prezzo = prezzo;
    queue->Km = km;
    strcpy(queue->Localita_Precedente, localita_precedente);
    queue->next = NULL;
    return queue;
}

char Valore_Testa_Localita(Priority_Queue **testa, char localita[]){
	strcpy(localita, (*testa)->Localita);
    return *localita;
}

char Valore_Testa_Localita_Precedente(Priority_Queue **testa, char localita_precedente[]){
        strcpy(localita_precedente, (*testa)->Localita_Precedente);
        return *localita_precedente;
}

double Valore_Testa_Priorita(Priority_Queue **testa, double prezzo){
	prezzo = (*testa)->prezzo;
    return prezzo;
}

void Dealloca_Priority_Queue(Priority_Queue **testa){
    if(!(Queue_Vuota(testa))){
        Priority_Queue *tmp = *testa;
        (*testa) = (*testa)->next;
        free(tmp);
    }
}

bool Queue_Vuota(Priority_Queue **testa){
	if((*testa) == NULL){
    	return true;
	}else{
		return false;
	}
}

Priority_Queue *Ini_Coda_Priorita(Grafo *f, Priority_Queue *m, char vertice_partenza[], int index){
	if(!(Grafo_Vuoto(f))){
		if(Verifica_Disponibilita(index, f)){
			int verify = 0;
			if(Esiste_Vertice(f,verify,vertice_partenza)){
				if(strcmp(f->Connessioni[index].Localita, vertice_partenza) != 0){
					m = Push(&m, f->Connessioni[index].Localita, INFINI, "NULL", INFINI);
					m = Ini_Coda_Priorita(f, m, vertice_partenza, index + 1);
				}else{
					m = Push(&m, f->Connessioni[index].Localita, 0.0, "NULL", 0.0);
					m = Ini_Coda_Priorita(f, m, vertice_partenza, index + 1);
				}
			}else{
				printf("La Localita' Inserita Non e' Presente.\n");
			}
		}
	}
	return m;
}

Priority_Queue *Push(Priority_Queue **testa, char localita[], double prezzo, char localita_precedente[],double km){
	if(Queue_Vuota(testa)){
		(*testa)= Alloca_Queue(localita, prezzo, localita_precedente, km);
	}else{
    	Priority_Queue *inizio = (*testa);
    	Priority_Queue *tmp = Alloca_Queue(localita, prezzo, localita_precedente, km);
    	if((*testa)->prezzo > prezzo) {
        	tmp->next = *testa;
        	(*testa) = tmp;
    	}else{
        	while (inizio->next != NULL && inizio->next->prezzo < prezzo) {
            	inizio = inizio->next;
        	}
        	tmp->next = inizio->next;
        	inizio->next = tmp;
    	}
	}
    return (*testa);
}

Priority_Queue *Pop(Priority_Queue **testa, char localita[]){
	while(!(Queue_Vuota(testa))){
		if(strcmp((*testa)->Localita, localita) == 0){
    		Priority_Queue *tmp = (*testa)->next;
    		free(*testa);
			return tmp;
		}
	}
	return (*testa);
}

int salva_prenotazioni_economiche(char nomeutente[], int id_prenotazione, Priority_Queue **testa, double prezzo,  int saldo_punti){
    id_prenotazione = Genera_Id_Prenotazione(nomeutente,id_prenotazione);
    FILE *fp = fopen("lista_prenotazioni.txt","a");
    int i = 0;
    if(fp != NULL){
        while(!(Queue_Vuota(testa))){
            if(i == 0){
                i++;
                (*testa)= (*testa)->next;
            }else{
                fprintf(fp, "%s,%d,%s,%s,%lf,%d;\n",nomeutente, id_prenotazione, (*testa)->Localita_Precedente , (*testa)->Localita,  prezzo, saldo_punti);
                (*testa)= (*testa)->next;
            }
        }
   }
   fclose(fp);
   return id_prenotazione;
}
