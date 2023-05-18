#include "Nascondi_Pass.h"

char nascondi_pass(char pas[]){
    int p=0;
    char ch;
    while(1){
        ch = getch();
        if(ch == ENTER){
            pas[p] = '\0';
            break;
        }else if(ch == BKSP){
            if(p > 0){
                p--;
                printf("\b \b");
            }
        }else{
            pas[p] = ch;
            p++;
            printf("*");
        }
    }
    return *pas;
}
