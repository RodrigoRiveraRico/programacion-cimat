#include <stdlib.h>
#include <stdio.h>

/// Función inicializadora: Recibe como parámetros un apuntador simple de tipo int, 
/// las dimensiones del cuboide 
/// y un valor entero a. 
/// La función tiene que llenar el cuboide completo con el valor a usando el método contiguo descrito previamente.
void inicializadora(int *datos, int h, int m, int n, int a);

/// Construcción del cuboide
/// Entradas (i,j,k)
/// 0 <= i <= h
/// 0 <= j < m
/// 0 <= k < n
int ***contruir_cuboide(int h, int m, int n, int a);

/// Función diagonal: Recibe como parámetros un apuntador triple de tipo int y las dimensiones del cuboide. 
/// Llena la diagonal del cuboide con 1s (elementos C[i][j][k] donde (i=j=k).
void diagonal(int ***cubo, int h, int m, int n);

/// Función que imprime el cuboide: 
/// Recibe como parámetros un apuntador triple de tipo int y las dimensiones del cuboide. 
/// Imprime el cuboide por "capas" respetando cada una de las dimensiones.
void printCubo(int ***cubo,int h,int m,int n);

int main(void){

    int h,m,n;
    int a;

    scanf("%d",&h);
    scanf("%d",&m);
    scanf("%d",&n);
    scanf("%d",&a);

    int ***mi_cubo = contruir_cuboide(h,m,n,a);
    if(!mi_cubo){
        return 1;
    }

    diagonal(mi_cubo,h,m,n);

    printCubo(mi_cubo,h,m,n);
    
    return 0;
}

void inicializadora(int *datos, int h, int m, int n, int a){

    int total_elementos = h*m*n;

    for(int i=0;i<total_elementos;i++){
        datos[i]=a;
    }
}

int ***contruir_cuboide(int h, int m, int n, int a){

    int ***cubo = (int ***)malloc(h*sizeof(int **));
    if(!cubo){
        return NULL;
    }

    // Bloque de h*m punteros a int
    cubo[0] = (int **)malloc(h*m*sizeof(int *));
    if(!cubo[0]){
        free(cubo);
        return NULL;
    }

    // Hacer que cada capa apunte a sus m filas 
    for(int i=1;i<h;i++){
        cubo[i] = cubo[i-1] + m;
    }

    // Bloque de TODOS los elementos int
    cubo[0][0] = malloc(h*m*n*sizeof(int));
    if(!cubo[0][0]){
        free(cubo[0]);
        free(cubo);
        return NULL;
    }

    // Conectar todas las filas con el bloque de int
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < m; j++) {

            if (i == 0 && j == 0)
                continue;

            cubo[i][j] = cubo[0][0] + (i * m * n) + (j * n);
        }
    }

    int * datos = cubo[0][0];
    inicializadora(datos,h,m,n,a);

    return cubo;
}

void diagonal(int ***cubo, int h, int m, int n){
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0; k<h;k++){
                if(i==j && j==k){
                    cubo[i][j][k]=1;
                }
            }
        }
    }
}

void printCubo(int ***cubo, int h, int m, int n){
    for(int k=0;k<h;k++){
        for(int j=0;j<m;j++){
            for(int i=0; i<n;i++){
                printf("%d ",cubo[k][j][i]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
