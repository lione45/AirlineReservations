#include "grafi.h"

Arco *Alloca_Arco(char localita_collegata[],double prezzo, double km){
    Arco *f = (Arco *)malloc(sizeof(Arco));
    strcpy(f->Localita_Collegata, localita_collegata);
    f->Prezzo = prezzo;
    f->Km = km;
    f->next = NULL;
    return f;
}

Grafo *Inizializza_Grafo(int numero_localita){
	int index = 0;
	Grafo *g = (Grafo*)malloc(sizeof(Grafo));
	g->Numero_Localita = numero_localita;
	g->Connessioni = (Lista_Archi*)malloc(numero_localita*sizeof(Lista_Archi));
	g->Connessioni = Inizializza_Lista_Archi(g,index);
    return g;
}

Lista_Archi *Inizializza_Lista_Archi(Grafo *h, int i){
    srand(time(NULL));
	if(!(Grafo_Vuoto(h))){
		if(Verifica_Disponibilita(i, h)){
			char localita[50];
			printf("Inserisci Localita':");
			fgets(localita, 50, stdin);
        	*localita = pulisci_buffer_localita(localita);
			strcpy(h->Connessioni[i].Localita, localita);
			h->Connessioni[i].Notorieta = rand()%+1;;
			h->Connessioni[i].arco = NULL;
			h->Connessioni = Inizializza_Lista_Archi(h, i + 1);
		}
	}
	return h->Connessioni;
}

Grafo *Crea_Grafo(Grafo *f, int numero_localita){
	int i = 0;
	f = Inizializza_Grafo(numero_localita);
	f = Crea_Archi(f, i);
	return f;
}

Grafo *Crea_Archi(Grafo *o, int index){
	if(!(Grafo_Vuoto(o))){
		if(Verifica_Disponibilita(index, o)){
			int n_archi;
			printf("Quanti Collegamenti Ha La Citta' Di %s:", o->Connessioni[index].Localita);
			scanf("%d", &n_archi);
			while('\n'!=getchar());
			if(n_archi != 0 && n_archi <= o->Numero_Localita){
				int count = 0;
				o = Inserisci_Arco(o, index, count, n_archi);
				o = Crea_Archi(o, index + 1);
			}else{
				o = Crea_Archi(o, index + 1);
			}
		}
	}
	return o;
}

Grafo *Inserisci_Arco(Grafo * r, int nodo_partenza, int i, int numero_archi){
	if(!(Grafo_Vuoto(r))){
		int verifica = 0;
		if(i < numero_archi){
			double prezzo;
			double km;
			char localita_arrivo[50];
			printf("Con Quale Localita' e' Collegata:");
			fgets(localita_arrivo, 50, stdin);
        	*localita_arrivo = pulisci_buffer_localita(localita_arrivo);
			if(Esiste_Vertice(r, verifica, localita_arrivo)){
        		printf("Inserisci Il Prezzo Del Volo:");
        		scanf("%lf", &prezzo);
        		while('\n'!=getchar());
                printf("Quanti Km Separano La Citta' %s Dalla Citta' %s:", r->Connessioni[nodo_partenza].Localita, localita_arrivo);
        		scanf("%lf", &km);
        		while('\n'!=getchar());
				Arco *a = Alloca_Arco(localita_arrivo, prezzo, km);
				a->next = r->Connessioni[nodo_partenza].arco;
				r->Connessioni[nodo_partenza].arco = a;
				r = Inserisci_Arco(r, nodo_partenza, i + 1, numero_archi);
			}else{
				printf("La Localita' Inserita Non e' Presente.\n");
				r = Inserisci_Arco(r, nodo_partenza, i, numero_archi);
			}
		}
	}
    return r;
}

void Stampa_Grafo(Grafo *a, int v){
	if(!(Grafo_Vuoto(a))){
		if(Verifica_Disponibilita(v, a)){
			Arco *tmp = a->Connessioni[v].arco;
			SetColor(0);
			printf("\n====================================================================");
            SetColor(2);
            printf("\nLista Dei Collegamenti Alla Citta' Di %s Con I Relativi Prezzi E Distanze:\n\n", a->Connessioni[v].Localita);
            Stampa_Arco(tmp);
            Stampa_Grafo(a, v+1);
		}else{
		    SetColor(0);
		    printf("\n===================================================================");
		    SetColor(4);
			printf("\n\t\t\tFine Tratte.\n");
			SetColor(0);
			printf("===================================================================\n\n");
		}
	}
}

void Stampa_Arco(Arco *v){
        if(!(Arco_Vuoto(v))){
            printf("\tCitta': %s, Prezzo: %.2lf Euro, Distanza: %.3lf Km;\n", v->Localita_Collegata, v->Prezzo, v->Km);
            Stampa_Arco(v->next);
        }
}

Arco *Dealloca_Arco(Arco *v){
    if(!(Arco_Vuoto(v))){
            Dealloca_Arco(v->next);
            v->next = NULL;
            free(v);
    }
    return v;
}
Grafo *Dealloca_Grafo(Grafo *d, int i){
	if(!(Grafo_Vuoto(d))){
		if(Verifica_Disponibilita(i, d)){
			Arco *tmp = d->Connessioni[i].arco;
			tmp = Dealloca_Arco(tmp);
			d = Dealloca_Grafo(d, i + 1);
		}
	}
	return d;
}

void Salva_Grafo_Su_File(Grafo *g, int index){
	FILE *fp = fopen ("grafo.txt", "a");
	if(fp != NULL){
		if(!(Grafo_Vuoto(g))){
			if(Verifica_Disponibilita(index, g)){
				fprintf(fp, "%s,%d{", g->Connessioni[index].Localita,g->Connessioni[index].Notorieta);
				Salva_Arco_Su_File(g->Connessioni[index].arco, fp);
				fprintf(fp,"}\n");
				Salva_Grafo_Su_File(g, index + 1);
			}
		}
	}
	fclose(fp);
}

void Salva_Arco_Su_File(Arco * f, FILE *gp){
	if(gp != NULL){
		if(!(Arco_Vuoto(f))){
			fprintf(gp, "%s,%.2lf,%.3lf;", f->Localita_Collegata, f->Prezzo, f->Km);
			Salva_Arco_Su_File(f->next,gp);
		}
	}
}

