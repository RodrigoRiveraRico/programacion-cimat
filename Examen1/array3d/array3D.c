#include <stdlib.h>
#include <stdio.h>

/** 
 * @brief Estructura para representar un arreglo 3D
 */
typedef struct {
    double ***data;  /**< Arreglo plano con los datos */
    size_t   ndim;   /**< Número de dimensiones. Debe ser 3 */
    size_t   rows;   /**< Número de filas */
    size_t   cols;   /**< Número de columnas */
    size_t   lays;   /**< Número de capas */
} Array3d;

/* Reserva memoria para una arreglo 3D de tamaño nl x nr x nc
 * nl número de capas
 * nr número de renglones
 * nc número de columnas
 */
Array3d *array3d_alloc(int nl, int nr, int nc){
    // Reservamos memoria para la estructura 3D
    Array3d* array = (Array3d *) malloc(sizeof(Array3d));
    if(!array) {
        return NULL;
    } 
    // Reservamos memoria para nl capas
    array->data = (double ***) malloc(nl*sizeof(double **));
    if(array->data==NULL) {
        free(array);
        return NULL;
    }

    // Reservamos memoria para nl x nr renglones
    array->data[0] = (double **) malloc(nl*nr*sizeof(double *));
    if(array->data[0]==NULL){
        free(array->data);
        free(array);
        return NULL;
    }

    // Cada capa apunta al inicio de sus respectivos nr renglones
    for(int i=1;i<nl;i++){
        array->data[i] = array->data[i-1] + nr;
    }

    // Reservamos memoria para nl x nr x nc elementos
    array->data[0][0] = (double *) calloc(nl*nr*nc,sizeof(double)); // calloc inicializa en ceros
    if(array->data[0][0]==NULL){
        free(array->data[0]);
        free(array->data);
        free(array);
        return NULL;
    }
    // Cada renglón apunta al inicio de sus respectivos nc elementos
    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nr; j++) {

            if (i == 0 && j == 0)
                continue;

            array->data[i][j] = array->data[0][0] + (i * nr * nc) + (j * nc);
        }
    }
    array->ndim = 3;
    array->rows = nr;
    array->cols = nc;
    array->lays = nl;

    return array;
}

// Libera la memoria del arreglo 3D
void freeArray3d(Array3d *array){
    free(array->data[0][0]);
    free(array->data[0]);
    free(array->data);
    free(array);
}

/* Imprime la matriz
 * arreglo[i][j][k]
 * i capas
 * j renglones
 * k columnas
 */
void printArray3d(Array3d *array){
    size_t capas = array->lays;
    size_t renglones = array->rows;
    size_t columnas = array->cols;
    size_t i,j,k;
    for(i=0;i<capas;i++){
        for(j=0;j<renglones;j++){
            for(k=0;k<columnas;k++){
                printf("%f ",array->data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}