#include "menu.h"
#include "Utente.h"
#include "Admin.h"
#include "Priority_Queue.h"
#include "lista_preno.h"

int main (){
    char loop = 'n';
    int scelta_ini , login , utente, admin, UT, AD, check_nome_admin;
    int e = 0, i=0, j=0, s=0, index = 0, scelta, scelta1, id, punti, punti_ini = 0, scelta_viaggio, verify = 0, n_prenotazioni = 0;
    double prezzo, prezzo_scontato, spesa_prevista, spesa_minima = 0.0;
    Grafo *g = NULL;
    Priority_Queue *Percorso_Migliore = NULL;
    Priority_Queue *Percorso_Veloce = NULL;
    Priority_Queue *Risparmi = NULL;
    char nome_utente[30], nome_admin[30], paswd_admin[30], localita_partenza[50], localita_arrivo[50], localita[50], scelta_sconto, conferma;
    while(loop == 'n' || loop == 'N'){
        ClearConsoleToColors(0, 15);
        do{
            scelta_ini = menu_iniziale(scelta_ini);
            while('\n'!=getchar());
            switch(scelta_ini){
                case 1:
                    do{
                        utente = primo_menu_utente(utente);
                        while('\n'!=getchar());
                        int verifica = 0;
                        switch(utente){
                            case 1:
                                    do{
                                        printf("\nInserisci Username:");
                                        fgets(nome_utente, 30, stdin);
                                        *nome_utente = pulisci_buffer(nome_utente);
                                        verifica = Esiste_Nome_Utente(nome_utente, verifica);
                                        if(verifica != 1){
                                            printf("\n==============================\n");
                                            SetColor(4);
                                            printf("Lo Username Inserito Non e' Corretto.");
                                            SetColor(0);
                                            printf("\n==============================\n\n");
                                        }
                                    }while(verifica != 1);
                                    login = accedi(login, nome_utente);
                                    if(login == 0){
                                        printf("\n\n==============================\n");
                                        SetColor(2);
                                        printf("Login Avvenuto Con Successo.");
                                        SetColor(0);
                                        printf("\n==============================\n\n");
                                    }
                                    do{
                                        UT = menu_utente(UT, nome_utente);
                                        while('\n'!=getchar());
                                        switch(UT){
                                            case 1:
                                                index = 0;
                                                e = 0;
                                                g = leggi_grafo_da_file(g, e);
                                                do{
                                                    printf("\nSai Gia' Dove Andare?\n\n\t");
                                                    SetColor(6);
                                                    printf("1)Si, Allora Prenota Cosa Aspetti?\n\t");
                                                    SetColor(10);
                                                    printf("2)No, Vuoi Che Ci Pensiamo Noi?\n\n");
                                                    SetColor(0);
                                                    printf("La Tua Risposta:");
                                                    scanf("%d",&scelta);
                                                    while('\n'!=getchar());
                                                    switch (scelta){
                                                        case 1:
                                                            do{
                                                                index = 0;
                                                                printf("\nInserisci Localita' Partenza:");
                                                                fgets(localita_partenza, 50, stdin);
                                                                *localita_partenza = pulisci_buffer_localita(localita_partenza);
                                                                if(!(Esiste_Vertice(g, index,localita_partenza))){
                                                                    printf("\n==============================\n");
                                                                    SetColor(4);
                                                                    printf("La Localita' Di Partenza Non Esiste.");
                                                                    SetColor(0);
                                                                    printf("\n==============================\n\n");
                                                                }
                                                            }while(!(Esiste_Vertice(g, index,localita_partenza)));
                                                            do{
                                                                index = 0;
                                                                printf("Inserisci Localita' Arrivo:");
                                                                fgets(localita_arrivo, 50, stdin);
                                                                *localita_arrivo = pulisci_buffer_localita(localita_arrivo);
                                                                if(!(Esiste_Vertice(g, index,localita_arrivo))){
                                                                    printf("\n==============================\n");
                                                                    SetColor(4);
                                                                    printf("La Localita' Di Arrivo Non Esiste.");
                                                                    SetColor(0);
                                                                    printf("\n==============================\n\n");
                                                                }
                                                            }while(!(Esiste_Vertice(g, index,localita_arrivo)));
                                                            Aggiorna_notorieta(g,localita_arrivo);
                                                            pulisci_file();
                                                            s = 0;
                                                            Salva_Grafo_Su_File(g, s);
                                                            index = 0;
                                                            if(Esiste_Volo_Diretto(g, localita_partenza, localita_arrivo, index)){
                                                                index = 0;
                                                                Percorso_Migliore = Dijkstra(g,localita_partenza,localita_arrivo);
                                                                printf("2)Economico:");
                                                                Stampa_Queue((&Percorso_Migliore), index);
                                                                do{
                                                                    printf("\nQuale Tipo Di Volo Scegli?\n\n\t1)Diretto;\n\t2)Economico;\n\t3)Annulla;\n\nLa Tua Risposta:");
                                                                    scanf("%d",&scelta1);
                                                                    while('\n'!=getchar());
                                                                    switch(scelta1){
                                                                        case 1:
                                                                                prezzo = Estrai_Prezzo_diretto(g,localita_partenza,localita_arrivo, prezzo);
                                                                                punti_ini = 0;
                                                                                punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                scanf("\n%c", &scelta_sconto);
                                                                                while('\n'!=getchar());
                                                                                if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                    prezzo_scontato = 0;
                                                                                    prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                    punti = punti_ini + prezzo_scontato;
                                                                                    id = salva_prenotazioni_diretti(nome_utente, id, localita_partenza, localita_arrivo, prezzo_scontato, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.",id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(4);
                                                                                    printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                    punti = punti_ini + prezzo;
                                                                                    id = salva_prenotazioni_diretti(nome_utente, id, localita_partenza, localita_arrivo, prezzo, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.",id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                    punti = punti_ini + prezzo;
                                                                                    id = salva_prenotazioni_diretti(nome_utente, id, localita_partenza, localita_arrivo, prezzo, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.",id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }
                                                                            break;
                                                                        case 2:
                                                                                punti_ini = 0;
                                                                                punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                prezzo = Estrai_Priorita((&Percorso_Migliore), localita_arrivo, prezzo);
                                                                                printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                scanf("\n%c", &scelta_sconto);
                                                                                while('\n'!=getchar());
                                                                                if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                    prezzo_scontato = 0;
                                                                                    prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                    punti = punti_ini + prezzo_scontato;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo_scontato, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(4);
                                                                                    printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                    punti = punti_ini + prezzo;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                    punti = punti_ini + prezzo;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }
                                                                            break;
                                                                        case 3:
                                                                                printf("\n==============================\n");
                                                                                SetColor(2);
                                                                                printf("Prenotazione Annullata.");
                                                                                SetColor(0);
                                                                                printf("\n==============================\n\n");
                                                                            break;
                                                                        default:
                                                                                printf("\n==============================\n");
                                                                                SetColor(4);
                                                                                printf("Scelta Errata, Ritenta.");
                                                                                SetColor(0);
                                                                                printf("\n==============================\n\n");
                                                                            break;
                                                                    }
                                                                }while((scelta1 != 1 && scelta1 != 2) && scelta1 != 3);
                                                            }else{
                                                                index = 0;
                                                                printf("\n1)Breve Tempo Di Percorrenza:");
                                                                Percorso_Veloce = Dijkstra_Km(g,localita_partenza,localita_arrivo);
                                                                Stampa_Queue((&Percorso_Veloce), index);
                                                                index = 0;
                                                                printf("\n2)Economico:");
                                                                Percorso_Migliore = Dijkstra(g,localita_partenza,localita_arrivo);
                                                                Stampa_Queue((&Percorso_Migliore), index);
                                                                do{
                                                                    printf("\nQuale Tipo Di Volo Scegli?\n\n\t1)Breve Tempo Di Percorrenza;\n\t2)Economico;\n\t3)Annulla;\n\nLa Tua Risposta:");
                                                                    scanf("%d",&scelta1);
                                                                    while('\n'!=getchar());
                                                                    switch(scelta1){
                                                                        case 1:
                                                                                punti_ini = 0;
                                                                                punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                prezzo = Estrai_Priorita((&Percorso_Veloce), localita_arrivo, prezzo);
                                                                                printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                scanf("\n%c", &scelta_sconto);
                                                                                while('\n'!=getchar());
                                                                                if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                    prezzo_scontato = 0;
                                                                                    prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                    punti = punti_ini + prezzo_scontato;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Veloce), prezzo_scontato, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(4);
                                                                                    printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                    punti = punti_ini + prezzo;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Veloce), prezzo, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                    punti = punti_ini + prezzo;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Veloce), prezzo, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }
                                                                            break;
                                                                        case 2:
                                                                                punti_ini = 0;
                                                                                punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                prezzo = Estrai_Priorita((&Percorso_Migliore), localita_arrivo, prezzo);
                                                                                printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                scanf("\n%c", &scelta_sconto);
                                                                                while('\n'!=getchar());
                                                                                if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                    prezzo_scontato = 0;
                                                                                    prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                    punti = punti_ini + prezzo_scontato;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo_scontato, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(4);
                                                                                    printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                    punti = punti_ini + prezzo;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                    punti = punti_ini + prezzo;
                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo, punti);
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(2);
                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                }
                                                                            break;
                                                                        case 3:
                                                                                printf("\n==============================\n");
                                                                                SetColor(2);
                                                                                printf("Prenotazione Annullata.");
                                                                                SetColor(0);
                                                                                printf("\n==============================\n\n");
                                                                            break;
                                                                        default:
                                                                                printf("\n==============================\n");
                                                                                SetColor(4);
                                                                                printf("Scelta Errata, Ritenta.");
                                                                                SetColor(0);
                                                                                printf("\n==============================\n\n");
                                                                            break;
                                                                    }
                                                                }while((scelta1 != 1 && scelta1 != 2) && scelta1 != 3);
                                                            }
                                                            break;
                                                        case 2:
                                                                e = 0;
                                                                g = leggi_grafo_da_file(g, e);
                                                                do{
                                                                    index = 0;
                                                                    printf("\nInserisci Localita' Partenza:");
                                                                    fgets(localita_partenza, 50, stdin);
                                                                    *localita_partenza = pulisci_buffer_localita(localita_partenza);
                                                                    if(!(Esiste_Vertice(g, index,localita_partenza))){
                                                                        printf("\n==============================\n");
                                                                        SetColor(4);
                                                                        printf("La Localita' Di Partenza Non Esiste.");
                                                                        SetColor(0);
                                                                        printf("\n==============================\n\n");
                                                                    }
                                                                }while(!(Esiste_Vertice(g, index,localita_partenza)));
                                                                index = 0;
                                                                spesa_minima = trova_spesa_minima(g, localita_partenza, index, spesa_minima);
                                                                do{
                                                                    printf("\nQuale Meta Preferisci?\n\n\t1)Economica;\n\t2)Gettonata;\n\t3)Annulla;\n\nLa Tua Risposta:");
                                                                    scanf("%d",&scelta_viaggio);
                                                                    while('\n'!=getchar());
                                                                    switch(scelta_viaggio){
                                                                        case 1:
                                                                            do{
                                                                                printf("\nQuanto Sei Disposto a Spendere?\tEuro:");
                                                                                scanf("%lf", &spesa_prevista);
                                                                                if(spesa_prevista < spesa_minima){
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(4);
                                                                                    printf("Da %s La Spesa Minima e' %.3lf Euro.", localita_partenza, spesa_minima);
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                    printf("Vuoi Continuare?\n\n\tY)Per Confermare;\n\tN)Per Terminare;\n\nLa Tua Risposta:");
                                                                                    scanf("\n%c", &conferma);
                                                                                    while('\n'!=getchar());
                                                                                    if(conferma == 'N' || conferma == 'n'){
                                                                                        printf("\n==============================\n");
                                                                                        SetColor(2);
                                                                                        printf("Prenotazione Annullata.");
                                                                                        SetColor(0);
                                                                                        printf("\n==============================\n\n");
                                                                                        break;
                                                                                    }
                                                                                }
                                                                            }while(spesa_prevista < spesa_minima);
                                                                                if(conferma == 'N' || conferma == 'n'){
                                                                                    break;
                                                                                }
                                                                                Risparmi = Dijkstra_Partenza_Economica(g, localita_partenza, localita, spesa_prevista);
                                                                                index = 0;
                                                                                Stampa_Queue((&Risparmi), index);
                                                                                printf("\nIl Nostro Sistema Le Suggerisce La Seguente Meta: %s.",localita);
                                                                            do{
                                                                                printf("Confermare Il Volo Da %s A %s?\n\n\tY)Per Confermare;\n\tN)Per Terminare;\n\nLa Tua Risposta:", localita_partenza, localita);
                                                                                scanf("\n%c", &conferma);
                                                                                while('\n'!=getchar());
                                                                                if(conferma == 'y' || conferma == 'Y'){
                                                                                    punti_ini = 0;
                                                                                    punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                    prezzo = Estrai_Priorita((&Risparmi), localita, prezzo);
                                                                                    printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                    scanf("\n%c", &scelta_sconto);
                                                                                    while('\n'!=getchar());
                                                                                    if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                            prezzo_scontato = 0;
                                                                                            prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                            punti = punti_ini + prezzo_scontato;
                                                                                            id = salva_prenotazioni_economiche(nome_utente, id, (&Risparmi), prezzo_scontato, punti);
                                                                                            printf("\n==============================\n");
                                                                                            SetColor(2);
                                                                                            printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                            SetColor(0);
                                                                                            printf("\n==============================\n\n");
                                                                                    }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                            printf("\n==============================\n");
                                                                                            SetColor(4);
                                                                                            printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                            SetColor(0);
                                                                                            printf("\n==============================\n\n");
                                                                                            punti = punti_ini + prezzo;
                                                                                            id = salva_prenotazioni_economiche(nome_utente, id, (&Risparmi), prezzo, punti);
                                                                                            printf("\n==============================\n");
                                                                                            SetColor(2);
                                                                                            printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                            SetColor(0);
                                                                                            printf("\n==============================\n\n");
                                                                                    }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                            punti = punti_ini + prezzo;
                                                                                            id = salva_prenotazioni_economiche(nome_utente, id, (&Risparmi), prezzo, punti);
                                                                                            printf("\n==============================\n");
                                                                                            SetColor(2);
                                                                                            printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                            SetColor(0);
                                                                                            printf("\n==============================\n\n");
                                                                                    }

                                                                            }else if (conferma == 'n' || conferma == 'N'){
                                                                                printf("\n==============================\n");
                                                                                SetColor(2);
                                                                                printf("Prenotazione Annullata.");
                                                                                SetColor(0);
                                                                                printf("\n==============================\n\n");
                                                                            }else{
                                                                                printf("\n==============================\n");
                                                                                SetColor(4);
                                                                                printf("Scelta Errata, Ritenta.");
                                                                                SetColor(0);
                                                                                printf("\n==============================\n\n");
                                                                            }
                                                                        }while((conferma != 'y' && conferma != 'Y') && (conferma != 'n' && conferma != 'N'));
                                                                            break;
                                                                        case 2:
                                                                            s = 0;
                                                                            *localita_arrivo = Gettonata (g, s, localita_arrivo);
                                                                            if(strcmp(localita_partenza,localita_arrivo) == 0){
                                                                                    printf("\n==============================\n");
                                                                                    SetColor(4);
                                                                                    printf("Impossibile Prenotare Il Volo Citta' Di Partenza e Meta Gettonata Coincidono.");
                                                                                    SetColor(0);
                                                                                    printf("\n==============================\n\n");
                                                                                    break;
                                                                            }
                                                                            printf("\nIl Nostro Sistema Le Suggerisce La Seguente Meta: %s.",localita_arrivo);
                                                                            Aggiorna_notorieta(g,localita_arrivo);
                                                                            pulisci_file();
                                                                            s = 0;
                                                                            Salva_Grafo_Su_File(g, s);
                                                                            index = 0;
                                                                            if(Esiste_Volo_Diretto(g, localita_partenza, localita_arrivo, index)){
                                                                                index = 0;
                                                                                Percorso_Migliore = Dijkstra(g,localita_partenza,localita_arrivo);
                                                                                printf("2)Economico:");
                                                                                Stampa_Queue((&Percorso_Migliore), index);
                                                                                do{
                                                                                    printf("\nQuale Tipo Di Volo Scegli?\n\n\t1)Diretto;\n\t2)Economico;\n\t3)Annulla;\n\nLa Tua Risposta:");
                                                                                    scanf("%d",&scelta1);
                                                                                    while('\n'!=getchar());
                                                                                    switch(scelta1){
                                                                                        case 1:
                                                                                                prezzo = Estrai_Prezzo_diretto(g,localita_partenza,localita_arrivo, prezzo);
                                                                                                punti_ini = 0;
                                                                                                punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                                printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                                scanf("\n%c", &scelta_sconto);
                                                                                                while('\n'!=getchar());
                                                                                                if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                                    prezzo_scontato = 0;
                                                                                                    prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                                    punti = punti_ini + prezzo_scontato;
                                                                                                    id = salva_prenotazioni_diretti(nome_utente, id, localita_partenza, localita_arrivo, prezzo_scontato, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.",id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(4);
                                                                                                    printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                    punti = punti_ini + prezzo;
                                                                                                    id = salva_prenotazioni_diretti(nome_utente, id, localita_partenza, localita_arrivo, prezzo, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.",id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                                    punti = punti_ini + prezzo;
                                                                                                    id = salva_prenotazioni_diretti(nome_utente, id, localita_partenza, localita_arrivo, prezzo, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.",id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }
                                                                                            break;
                                                                                        case 2:
                                                                                                punti_ini = 0;
                                                                                                punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                                prezzo = Estrai_Priorita((&Percorso_Migliore), localita_arrivo, prezzo);
                                                                                                printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                                scanf("\n%c", &scelta_sconto);
                                                                                                while('\n'!=getchar());
                                                                                                if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                                    prezzo_scontato = 0;
                                                                                                    prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                                    punti = punti_ini + prezzo_scontato;
                                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo_scontato, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(4);
                                                                                                    printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                    punti = punti_ini + prezzo;
                                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                                    punti = punti_ini + prezzo;
                                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }
                                                                                            break;
                                                                                        case 3:
                                                                                                printf("\n==============================\n");
                                                                                                SetColor(2);
                                                                                                printf("Prenotazione Annullata.");
                                                                                                SetColor(0);
                                                                                                printf("\n==============================\n\n");
                                                                                            break;
                                                                                        default:
                                                                                                printf("\n==============================\n");
                                                                                                SetColor(4);
                                                                                                printf("Scelta Errata, Ritenta.");
                                                                                                SetColor(0);
                                                                                                printf("\n==============================\n\n");
                                                                                            break;
                                                                                        }
                                                                                    }while((scelta1 != 1 && scelta1 != 2) && scelta1 != 3);
                                                                            }else{
                                                                                index = 0;
                                                                                printf("\n1)Breve Tempo Di Percorrenza:");
                                                                                Percorso_Veloce = Dijkstra_Km(g,localita_partenza,localita_arrivo);
                                                                                Stampa_Queue((&Percorso_Veloce), index);
                                                                                index = 0;
                                                                                printf("\n2)Economico:");
                                                                                Percorso_Migliore = Dijkstra(g,localita_partenza,localita_arrivo);
                                                                                Stampa_Queue((&Percorso_Migliore), index);
                                                                                do{
                                                                                    printf("\nQuale Tipo Di Volo Scegli?\n\n\t1)Breve Tempo Di Percorrenza;\n\t2)Economico;\n\t3)Annulla;\n\nLa Tua Risposta:");
                                                                                    scanf("%d",&scelta1);
                                                                                    while('\n'!=getchar());
                                                                                    switch(scelta1){
                                                                                        case 1:
                                                                                                punti_ini = 0;
                                                                                                punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                                prezzo = Estrai_Priorita((&Percorso_Veloce), localita_arrivo, prezzo);
                                                                                                printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                                scanf("\n%c", &scelta_sconto);
                                                                                                while('\n'!=getchar());
                                                                                                if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                                        prezzo_scontato = 0;
                                                                                                        prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                                        punti = punti_ini + prezzo_scontato;
                                                                                                        id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Veloce), prezzo_scontato, punti);
                                                                                                        printf("\n==============================\n");
                                                                                                        SetColor(2);
                                                                                                        printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                        SetColor(0);
                                                                                                        printf("\n==============================\n\n");
                                                                                                }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                                        printf("\n==============================\n");
                                                                                                        SetColor(4);
                                                                                                        printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                                        SetColor(0);
                                                                                                        printf("\n==============================\n\n");
                                                                                                        punti = punti_ini + prezzo;
                                                                                                        id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Veloce), prezzo, punti);
                                                                                                        printf("\n==============================\n");
                                                                                                        SetColor(2);
                                                                                                        printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                        SetColor(0);
                                                                                                        printf("\n==============================\n\n");
                                                                                                }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                                        punti = punti_ini + prezzo;
                                                                                                        id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Veloce), prezzo, punti);
                                                                                                        printf("\n==============================\n");
                                                                                                        SetColor(2);
                                                                                                        printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                        SetColor(0);
                                                                                                        printf("\n==============================\n\n");
                                                                                                }
                                                                                            break;
                                                                                        case 2:
                                                                                                punti_ini = 0;
                                                                                                punti_ini = Estrai_Punti(nome_utente, punti_ini);
                                                                                                prezzo = Estrai_Priorita((&Percorso_Migliore), localita_arrivo, prezzo);
                                                                                                printf("\nVuoi Applicare Uno Sconto?\n\n\tY)Si;\n\tN)No;\n\nLa Tua Risposta:");
                                                                                                scanf("\n%c", &scelta_sconto);
                                                                                                while('\n'!=getchar());
                                                                                                if((scelta_sconto == 'y' || scelta_sconto == 'Y') && punti_ini >= 1000){
                                                                                                    prezzo_scontato = 0;
                                                                                                    prezzo_scontato = Sconto((&punti_ini), prezzo, prezzo_scontato);
                                                                                                    punti = punti_ini + prezzo_scontato;
                                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo_scontato, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }else if((scelta_sconto == 'y' || scelta_sconto == 'Y') && (punti_ini >= 0 && punti_ini < 1000)){
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(4);
                                                                                                    printf("Sconto Non Applicablie Punti Insufficienti.");
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                    punti = punti_ini + prezzo;
                                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }else if (scelta_sconto == 'n' || scelta_sconto == 'N'){
                                                                                                    punti = punti_ini + prezzo;
                                                                                                    id = salva_prenotazioni_economiche(nome_utente, id, (&Percorso_Migliore), prezzo, punti);
                                                                                                    printf("\n==============================\n");
                                                                                                    SetColor(2);
                                                                                                    printf("Prenotazione Volo Di Id: %d Effettuata.", id);
                                                                                                    SetColor(0);
                                                                                                    printf("\n==============================\n\n");
                                                                                                }
                                                                                            break;
                                                                                        case 3:
                                                                                                printf("\n==============================\n");
                                                                                                SetColor(2);
                                                                                                printf("Prenotazione Annullata.");
                                                                                                SetColor(0);
                                                                                                printf("\n==============================\n\n");
                                                                                            break;
                                                                                        default:
                                                                                                printf("\n==============================\n");
                                                                                                SetColor(4);
                                                                                                printf("Scelta Errata, Ritenta.");
                                                                                                SetColor(0);
                                                                                                printf("\n==============================\n\n");
                                                                                            break;
                                                                                        }
                                                                                    }while((scelta1 != 1 && scelta1 != 2) && scelta1 != 3);
                                                                                }
                                                                            break;
                                                                        case 3:
                                                                                printf("\n==============================\n");
                                                                                SetColor(12);
                                                                                printf("Hai Deciso Di Tornare Al Menu' Precedente.");
                                                                                SetColor(0);
                                                                                printf("\n==============================\n\n");
                                                                            break;
                                                                        default:
                                                                                printf("\n==============================\n");
                                                                                SetColor(4);
                                                                                printf("Scelta Errata, Ritenta.");
                                                                                SetColor(0);
                                                                                printf("\n==============================\n\n");
                                                                            break;
                                                                    }
                                                                }while((scelta_viaggio != 1 && scelta_viaggio != 2) && scelta_viaggio != 3);
                                                            break;
                                                        default:
                                                                printf("\n==============================\n");
                                                                SetColor(4);
                                                                printf("Scelta Errata, Ritenta.");
                                                                SetColor(0);
                                                                printf("\n==============================\n\n");
                                                            break;
                                                        }
                                                    }while(scelta != 1 && scelta != 2);
                                                break;
                                            case 2:
                                                Leggi_Lista_Prenotazioni(nome_utente);
                                                break;
                                            case 3:
                                                Saldo_Punti(nome_utente);
                                                break;
                                            case 4:
                                                    printf("\nInserisci Id Della Prenotazione Da Eliminare:");
                                                    scanf("%d", &id);
                                                    while('\n'!=getchar());
                                                    n_prenotazioni = conta_prenotazioni(n_prenotazioni);
                                                    verify = cancella_prenotazione(nome_utente, id, n_prenotazioni);
                                                    if(verify == n_prenotazioni){
                                                        printf("\n==============================\n");
                                                        SetColor(4);
                                                        printf("Prenotazione Id %d Inesistente, Impossibile Eliminare.", id);
                                                        SetColor(0);
                                                        printf("\n==============================\n\n");
                                                    }else if(verify != n_prenotazioni){
                                                        printf("\n==============================\n");
                                                        SetColor(2);
                                                         printf("Prenotazione Id %d Eliminata Con Successo.", id);
                                                        SetColor(0);
                                                        printf("\n==============================\n\n");
                                                    }
                                                break;
                                            case 5:
                                                    printf("\n==============================\n");
                                                    SetColor(12);
                                                    printf("Logout Effettuato Con Successo.");
                                                    SetColor(0);
                                                    printf("\n==============================\n\n");
                                                break;
                                            default:
                                                    printf("\n==============================\n");
                                                    SetColor(4);
                                                    printf("Scelta Errata, Ritenta.");
                                                    SetColor(0);
                                                    printf("\n==============================\n\n");
                                                break;
                                        }
                                    }while((UT != 1 ||  UT != 2 || UT != 3 || UT != 4) && UT != 5);
                                break;
                            case 2:
                                    verifica = registrati(verifica);
                                    if(verifica == 0){
                                        printf("\n\n==============================\n");
                                        SetColor(2);
                                        printf("Registrazione Avvenuta Con Successo.");
                                        SetColor(0);
                                        printf("\n==============================\n\n");
                                    }
                                break;
                            case 3:
                                    printf("\n==============================\n");
                                    SetColor(12);
                                    printf("Hai Deciso Di Tornare Al Menu' Precedente.");
                                    SetColor(0);
                                    printf("\n==============================\n\n");
                                break;
                            default:
                                    printf("\n==============================\n");
                                    SetColor(4);
                                    printf("Scelta Errata, Ritenta.");
                                    SetColor(0);
                                    printf("\n==============================\n\n");
                                break;
                        }
                    }while((utente != 1 ||  utente != 2) && utente != 3);
                    break;
                case 2:
                        do{
                            printf("Per Ragioni Di Sicurezza Inserisci User Dell'Admin:");
                            fgets(nome_admin, 30, stdin);
                            *nome_admin = pulisci_buffer_admin(nome_admin);
                            check_nome_admin = Esiste_Nome_Admin(nome_admin, check_nome_admin);
                            if((strcmp(nome_admin,"admin") != 0 && strcmp(nome_admin,"Admin") != 0) && check_nome_admin != 1){
                                printf("\n==============================\n");
                                SetColor(4);
                                printf("Spiacente Ma Lo User Admin e' Errato.");
                                SetColor(0);
                                printf("\n==============================\n\n");
                            }
                        }while((strcmp(nome_admin,"admin") != 0 && strcmp(nome_admin,"Admin") != 0) && check_nome_admin != 1);
                        if(strcmp(nome_admin,"admin") == 0 || strcmp(nome_admin,"Admin") == 0){
                            do{
                                printf("Inserisci Password:");
                                *paswd_admin = nascondi_pass(paswd_admin);
                                if((strcmp(paswd_admin,"admin") != 0) && (strcmp(paswd_admin,"Admin") != 0)){
                                    printf("\n\n==============================\n");
                                    SetColor(4);
                                    printf("Spiacente Ma La Password e' Errata.");
                                    SetColor(0);
                                    printf("\n==============================\n\n");
                                }
                            }while((strcmp(paswd_admin,"admin") != 0) && (strcmp(paswd_admin,"Admin") != 0));
                            do{
                                e = 0;
                                admin = primo_menu_admin(admin);
                                g = leggi_grafo_da_file(g,e);
                                while('\n'!=getchar());
                                int verifica = 0;
                                switch (admin){
                                    case 1:
                                            verifica = Registra_Admin(verifica);
                                            if(verifica == 0){
                                                printf("\n\n==============================\n");
                                                SetColor(2);
                                                printf("Registrazione Avvenuta Con Successo.");
                                                SetColor(0);
                                                printf("\n==============================\n\n");
                                            }
                                        break;
                                    case 2:
                                            printf("\n==============================\n");
                                            SetColor(12);
                                            printf("Logout Effettuato Con Successo.");
                                            SetColor(0);
                                            printf("\n==============================\n\n");
                                        break;
                                    default:
                                            printf("\n==============================\n");
                                            SetColor(4);
                                            printf("Scelta Errata, Ritenta.");
                                            SetColor(0);
                                            printf("\n==============================\n\n");
                                        break;
                                }
                            }while(admin != 1 && admin != 2);
                        }else{
                            login = Accedi_Admin(login, nome_admin);
                            if(login == 0){
                                printf("\n\n==============================\n");
                                SetColor(2);
                                printf("Login Avvenuto Con Successo.");
                                SetColor(0);
                                printf("\n==============================\n\n");
                            }
                            do{
                                AD = menu_admin(AD, nome_admin);
                                while('\n'!=getchar());
                                switch(AD){
                                    case 1:
                                            e = 0;
                                            g = leggi_grafo_da_file(g,e);
                                           do{
                                                printf("\nCosa Vuoi Fare?\n\n\t1)Aggiungi Localita';\n\t2)Aggiungi Tratta;\n\nLa Tua Risposta:");
                                                scanf("%d",&scelta);
                                                while('\n'!=getchar());
                                                switch (scelta){
                                                    case 1:
                                                            index = 0;
                                                            printf("\nInserisci Localita':");
                                                            fgets(localita, 50, stdin);
                                                            *localita = pulisci_buffer_localita(localita);
                                                            if((Esiste_Vertice(g, index,localita))){
                                                                printf("\n==============================\n");
                                                                SetColor(4);
                                                                printf("Localita' Esistente.");
                                                                SetColor(0);
                                                                printf("\n==============================\n\n");
                                                            }
                                                            g = Aggiungi_Vertice(g, localita);
                                                            pulisci_file();
                                                            Salva_Grafo_Su_File(g, s);
                                                            printf("\n==============================\n");
                                                            SetColor(2);
                                                            printf("Localita' Aggiunta Con Successo.");
                                                            SetColor(0);
                                                            printf("\n==============================\n\n");
                                                        break;
                                                    case 2:
                                                            do{
                                                                index = 0;
                                                                printf("\nInserisci Localita' Partenza:");
                                                                fgets(localita_partenza, 50, stdin);
                                                                *localita_partenza = pulisci_buffer_localita(localita_partenza);
                                                                if(!(Esiste_Vertice(g, index,localita_partenza))){
                                                                    printf("\n==============================\n");
                                                                    SetColor(4);
                                                                    printf("La Localita' Di Partenza Non Esiste.");
                                                                    SetColor(0);
                                                                    printf("\n==============================\n\n");
                                                                }
                                                            }while(!(Esiste_Vertice(g, index,localita_partenza)));
                                                            do{
                                                                index = 0;
                                                                printf("Inserisci Localita' Arrivo:");
                                                                fgets(localita_arrivo, 50, stdin);
                                                                *localita_arrivo = pulisci_buffer_localita(localita_arrivo);
                                                                if(!(Esiste_Vertice(g, index,localita_arrivo))){
                                                                    printf("\n==============================\n");
                                                                    SetColor(4);
                                                                    printf("La Localita' Di Arrivo Non Esiste.");
                                                                    SetColor(0);
                                                                    printf("\n==============================\n\n");
                                                                }
                                                            }while(!(Esiste_Vertice(g, index,localita_arrivo)));
                                                            index = 0;
                                                            if(Esiste_Tratta(g,localita_partenza,localita_arrivo, index)){
                                                                printf("\n==============================\n");
                                                                SetColor(4);
                                                                printf("La Tratta Scelta Esiste, Impossibile Aggiungere.");
                                                                SetColor(0);
                                                                printf("\n==============================\n\n");
                                                            }else{
                                                                index = 0;
                                                                g = Aggiungi_Tratta(g,localita_partenza, localita_arrivo);
                                                                pulisci_file();
                                                                Salva_Grafo_Su_File(g, index);
                                                                printf("\n==============================\n");
                                                                SetColor(2);
                                                                printf("Tratta Aggiunta Con Successo.");
                                                                SetColor(0);
                                                                printf("\n==============================\n\n");
                                                            }
                                                        break;
                                                    default:
                                                            printf("\n==============================\n");
                                                            SetColor(4);
                                                            printf("Scelta Errata, Ritenta.");
                                                            SetColor(0);
                                                            printf("\n==============================\n\n");
                                                        break;
                                                    }
                                            }while(scelta != 1 && scelta != 2);
                                        break;
                                    case 2:
                                            e = 0;
                                            g = leggi_grafo_da_file(g,e);
                                            do{
                                                printf("\nCosa Vui Fare?\n\n\t1)Elimina Localita';\n\t2)Elimina Tratta;\n\nLa Tua Risposta:");
                                                scanf("%d",&scelta);
                                                while('\n'!=getchar());
                                                switch (scelta){
                                                    case 1:
                                                            index = 0;
                                                            printf("\nInserisci Localita' Da Eliminare:");
                                                            fgets(localita, 50, stdin);
                                                            *localita = pulisci_buffer_localita(localita);
                                                            if(!(Esiste_Vertice(g, index,localita))){
                                                                printf("\n==============================\n");
                                                                SetColor(4);
                                                                printf("Localita' Inesistente.");
                                                                SetColor(0);
                                                                printf("\n==============================\n\n");
                                                            }
                                                            e = 0;
                                                            g = Cancella_Meta(g, localita, e);
                                                            pulisci_file();
                                                            Salva_Grafo_Su_File(g, s);
                                                            printf("\n==============================\n");
                                                            SetColor(2);
                                                            printf("Localita' Eliminata Con Successo.");
                                                            SetColor(0);
                                                            printf("\n==============================\n\n");
                                                        break;
                                                    case 2:
                                                            do{
                                                                index = 0;
                                                                printf("\nInserisci Localita' Partenza:");
                                                                fgets(localita_partenza, 50, stdin);
                                                                *localita_partenza = pulisci_buffer_localita(localita_partenza);
                                                                if(!(Esiste_Vertice(g, index,localita_partenza))){
                                                                    printf("\n==============================\n");
                                                                    SetColor(4);
                                                                    printf("La Localita' Di Partenza Non Esiste.");
                                                                    SetColor(0);
                                                                    printf("\n==============================\n\n");
                                                                }
                                                            }while(!(Esiste_Vertice(g, index,localita_partenza)));
                                                            do{
                                                                index = 0;
                                                                printf("Inserisci Localita' Arrivo:");
                                                                fgets(localita_arrivo, 50, stdin);
                                                                *localita_arrivo = pulisci_buffer_localita(localita_arrivo);
                                                                if(!(Esiste_Vertice(g, index,localita_arrivo))){
                                                                    printf("\n==============================\n");
                                                                    SetColor(4);
                                                                    printf("La Localita' Di Arrivo Non Esiste.");
                                                                    SetColor(0);
                                                                    printf("\n==============================\n\n");
                                                                }
                                                            }while(!(Esiste_Vertice(g, index,localita_arrivo)));
                                                            index = 0;
                                                            if(!(Esiste_Tratta(g,localita_partenza,localita_arrivo, index))){
                                                                printf("\n==============================\n");
                                                                SetColor(4);
                                                                printf("La Tratta Scelta Non Esiste, Impossibile Eliminare.");
                                                                SetColor(0);
                                                                printf("\n==============================\n\n");
                                                            }else{
                                                                g = Elimina_Tratta(g,localita_partenza, localita_arrivo);
                                                                pulisci_file();
                                                                Salva_Grafo_Su_File(g, index);
                                                                printf("\n==============================\n");
                                                                SetColor(2);
                                                                printf("Tratta Eliminata Con Successo.");
                                                                SetColor(0);
                                                                printf("\n==============================\n\n");
                                                            }
                                                        break;
                                                    default:
                                                            printf("\n==============================\n");
                                                            SetColor(4);
                                                            printf("Scelta Errata, Ritenta.");
                                                            SetColor(0);
                                                            printf("\n==============================\n\n");
                                                        break;
                                                    }
                                            }while(scelta != 1 && scelta != 2);
                                        break;
                                    case 3:
                                            e = 0;
                                            g = leggi_grafo_da_file(g,e);
                                            Stampa_Grafo(g,i);
                                        break;
                                    case 4:
                                            printf("\n==============================\n");
                                            SetColor(12);
                                            printf("Logout Effettuato Con Successo.");
                                            SetColor(0);
                                            printf("\n==============================\n\n");
                                        break;
                                    default:
                                            printf("\n==============================\n");
                                            SetColor(4);
                                            printf("Scelta Errata, Ritenta.");
                                            SetColor(0);
                                            printf("\n==============================\n\n");
                                        break;
                                    }
                            }while((AD != 1 ||  AD != 2 || AD != 3) && AD != 4);
                        }
                    break;
                case 3:
                        printf("\n==============================\n");
                        SetColor(12);
                        printf("Hai Deciso Di Uscire.");
                        SetColor(0);
                        printf("\n==============================\n");
                    break;
                default:
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Scelta Errata, Ritenta.");
                        SetColor(0);
                        printf("\n==============================\n\n");
					break;
            }
        }while((scelta_ini != 1 ||  scelta_ini != 2) && scelta_ini != 3);
    printf("\nSei Sicuro Di Voler Uscire Dal Programma?\n\n\tY)Per Terminare;\n\tN)Per Continuare;\n\nLa Tua Risposta:");
	scanf("\n%c",&loop);
    }
    g = Dealloca_Grafo(g, j);
    return 0;
}
