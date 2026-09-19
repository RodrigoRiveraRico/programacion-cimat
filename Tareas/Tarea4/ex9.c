#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERR_MEMORY 2

/// @brief Estructura de matriz
typedef struct{
    int **data;   ///< La matriz
    int n;          ///< Número de filas
    int m;          ///< Número de columnas
}Matrix;

/// @brief Recibe las dimensiones de la matriz y te devuelve una instancia de Matrix con memoria reservada.
/// @param n Filas 
/// @param m Columnas
/// @return Matrix
Matrix *creaMatrix(int n, int m);

/// @brief Recibe una matriz y libera la memoria asociada.
/// @param  matriz La matriz
void freeMatrix(Matrix *matriz);

/// @brief Recibe una matriz y devuelve otra matriz que representa su transpuesta.
/// @param matriz La matriz
/// @return Matrix Transpuesta de la matriz recibida
Matrix *transpose(Matrix *matriz);

/// @brief Recibe una matriz cuadrada y calcula su transpuesta dentro de la misma matriz.
/// @param matriz La matriz
void transpose_inplace(Matrix *matriz);

/// @brief Recibe una matriz y la imprime a la salida estándar
/// @param matriz La matriz
void printMatrix(Matrix *matriz);

int main(void){
    // Leer tamaño de la matriz
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);

    Matrix *mi_matriz = creaMatrix(n,m);
    if(!mi_matriz){return ERR_MEMORY;}

    // Elementos de la matriz
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&(mi_matriz->data[i][j]));
        }
    }

    if(n==m){
        transpose_inplace(mi_matriz);
        printMatrix(mi_matriz);
    }
    else{
        Matrix *mi_transpuesta = transpose(mi_matriz);
        if(!mi_transpuesta){
            freeMatrix(mi_matriz);    
            return ERR_MEMORY;
        }
        printMatrix(mi_transpuesta);
        freeMatrix(mi_transpuesta);
    }

    freeMatrix(mi_matriz);
    return OK;
}

Matrix *creaMatrix(int n, int m){
    // Memoria para la estructura
    Matrix *matriz = malloc(sizeof *matriz);
    if(!matriz){
        return NULL;
    }
    matriz->n = n;
    matriz->m = m;

    // Memoria para los apuntadores de filas
    matriz->data = malloc(n*sizeof *(matriz->data));
    if(!matriz->data){
        free(matriz);
        return NULL;
    }

    // Bloque de memoria para los elementos de la matriz
    matriz->data[0] = malloc(n*m*sizeof **(matriz->data));
    if(!matriz->data[0]){
        free(matriz->data);
        free(matriz);
        return NULL;
    }

    // Asignación de bloques de memoria a la filas
    for(int i=1;i<n;i++){
        matriz->data[i] = matriz->data[i-1] + m;
    }

    return matriz;
}

void freeMatrix(Matrix *matriz){
    if (!matriz) return; // Validación de seguridad
    if (matriz->data) {
        free(matriz->data[0]);
        free(matriz->data);
    }
    free(matriz);
}

Matrix *transpose(Matrix *matriz){
    int n = matriz->n;
    int m = matriz->m;
    Matrix *transpuesta = creaMatrix(m, n);
    if(!transpuesta){return NULL;}

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            transpuesta->data[j][i] = matriz->data[i][j];
        }
    }

    return transpuesta;
}

void transpose_inplace(Matrix *matriz){
    int n = matriz->n;
    int m = matriz->m;

    if(n!=m){return;}

    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            int temp;
            temp = matriz->data[j][i];
            matriz->data[j][i] = matriz->data[i][j];
            matriz->data[i][j] = temp;
        }
    }
}

void printMatrix(Matrix *matriz){
    int n = matriz->n;
    int m = matriz->m;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",matriz->data[i][j]);
        }
        printf("\n");
    }
}
