#include <stdio.h>
#include <stdlib.h>

int main(void){
    unsigned int M,N;
    int **A, **B;

    scanf("%u",&M);
    scanf("%u",&N);

    // Matriz A
    A = (int **)malloc(M*sizeof(int *));
    if(!A){
        printf("\nNo hay memoria para la matriz A.");
        return 1;
    }
    for(int i=0;i<M;i++){
        A[i] = (int *)malloc(N*sizeof(int));
        if(!A[i]){
            printf("\nNo hay memoeria para las columnas de A.");
            for(int j=0;j<i;j++){
                free(A[j]);
            }
            free(A);
            return 1;
        }
    }

    // Matriz B
    B = (int **)malloc(M*sizeof(int *));
    if(!B){
        printf("\nNo hay memoria para la matriz B.");
        return 1;
    }
    for(int i=0;i<M;i++){
        B[i] = (int *)malloc(N*sizeof(int));
        if(!B[i]){
            printf("\nNo hay memoeria para las columnas de B.");
            for(int j=0;j<i;j++){
                free(B[j]);
            }
            free(B);
            return 1;
        }
    }

    // Guardamos los elementos de A
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&A[i][j]);
        }
    }

    // Guardamos los elementos de B
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&B[i][j]);
        }
    }

    // Calculamos la matriz C = A + B
    for(int i=0;i<M;i++){
        printf("\n");
        for(int j=0;j<N;j++){
            printf("%d ",A[i][j]+B[i][j]);
        }
    }

    // Liberar memoria A
    for(int j=0;j<M;j++){
        free(A[j]);
    }
    free(A);

    // Liberar memoria B
    for(int j=0;j<M;j++){
        free(B[j]);
    }
    free(B);

    return 0;
}