#include <stdio.h>

int main(void){

    int x;
    int anterior;
    int cont=0;
    
    scanf("%d",&x);

    while(x>=0){
        if(cont>0 && x <= anterior){ // Checa primero la primera condición, después la segunda.
            break;
        }

        anterior = x;
        cont++;

        scanf("%d",&x);
    }

    printf("%d",cont);
    

    return 0;
}