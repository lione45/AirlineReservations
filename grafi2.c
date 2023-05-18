#include "grafi.h"

Grafo *Aggiungi_Vertice(Grafo *l, char localita[]){
   int controllo = 0, index = 0;
   int dim, real_dim;
   char sc;
   Lista_Archi *p;
   if (!(Grafo_Vuoto(l)) && !(Esiste_Vertice(l, controllo, localita))){
        dim = l->Numero_Localita + 1;
        real_dim = dim - 1;
        p = (Lista_Archi *)realloc(l->Connessioni,dim*sizeof(Lista_Archi));
           l->Numero_Localita = dim;
           l->Connessioni = p;
           strcpy(l->Connessioni[real_dim].Localita,localita);
           l->Connessioni[real_dim].Notorieta = 0;
           l->Connessioni[real_dim].arco = NULL;
           do{
                printf("\nVuoi Collegare La Localita' %s Con Tutte Le Altre Localita'?\n\n\tY)Per Confermare;\n\tN)Per Rifiutare;\n\nLa Tua Risposta:", localita);
                scanf("\n%c",&sc);
                while('\n'!=getchar());
                if(sc == 'y' || sc == 'Y'){
                    l = Inserisci_Archi_Per_Tutti(l, real_dim, index, real_dim);
                }else if(sc == 'n' || sc == 'N'){
                    l = Crea_Archi_Dopo_Aggiunta_Vertice(l, real_dim);
                }else{
                    printf("\n==============================\n");
                    SetColor(4);
                    printf("Scelta Errata, Ritenta.");
                    SetColor(0);
                    printf("\n==============================\n\n");
                }
           }while((sc != 'y' && sc != 'Y') && (sc != 'n' && sc != 'N'));
    }
    return l;
}

void pulisci_file(){
    FILE *fp = fopen("grafo.txt","w");
    fclose(fp);
}

Grafo *Inserisci_Archi_Per_Tutti(Grafo * r, int nodo_partenza, int i, int numero_archi){
	if(!(Grafo_Vuoto(r))){
		if(i < numero_archi){
			double prezzo;
			double km;
            printf("Inserisci Il Prezzo Del Volo Da %s A %s:", r->Connessioni[nodo_partenza].Localita, r->Connessioni[i].Localita);
            scanf("%lf", &prezzo);
            while('\n'!=getchar());
            printf("Inserisci La Distanza Da %s A %s:", r->Connessioni[nodo_partenza].Localita, r->Connessioni[i].Localita);
            scanf("%lf", &km);
            while('\n'!=getchar());
            Arco *a = Alloca_Arco(r->Connessioni[i].Localita, prezzo, km);
			a->next = r->Connessioni[nodo_partenza].arco;
			r->Connessioni[nodo_partenza].arco = a;
			a = Alloca_Arco(r->Connessioni[nodo_partenza].Localita, prezzo, km);
            a->next = r->Connessioni[i].arco;
            r->Connessioni[i].arco = a;
			r = Inserisci_Archi_Per_Tutti(r, nodo_partenza, i + 1, numero_archi);
		}
	}
    return r;
}

Grafo *Crea_Archi_Dopo_Aggiunta_Vertice(Grafo *o, int index){
	if(!(Grafo_Vuoto(o))){
		if(Verifica_Disponibilita(index, o)){
			int n_archi;
			printf("Quanti Collegamenti Ha La Citta' Di %s:", o->Connessioni[index].Localita);
			scanf("%d", &n_archi);
			while('\n'!=getchar());
			if(n_archi != 0 && n_archi <= o->Numero_Localita){
				int count = 0;
				o = Inserisci_Arco_Dopo_Aggiunta_Vertice(o, index, count, n_archi);
				o = Crea_Archi_Dopo_Aggiunta_Vertice(o, index + 1);
			}else{
				o = Crea_Archi_Dopo_Aggiunta_Vertice(o, index + 1);
			}
		}
	}
	return o;
}

Grafo *Inserisci_Arco_Dopo_Aggiunta_Vertice(Grafo * r, int nodo_partenza, int i, int numero_archi){
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
                int ritorno = 0;
                ritorno = Estrai_Indice_Localita_Arrivo(r, localita_arrivo, ritorno);
        		printf("Inserisci Il Prezzo Del Volo:");
        		scanf("%lf", &prezzo);
        		while('\n'!=getchar());
        		printf("Inserisci La Distanza Dalla Citta' %s Alla Citta' %s:",r->Connessioni[nodo_partenza].Localita, r->Connessioni[ritorno].Localita);
        		scanf("%lf", &km);
        		while('\n'!=getchar());
				Arco *a = Alloca_Arco(localita_arrivo, prezzo, km);
				a->next = r->Connessioni[nodo_partenza].arco;
				r->Connessioni[nodo_partenza].arco = a;
				a = Alloca_Arco(r->Connessioni[nodo_partenza].Localita, prezzo, km);
                a->next = r->Connessioni[ritorno].arco;
                r->Connessioni[ritorno].arco = a;
				r = Inserisci_Arco_Dopo_Aggiunta_Vertice(r, nodo_partenza, i + 1, numero_archi);
			}else{
				printf("La Localita' Inserita Non e' Presente.\n");
				r = Inserisci_Arco_Dopo_Aggiunta_Vertice(r, nodo_partenza, i, numero_archi);
			}
		}
	}
    return r;
}

