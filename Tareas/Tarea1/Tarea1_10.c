#include <stdio.h>

int primo(int);

int main(void){

    int a;

    while(1){
    printf("\n Escribe un numero entre 3 y 4000: ");
    scanf("%i",&a);

    if(a<3 || a>4000){
        printf("\n Numero invalido.");
    }
    else 
        break;
    }

    if(primo(a)==1){
        printf("\n Es numero primo.");
    }
    else{
        printf("\n No es numero primo.");
    }

    return 0;
}

int primo(int a){
    int cont = 0;

    for(int i=2;i<=a;i++){
        if(a%i==0){
            cont++;
        }
    }
    if(cont>1){
        return 0;
    }
    else{
        return 1;
    }
}