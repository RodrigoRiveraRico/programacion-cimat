#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
// #define VACIO 2

// Falta ajustar la memoria de cada conjunto calculado.

int *Union(int *A, int n, int *B, int m);
int *Inter(int *A, int n, int *B, int m);
int *Diff(int *A, int n, int *B, int m);
int copiar(int *A, int n, int *C);

int main(void){

    int n,m;

    scanf("%d",&n);

    int *A = NULL;

    if(n > 0){
        A = malloc(n*sizeof *A);

        if(!A){
            return ERROR;
        }

        for(int i=0;i<n;i++){
            scanf("%d",&A[i]);
        }
    }

    scanf("%d",&m);

    int *B = NULL;

    if(m > 0){
        B = malloc(m*sizeof *B);

        if(!B){
            free(A);
            return ERROR;
        }

        for(int i=0;i<m;i++){
            scanf("%d",&B[i]);
        }
    }

    int *C = NULL;

    C = Union(A,n,B,m);
    free(C);

    C = Inter(A,n,B,m);
    free(C);

    C = Diff(A,n,B,m);
    free(C);

    free(A);
    free(B);

    return OK;
}


int copiar(int *A, int n, int *C){

    if(!A && n > 0){
        return ERROR;
    }

    if(!C){
        return ERROR;
    }

    for(int i=0;i<n;i++){
        C[i] = A[i];
    }

    return OK;
}


int *Union(int *A, int n, int *B, int m){

    if(n == 0 && m == 0){ //Ambos son vacios
        printf("\n");
        return NULL;
    }

    int *C = malloc((n+m)*sizeof *C); // A lo más son n+m elementos en la unión.

    if(!C){
        return NULL;
    }

    int p = 0;

    // A es vacío: A U B = B
    if(n == 0){

        for(int i=0;i<m;i++){
            C[p] = B[i];
            p++;
        }
    }

    // B es vacío: A U B = A
    else if(m == 0){

        if(!copiar(A,n,C)){
            free(C);
            return NULL;
        }

        p = n;
    }

    // Ningún conjunto es vacío
    else{

        if(!copiar(A,n,C)){
            free(C);
            return NULL;
        }

        p = n;

        for(int j=0;j<m;j++){

            int i;

            for(i=0;i<p;i++){

                if(B[j] == C[i]){
                    break; // B_j ya está
                }
            }

            if(i == p){
                C[p] = B[j]; // Guardamos B_j
                p++; // Avanzamos posición
            }
        }
    }

    for(int k=0;k<p;k++){

        if(k > 0){
            printf(" ");
        }

        printf("%d",C[k]);
    }

    printf("\n");

    return C;
}


int *Inter(int *A, int n, int *B, int m){

    // A lo más son min(n,m) elementos.
    int tamano = n <= m ? n : m;

    if(tamano == 0){
        printf("\n");
        return NULL;
    }

    int *C = malloc(tamano*sizeof *C);

    if(!C){
        return NULL;
    }

    int *p = C;

    for(int j=0;j<n;j++){

        for(int i=0;i<m;i++){

            if(A[j] == B[i]){

                *p = A[j];
                p++;

                break;
            }
        }
    }

    if(p == C){

        free(C);

        printf("\n"); // Intersección vacía

        return NULL;
    }

    for(int k=0;k<(p-C);k++){

        if(k > 0){
            printf(" ");
        }

        printf("%d",C[k]);
    }

    printf("\n");

    return C;
}


int *Diff(int *A, int n, int *B, int m){

    if(n == 0){ // Conjunto vacío
        printf("\n");
        return NULL;
    }

    int *C = malloc(n*sizeof *C); // A lo más el tamaño es el de A

    if(!C){
        return NULL;
    }

    int *p = C;
    int flag;

    for(int j=0;j<n;j++){

        flag = 0;

        for(int i=0;i<m;i++){

            if(A[j] == B[i]){

                flag = 1;

                break;
            }
        }

        if(flag == 0){

            *p = A[j];
            p++;
        }
    }

    if(p == C){

        free(C);

        printf("\n"); // Igualdad de conjuntos

        return NULL;
    }

    for(int k=0;k<(p-C);k++){

        if(k > 0){
            printf(" ");
        }

        printf("%d",C[k]);
    }

    printf("\n");

    return C;
}