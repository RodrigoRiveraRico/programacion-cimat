#include <stdio.h>
#include <stdlib.h>

int main(void){
    unsigned int N,M;
    int **A,**B;
    long long int traza; // %lld

    scanf("%u",&N);
    scanf("%u",&M);

    // Matriz A
    A = (int **)malloc(N*sizeof(int *));
    if(!A){
        printf("\nNo hay memoria suficiente para guardar A.");
        return 1;
    }
    for(int i=0;i<N;i++){
        A[i]=(int *)malloc(M*sizeof(int));
        if(!A[i]){
            printf("\nNo hay memoria suficiente para guardar las columnas de A.");
            for(int k=0;k<i;k++){
                free(A[k]);
            }
            free(A);
            return 1;
        }
    }

    // Matriz B
    B = (int **)malloc(M*sizeof(int *));
    if(!B){
        printf("\nNo hay memoria suficiente para guardar B.");
        for(int k=0;k<N;k++){
            free(A[k]);
        }
        free(A);
        return 1;
    }
    for(int i=0;i<M;i++){
        B[i]=(int *)malloc(N*sizeof(int));
        if(!B[i]){
            printf("\nNo hay memoria suficiente para guardar las columnas de B.");
            for(int k=0;k<i;k++){
                free(B[k]);
            }
            free(B);
            for(int k=0;k<N;k++){
                free(A[k]);
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

    // Elementos de B
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&B[i][j]);
        }
    }

    // Calculamos la traza de A x B
    traza = 0;
    for(int i=0;i<N;i++){
        for(int k=0;k<M;k++){
            traza += (long long int)A[i][k] * B[k][i];   // Evitamos overflow del producto int * int
        }
    }
    printf("\n%lld",traza);

    // Liberar memoria
    for(int k=0;k<N;k++){
        free(A[k]);
    }
    free(A);

    for(int k=0;k<M;k++){
        free(B[k]);
    }
    free(B);
    return 0;
}