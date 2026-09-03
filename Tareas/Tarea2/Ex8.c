#include <stdio.h>
#include <stdlib.h>

int main(void){

    int N,M,P,Q;
    int **A, **B;

    // Memoria dinámica para matriz A
    scanf("%d",&N);
    scanf("%d",&M);

    A = (int **) malloc(N*sizeof(int *));
    if(!A){
        printf("\nNo hay memoria para la matriz A");
        return 1;
    }
    for(int i=0;i<N;i++){
        A[i] = (int *)malloc(M*sizeof(int));
        if(!A[i]){
            printf("\nNo hay memoria para las columnas de la matriz A");
            for(int j=0;j<i;j++){
                free(A[i]);
            }
            free(A);
            return 1;
        }
    }

    // Elementos de A
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d",&A[i][j]);
        }
    }

    // Memoria dinámica para matriz B
    scanf("%d",&P);
    scanf("%d",&Q);
    
    B = (int **) malloc(P*sizeof(int *));
    if(!B){
        printf("\nNo hay memoria para la matriz B");
        return 1;
    }
    for(int i=0;i<P;i++){
        B[i] = (int *)malloc(Q*sizeof(int));
        if(!B[i]){
            printf("\nNo hay memoria para las columnas de la matriz B");
            for(int j=0;j<i;j++){
                free(B[i]);
            }
            free(B);
            return 1;
        }
    }

    // Elementos de B
    for(int i=0;i<P;i++){
        for(int j=0;j<Q;j++){
            scanf("%d",&B[i][j]);
        }
    }

    // Diferencia en dimensiones de las matrices
    if(P!=M || Q!=N){
        printf("\nNO");
        return 0;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(A[i][j]!=B[j][i]){
                printf("\nNO");
                return 0;
            }
        }
    }

    printf("\nSI");

    // Liberar A
    for(int j=0;j<N;j++){
        free(A[j]);
    }
    free(A);

    // Liberar B
    for(int j=0;j<P;j++){
        free(B[j]);
    }
    free(B);

    return 0;
}