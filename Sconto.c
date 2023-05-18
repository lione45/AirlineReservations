#include "Priority_Queue.h"

double Sconto(int *saldo_punti, double o_prezzo, double n_prezzo){
    int scelta, punti, sconto;
    punti = (*saldo_punti);
    do{
        printf("\nQuale Percentuale Si Sconto Vuoi Applicare?\n\n\t");
        printf("1)10 %%;\n\t2)20 %%;\n\t3)30 %%;\n\t4)40 %%;\n\t5)50 %%;\n\t6)60 %%;\n\t7)70 %%;\n\t8)80 %%;\n\t9)90 %%;\n\t10)100 %%;");
        printf("\n\nLa Tua Risposta:");
        scanf("%d", &scelta);
        while('\n'!=getchar());
        switch(scelta){
            case 1:
                    if(punti >= 1000){
                        sconto = (10*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 1000;
                        (*saldo_punti) = punti;
                    }
                break;
            case 2:
                    if(punti >= 2000){
                        sconto = (20*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 2000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            case 3:
                    if(punti >= 3000){
                        sconto = (30*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 3000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            case 4:
                    if(punti >= 4000){
                        sconto = (40*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 4000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            case 5:
                    if(punti >= 5000){
                        sconto = (50*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 5000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            case 6:
                    if(punti >= 6000){
                        sconto = (60*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 6000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            case 7:
                    if(punti >= 7000){
                        sconto = (70*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 7000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            case 8:
                    if(punti >= 8000){
                        sconto = (80*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 8000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            case 9:
                    if(punti >= 9000){
                        sconto = (90*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 9000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            case 10:
                    if(punti >= 10000){
                        sconto = (1000*o_prezzo)/100;
                        n_prezzo = o_prezzo - sconto;
                        punti -= 10000;
                        (*saldo_punti) = punti;
                    }else{
                        printf("\n==============================\n");
                        SetColor(4);
                        printf("Punti Insufficienti Per Applicare Questo Sconto.\nIl Tuo Saldo Attuale e' Di %d Punti.",punti);
                        SetColor(0);
                        printf("\n==============================\n");
                        scelta = 11;
                    }
                break;
            default:
                printf("\n==============================\n");
                SetColor(4);
                printf("Scelta Errata, Ritenta.");
                SetColor(0);
                printf("\n==============================\n");
                break;
        }
    }while(scelta != 1 && scelta != 2 && scelta != 3 && scelta != 4 && scelta != 5 && scelta != 6 && scelta != 7 && scelta != 8 && scelta != 9 && scelta != 10);
    return n_prezzo;
}
 void Aggiorna_notorieta(Grafo *f, char localita_arrivo[]){
    int coordinate_arrivo = 0;
    coordinate_arrivo = Estrai_Indice_Localita_Arrivo(f,localita_arrivo, coordinate_arrivo);
    f->Connessioni[coordinate_arrivo].Notorieta += 1;
 }

char Gettonata(Grafo *b, int index, char localita[]){
    int max = 0;
    if(!(Grafo_Vuoto(b))){
        while(Verifica_Disponibilita(index, b)){
                if(index == 0){
                        max = b->Connessioni[index].Notorieta;
                        strcpy(localita, b->Connessioni[index].Localita);
                }
                    if((b->Connessioni[index].Notorieta > max)){
                        max = b->Connessioni[index].Notorieta;
                        strcpy(localita, b->Connessioni[index].Localita);
                    }
                index ++;
        }
    }
    return *localita;
}
