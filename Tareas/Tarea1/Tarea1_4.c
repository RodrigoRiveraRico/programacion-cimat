#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int conversion(int,float,int);

int main(void){
    float d; // Número en base 10
    int k; // Precisión después punto decimal binario

    printf("\n Numero en base 10 y precision: ");
    scanf("%f %d",&d,&k); 

    conversion((int)d, d-(int)d, k);

    return 0;
}

int conversion(int e, float f, int k){
    int x = e;
    int *vector; // Apuntador
    int acum = 1;
    int cont = 1;
    int expo = 1;
    int b;

    if(e<0 || f<0){
        printf("-");
    }
    x = abs(x);
    f = fabsf(f);


    while(acum < abs(e)){
        expo*=2;
        acum+=expo;
        cont++;
    }

    // Asignar memoria dinámicamente con malloc
    vector = (int *) malloc(cont * sizeof(int));

    for(int i=cont-1;i>=0;i--){
        vector[i] = x%2;
        x/=2;
    }

    // printf("\n Imprimimos parte entera en binario: ");
    for(int i=0;i<cont;i++){
        printf("%d",vector[i]);
    }

    free(vector);

    printf(".");

    for(int i=0;i<k;i++){  // Precisión a k dígitos después del punto decimal.
        b = (int)(f*2);
        f = (f*2)-(int)(f*2);
        printf("%d",b);
    }

    return 0;
}