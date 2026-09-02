#include <stdio.h>
#include <stdlib.h>

float prom(int,int *);
int extremos(int, int *);
int arriba_32(int, int *);
int arriba_prom(float, int, int *);
int temps(int, int*);

int main(void){
    int n;
    int *vec;


    printf("\n n = ");
    scanf("%d",&n);

    vec = (int *) malloc(n * sizeof(int));

    for(int i=0;i<n;i++){
        scanf("%d",&vec[i]);
    }

    //Promedio
    prom(n,vec);

    //Extremos
    extremos(n,vec);

    //Temperatura arriba de 32
    arriba_32(n, vec);

    //Arriba del promedio
    arriba_prom(prom(n,vec), n, vec);

    //Imprimir temperaturas
    temps(n, vec);

    free(vec);
    return 0;
}

float prom(int n,int *vec){
    int acum = 0;
    for(int i=0;i<n;i++){
        acum+=vec[i];
    }
    
    printf("\nPromedio: %.2f",(float)acum/n);
    
    return (float)acum/n;
}

int extremos(int n, int *vec){
    int mini = vec[0];
    int maxi = vec[0];

    for(int i=0;i<n;i++){
        if(vec[i]<mini){
            mini = vec[i];
        }
        if(vec[i]>maxi){
            maxi = vec[i];
        }
    }
    printf("\nMaximo: %d\nMinimo: %d",maxi,mini);

    return 0;
}

int arriba_32(int n, int *vec){
    int cont = 0;
    for(int i=0;i<n;i++){
        if(vec[i]>32){
            cont++;
        }
    }
    printf("\nArriba de 32: %d",cont);
    return 0;
}

int arriba_prom(float prom, int n, int *vec){
    int cont=0;
    for(int i=0;i<n;i++){
        if(vec[i]>prom){
            cont++;
        }
    }
    printf("\nArriba del promedio: %d",cont);
    return 0;
}

int temps(int n, int* vec){
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d ",vec[i]);
    }
    return 0;
}