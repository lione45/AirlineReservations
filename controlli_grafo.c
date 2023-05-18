#include "grafi.h"

char pulisci_buffer_localita(char p[]){
	int n_dim;
	if (strrchr(p,'\n')){
		n_dim = strlen(p)-1;
		p[n_dim]='\0';
	}
	return *p;
}

bool Grafo_Vuoto(Grafo *gv){
	if(gv == NULL){
		return true;
	}else if(gv->Numero_Localita == 0){
		return true;
	}else{
		return false;
	}
}

bool Arco_Vuoto(Arco *i){
	if(i == NULL){
		return true;
	}else{
		return false;
	}
}

bool Verifica_Disponibilita(int index, Grafo *k){
	if(index < k->Numero_Localita){
		return true;
	}else{
		return false;
	}
}

bool Esiste_Vertice(Grafo *h, int index, char localita[]){
	if(!(Grafo_Vuoto(h))){
		if(Verifica_Disponibilita(index,h)){
			if(strcmp(localita,h->Connessioni[index].Localita) == 0){
				return true;
			}else{
				Esiste_Vertice(h, index + 1, localita);
			}
		}else{
			return false;
		}
	}else{
		return false;
	}
}

bool Esiste_Volo_Diretto(Grafo *l, char localita_partenza[], char localita_arrivo[], int index){
    if(!(Grafo_Vuoto(l))){
        if(Verifica_Disponibilita(index,l)){
			if(strcmp(localita_partenza,l->Connessioni[index].Localita) == 0){
                Arco *tmp = l->Connessioni[index].arco;
                while(!(Arco_Vuoto(tmp))){
                    if(strcmp(localita_arrivo,tmp->Localita_Collegata) == 0){
                        printf("\n1)Diretto:");
                        printf("\n============================================================");
                        printf("\nIl Volo Diretto Da %s a %s Costa: ", localita_partenza, localita_arrivo);
                        SetColor(12);
                        printf("%.3lf Euro.\n", tmp->Prezzo);
                        SetColor(0);
                        printf("============================================================\n\n");
                        return true;
                    }
                    tmp = tmp->next;
                }
                printf("\nDiretto:");
                printf("\n============================================================");
                SetColor(4);
                printf("\nNon Sono Previsti Voli Diretti Per La Seguente Tratta: %s - %s.\n", localita_partenza, localita_arrivo);
                SetColor(0);
                printf("============================================================\n");
                return false;
            }else{
                Esiste_Volo_Diretto(l, localita_partenza, localita_arrivo,index + 1);
            }
        }
    }
}

bool Esiste_Tratta(Grafo *h, char localita_partenza[], char localita_arrivo[], int index){
    if(!(Grafo_Vuoto(h))){
		if(Verifica_Disponibilita(index,h)){
			if(strcmp(localita_partenza,h->Connessioni[index].Localita) == 0){
				Arco *tmp = h->Connessioni[index].arco;
				while(!(Arco_Vuoto(tmp))){
                    if(strcmp(localita_arrivo,tmp->Localita_Collegata) == 0){
                        return true;
                    }
                    tmp = tmp->next;
				}
				return false;
			}else{
				Esiste_Tratta(h, localita_partenza, localita_arrivo, index + 1);
			}
		}
	}
}
