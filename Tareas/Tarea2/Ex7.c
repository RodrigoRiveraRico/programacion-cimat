#include <stdio.h>
#include <stdlib.h>

int main(void){

    int **mat;
    int N,M;
    int suma;

    scanf("%d",&N);
    scanf("%d",&M);
        
    mat = (int **)malloc(N*sizeof(int *));

    if(!mat){
        printf("\nNo fue posible asignar memoria a la matriz.");
        free(mat);
        return 1;
    }

    for(int i=0;i<N;i++){
        mat[i] = (int *)malloc(M*sizeof(int));
        if(!mat[i]){
            printf("\nNo fue posible asignar memoria a columnas.");
            for(int j=0;j<i;j++){
                free(mat[i]);
            }
            free(mat);
            return 1;
        }
    }
    
    // Guardamos los elementos de la matriz
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d",&mat[i][j]);
        }
    }

    // Revisamos filas
    for(int i=0;i<N;i++){
        suma = 0;
        for(int j=0;j<M;j++){
            suma+=mat[i][j];
        }
        if(suma%2!=0){
            printf("\nNO");
            return 0;
        }
    }

    // Revisamos columnas
    for(int j=0;j<M;j++){
        suma = 0;
        for(int i=0;i<N;i++){
            suma+=mat[i][j];
        }
        if(suma%2==0){
            printf("\nNO");
            return 0;
        }
    }

    printf("\nSI");

    return 0;
}