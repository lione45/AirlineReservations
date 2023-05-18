#include "grafi.h"

int conta_vertici(int count){
	FILE *fp = fopen("grafo.txt","r");
	char buffer[5000], *res;
	if(fp != NULL){
		while(!feof(fp)){
			res = fgets(buffer, 5000, fp);
			if(res != NULL){
				count++;
			}
		}
	}
	fclose(fp);
	return count;
}

Grafo *leggi_grafo_da_file(Grafo *e, int index){
	int num_localita = 0;
	num_localita = conta_vertici(num_localita);
	e = Crea_Grafo_Per_File(e ,num_localita);
	FILE *fp = fopen("grafo.txt", "r");
	int notorieta;
	double prezzo, km;
	char localita_arrivo[50], *la, buffer_tmp[5000], *bt, *p, *r, *t;
	char buffer[5000], *res, localita[30], *l, buffer2[5000], *b2;
	if(fp != NULL){
        while(!feof(fp)){
            res = fgets(buffer,5000,fp);
            if((res != NULL)){
                if(Verifica_Disponibilita(index, e)){
                    l = strtok(res, ",");
                    strcpy(localita,l);
                    strcpy(e->Connessioni[index].Localita,localita);
                    r = strtok(NULL, "{");
                    notorieta = atoi(r);
                    e->Connessioni[index].Notorieta = notorieta;
                    b2 = strtok(NULL, "}");
                    strcpy(buffer2,b2);
                    while(strcmp(buffer2,"\0") != 0){
                        la = strtok(buffer2, ",");
                        strcpy(localita_arrivo, la);
                        p = strtok(NULL,",");
                        prezzo = atof(p);
                        t = strtok(NULL,";");
                        km = atof(t);
                        e = Inserisci_Arco_Da_File(e, index, localita_arrivo, prezzo, km);
                        bt = strtok(NULL, "}");
                        if(bt != NULL){
                            strcpy(buffer_tmp,bt);
                            strcpy(buffer2,buffer_tmp);
                        }else{
                            strcpy(buffer2,"\0");
                        }
                    }
                    index++;
                }
            }
        }
    }
	return e;
}

Grafo *Inizializza_Grafo_Per_File(int numero_localita){
	int index = 0;
	Grafo *g = (Grafo*)malloc(sizeof(Grafo));
	g->Numero_Localita = numero_localita;
	g->Connessioni = (Lista_Archi*)malloc(numero_localita*sizeof(Lista_Archi));
	g->Connessioni = Inizializza_Lista_Archi_Per_File(g,index);
    return g;
}

Lista_Archi *Inizializza_Lista_Archi_Per_File(Grafo *h, int i){
	if(!(Grafo_Vuoto(h))){
		if(Verifica_Disponibilita(i, h)){
			strcpy(h->Connessioni[i].Localita, "NULL");
			h->Connessioni[i].Notorieta = 0;
			h->Connessioni[i].arco = NULL;
			h->Connessioni = Inizializza_Lista_Archi_Per_File(h, i + 1);
		}
	}
	return h->Connessioni;
}

Grafo *Crea_Grafo_Per_File(Grafo *f, int numero_localita){
	f = Inizializza_Grafo_Per_File(numero_localita);
	return f;
}

Grafo *Inserisci_Arco_Da_File(Grafo * r, int nodo_partenza, char localita_arrivo[], double prezzo, double km){
	if(!(Grafo_Vuoto(r))){
		Arco *a = Alloca_Arco(localita_arrivo, prezzo, km);
		a->next = r->Connessioni[nodo_partenza].arco;
		r->Connessioni[nodo_partenza].arco = a;
	}
    return r;
}

double trova_spesa_minima(Grafo *k, char localita[], int index, double spesa_minima){
    if(!(Grafo_Vuoto(k))){
        if(Verifica_Disponibilita(index,k)){
            if(strcmp(k->Connessioni[index].Localita,localita) == 0){
                int i = 0;
                double min;
                Arco *tmp = k->Connessioni[index].arco;
                while(!(Arco_Vuoto(tmp))){
                    if(i == 0){
                        min = tmp->Prezzo;
                        spesa_minima = min;
                    }
                    if((tmp->Prezzo < min)){
                        min = tmp->Prezzo;
                        spesa_minima = min;
                    }
                i ++;
                tmp = tmp->next;
                }
            }else{
                spesa_minima = trova_spesa_minima(k, localita, index + 1 , spesa_minima);
            }
        }
    }
    return spesa_minima;
}