int Estrai_Indice_Localita_Arrivo(Grafo *j, char localita_arrivo[], int index){
    if(!(Grafo_Vuoto(j))){
        if(Verifica_Disponibilita(index, j)){
            if(strcmp(localita_arrivo,j->Connessioni[index].Localita) == 0){
                return index;
            }else{
                index = Estrai_Indice_Localita_Arrivo(j, localita_arrivo, index + 1);
            }
       }
    }
}

Grafo *Aggiungi_Tratta(Grafo *s, char localita_partenza[], char localita_arrivo[]){
    int coordinata_partenza = 0;
    coordinata_partenza = Estrai_Indice_Localita_Arrivo(s, localita_partenza, coordinata_partenza);
    int coordinata_arrivo = 0;
    coordinata_arrivo = Estrai_Indice_Localita_Arrivo(s,localita_arrivo, coordinata_arrivo);
    double prezzo;
    double km;
    printf("Inserisci Il Prezzo Del Volo Da %s A %s:", s->Connessioni[coordinata_partenza].Localita, s->Connessioni[coordinata_arrivo].Localita);
    scanf("%lf", &prezzo);
    while('\n'!=getchar());
    printf("Inserisci Il Prezzo Del Volo Da %s A %s:", s->Connessioni[coordinata_partenza].Localita, s->Connessioni[coordinata_arrivo].Localita);
    scanf("%lf", &km);
    while('\n'!=getchar());
    Arco *a = Alloca_Arco(s->Connessioni[coordinata_arrivo].Localita, prezzo, km);
    a->next = s->Connessioni[coordinata_partenza].arco;
	s->Connessioni[coordinata_partenza].arco = a;
	a = Alloca_Arco(s->Connessioni[coordinata_partenza].Localita, prezzo, km);
    a->next = s->Connessioni[coordinata_arrivo].arco;
    s->Connessioni[coordinata_arrivo].arco = a;
    return s;
}
Grafo *Elimina_Tratta(Grafo *s, char localita_partenza[], char localita_arrivo[]){
    int coordinata_partenza = 0;
    coordinata_partenza = Estrai_Indice_Localita_Arrivo(s, localita_partenza, coordinata_partenza);
    int coordinata_arrivo = 0;
    coordinata_arrivo = Estrai_Indice_Localita_Arrivo(s,localita_arrivo, coordinata_arrivo);
    s->Connessioni[coordinata_partenza].arco = Rimuovi_Arco(s->Connessioni[coordinata_partenza].arco,localita_arrivo);
    s->Connessioni[coordinata_arrivo].arco = Rimuovi_Arco(s->Connessioni[coordinata_arrivo].arco, localita_partenza);
    return s;
}

Arco* Rimuovi_Arco(Arco* u, char localita_arrivo[]){
	if(u != NULL){
		u->next = Rimuovi_Arco(u->next,localita_arrivo);
		if(strcmp(u->Localita_Collegata, localita_arrivo) == 0){
			Arco* tmp = u->next;
			free(u);
			return tmp;
		}
	}
	return u;
}

Grafo *Cancella_Meta(Grafo *k, char localita[], int index){
    int coordinata_localita = 0;
    coordinata_localita = Estrai_Indice_Localita_Arrivo(k, localita, coordinata_localita);
    k->Connessioni[coordinata_localita].arco = Rimuovi_Tutti_Archi(k->Connessioni[coordinata_localita].arco);
    while((Verifica_Disponibilita(index,k)) && (Verifica_Disponibilita(coordinata_localita,k))){
        k->Connessioni[index].arco = Rimuovi_Arco(k->Connessioni[index].arco,localita);
        k->Connessioni[coordinata_localita] = k->Connessioni[coordinata_localita + 1];
        coordinata_localita++;
        index ++;
    }
    k->Numero_Localita -= 1;
    return k;
}

Arco* Rimuovi_Tutti_Archi(Arco* u){
	if(u != NULL){
		u->next = Rimuovi_Tutti_Archi(u->next);
        Arco* tmp = u->next;
        free(u);
        return tmp;
	}
}
