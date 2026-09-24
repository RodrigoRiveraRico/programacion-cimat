#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define FALLO 1;

typedef struct{
    int n;      /*< Tamaño de la matriz*/
    int *dat;   /*< Elementos de la matriz vistos en un arreglo 1D*/  
}matriz_cuadrada;

// Cálculo de la traza de una matriz cuadrada con sus elementos representados en 1D
int traza(const matriz_cuadrada *A);
// Función de comparación para qsort
int comparar_trazas(const void *a, const void *b);
// Imprimir matriz cuadrada con  sus elementos representados en 1D
void imprimirMatriz(matriz_cuadrada *A);

int main(void){

    int num_matrices;
    scanf("%d",&num_matrices);

    matriz_cuadrada *lista_de_matrices = malloc(num_matrices * sizeof *lista_de_matrices);
    if(!lista_de_matrices){
        return FALLO;
    }
    
    // Iteración sobre cada una de las matrices
    // Creación de cada matriz
    for(int i=0;i<num_matrices;i++){
        int tamano;
        scanf("%d",&tamano);
        lista_de_matrices[i].n = tamano;
        lista_de_matrices[i].dat = malloc(tamano*tamano * sizeof *lista_de_matrices[i].dat);
        if(!lista_de_matrices[i].dat){
            for(int j=0;j<i;j++){
                free(lista_de_matrices[j].dat);
            }
            free(lista_de_matrices);
            return FALLO;
        }
        // Llenamos la martriz
        for(int j=0;j<tamano*tamano;j++){
            scanf("%d",&lista_de_matrices[i].dat[j]);
        }
    }

    // Ordenar según la traza. De menor a mayor
    qsort(lista_de_matrices,num_matrices,sizeof *lista_de_matrices,comparar_trazas);

    // Imprimir matrices ordenadas de manor a mayor traza
    for(int i=0;i<num_matrices;i++){
        imprimirMatriz(&lista_de_matrices[i]);
    }

    // Liberar memoria
    for(int j=0;j<num_matrices;j++){
        free(lista_de_matrices[j].dat);
    }
    free(lista_de_matrices);
    return OK;
}

int comparar_trazas(const void *a, const void *b){
    // qsort pasa un puntero al elemento del arreglo. 
    // Como el arreglo guarda struct 'matriz_cuadrada', 'a' y 'b' se castean a 'matriz_cuadrada *'
    
    const matriz_cuadrada *MatrizA = (const matriz_cuadrada *)a;    // Renombramos
    const matriz_cuadrada *MatrizB = (const matriz_cuadrada *)b;    // Renombramos
    
    int trazaA = traza(MatrizA);    // Traza de A
    int trazaB = traza(MatrizB);    // Traza de B

    // Regla de ordenamiento
    if(trazaA > trazaB)  return 1;
    if(trazaA < trazaB)  return -1;
    if(trazaA == trazaB) return 0;
}

int traza(const matriz_cuadrada *A){
    int traza = 0;
    int n = A->n;
    for(int i=0;i<n;i++){
        traza += A->dat[(n+1)*i];
    }
    return traza;
}

void imprimirMatriz(matriz_cuadrada *A){
    int n = A->n;
    for(int i=0;i<n*n;i++){
        if(i%n==0){
            printf("\n");
        }
        printf("%d ",A->dat[i]);
    }
    printf("\n");
}