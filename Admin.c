#include "Admin.h"

int Registra_Admin(int verifica){
    char conferma_paswd[30], nome_utente[30], paswd[30];
    int b = 0;
    FILE *gp = fopen("passwd_admin.txt", "a");
    do{
        printf("\nInserisci Username:");
        fgets(nome_utente, 30, stdin);
        *nome_utente = pulisci_buffer_admin(nome_utente);
        b = Esiste_Nome_Admin(nome_utente, b);
        if(b != 2 && b != 0){
            printf("\n\n==============================\n");
            SetColor(4);
            printf("Lo Username Inserito e' Gia' In Uso.");
            SetColor(0);
            printf("\n==============================\n\n");
        }
    }while(b != 2 && b != 0);
    do{
        printf("Inserisci Password:");
        *paswd = nascondi_pass(paswd);
        printf("\nConferma Password:");
        *conferma_paswd = nascondi_pass(conferma_paswd);
        if(strcmp(paswd,conferma_paswd) != 0){
            printf("\n\n==============================\n");
            SetColor(4);
            printf("Spiacente Ma Le Password Non Coincidono.");
            SetColor(0);
            printf("\n==============================\n\n");
        }
    }while(strcmp(paswd,conferma_paswd) != 0);
    fprintf(gp, "%s,%s;\n", nome_utente, paswd);
    verifica = 0;
    fclose(gp);
    return verifica;
}

char pulisci_buffer_admin(char p[]){
	int n_dim;
	if (strrchr(p,'\n')){
		n_dim = strlen(p)-1;
		p[n_dim]='\0';
	}
	return *p;
}

int Esiste_Nome_Admin(char nome_utente[], int ver){
    FILE *fp = fopen("passwd_admin.txt","r");
    char *n, *p, *res, nome[30], buffer[30], pas[30];
    if(fp != NULL){
		while(!feof(fp)){
			res = fgets(buffer, 30, fp);
			if(res != NULL){
			    n = strtok(res, ",");
				strcpy(nome,n);
				p = strtok(NULL, ";");
				strcpy(pas,p);
                if(strcmp(nome,nome_utente) != 0){
                        ver = 2;
                }else{
                        ver = 1;
                        fclose(fp);
                        return ver;
                }
			}
		}
    }
    fclose(fp);
    return ver;
}

int Esiste_Paswd_Admin(char paswd[], char nome_utente[], int ve){
    FILE *fp = fopen("passwd_admin.txt","r");
    char *p, *n, *res, pas[30], buffer[30], nome[30];
    if(fp != NULL){
		while(!feof(fp)){
			res = fgets(buffer, 30, fp);
			if(res != NULL){
                n = strtok(res, ",");
				strcpy(nome,n);
			    p = strtok(NULL, ";");
				strcpy(pas,p);
                if(strcmp(nome,nome_utente) == 0){
                        if (strcmp(pas,paswd) == 0){
                                ve = 2;
                                fclose(fp);
                                return ve;
                        }else{
                                ve = 1;
                    }
                }
			}
		}
    }
    fclose(fp);
    return ve;
}

int Accedi_Admin(int verifica, char nome_ut[]){
    char paswd[30];
    int c = 0;
    do{
        printf("Inserisci Password:");
        *paswd = nascondi_pass(paswd);
        c = Esiste_Paswd_Admin(paswd, nome_ut, c);
        if(c != 2){
            printf("\n\n==============================\n");
            SetColor(4);
            printf("La Password Inserita Non e' Corretta.");
            SetColor(0);
            printf("\n==============================\n\n");
        }
    }while(c != 2);
    verifica = 0;
    return verifica;
}
