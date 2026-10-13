#include <stdio.h>
#include <stdlib.h>

/** 
 * @brief Estructura para representar un arreglo 2D
 */
typedef struct {
    int **data;   /**< Arreglo plano con los datos */
    size_t   ndim;   /**< Número de dimensiones. Debe ser 2 */
    size_t   rows;   /**< Número de filas */
    size_t   cols;   /**< Número de columnas */
} Array2d;


// Reserva memoria para una arreglo 2D de tamaño nr x nc
Array2d *array2d_alloc(int nr, int nc);

// Libera la memoria del arreglo bidimensional
void freeArray2d(Array2d *array);

// Imprime la fila i-esima del arreglo 
void printRow(int **data, int i, int nc, const char *format, int nshow);

// Imprime en la consola las entradas del arraglo 2D
void printArray2d(Array2d *array, const char *format, int nshow);

int main(void){

    // Dimension (2n+1) x (2n+1)
    int n;

    // Cantidad de coordenadas
    int  k;
    scanf("%d %d",&n, &k);

    // Memoria contigua
    Array2d *territorio = array2d_alloc(2*n+1, 2*n+1);
    if(!territorio){return 1;}

    // Visualización de la inicialización (todo es cero)
    // printArray2d(territorio, " %d ", 2*n+1);
    // printf("\n");

    // Nuevo conjunto de apuntadores. Cada apuntador renglón apuntará la columna de la mitad
    int **ptr_to_middle = malloc(territorio->rows * sizeof *ptr_to_middle);
    if(!ptr_to_middle){
        freeArray2d(territorio);
        return 1;
    }
    for(int i=0; i<territorio->rows; ++i) 
        ptr_to_middle[i] = territorio->data[i] + (2*n+1) / 2;

    // Apuntador al centro de la matriz. Ya podemos movernos con índices negativos.
    int **centro = &ptr_to_middle[(2*n+1) / 2];

    // Lectura de cada zona (x,y) respecto al centro
    for(int i=0;i<k;i++){
        float x;
        float y;
        scanf("%f %f",&x, &y);

        centro[(int)y][(int)x]++;

        if(centro[(int)y][(int)x] == 17){
            printf("Zona[%d][%d]: Notificacion\n",(int)y,(int)x);
        }
        else if(centro[(int)y][(int)x] == 19){
            printf("Zona[%d][%d]: Equipo\n",(int)y, (int)x);
            centro[(int)y][(int)x] = 0;
        }
    }

    // Visualización al final del algoritmo
    // printArray2d(territorio, " %d ", 2*n+1);


    freeArray2d(territorio);
    return 0;
}

/*
* Reserva memoria para un arreglo 2D de tamaño nr x nc
* calloc() asegura que cada byte del bloque asignado contenga el valor 0
*/
Array2d *array2d_alloc(int nr, int nc) {
    // Reservamos memoria
    Array2d* array = (Array2d *) malloc(sizeof(Array2d));
    if(!array) {
        return NULL;
    }
    array->data = malloc( (nr)*sizeof(*array->data));
    if(array->data==NULL) {
        free(array);
        return(NULL);
    }
    array->data[0] = calloc(nr*nc, sizeof(array->data[0]));
    if(array->data[0]==NULL) {
        free(array->data);
        free(array);
        return(NULL);
    }
    array->rows = nr;
    array->cols = nc;
    array->ndim = 2;
    for(int i=1; i<nr; ++i) 
        array->data[i] = array->data[i-1] + nc;
    return(array);
}

// Libera la memoria del arreglo bidimensional
void freeArray2d(Array2d *array) {
    free(array->data[0]);
    free(array->data);
    free(array);
}

void printArray2d(Array2d *array, const char *format, int nview) {
    int i, j, nr=array->rows, nc=array->cols; 

    if((2*nview+1)<nr ) {
        for(i=0; i<nview; ++i) 
            printRow(array->data, i, nc, format, nview);
        printf("... \n");
        for(i=nr-nview; i<nr; ++i) 
            printRow(array->data, i, nc, format, nview);
    }
    else {
        for(i=0; i<nr; ++i) 
            printRow(array->data, i, nc, format, nview);
    }

}

// Imprime la fila i-esima del arreglo 
void printRow(int **data, int i, int nc, const char *format, int nview) {
    printf("[");
    if((2*nview+1)<nc) {
        for(int j=0; j<nview; ++j) 
            printf(format, data[i][j]);
        printf(" ... ");
        for(int j=nc-nview; j<nc; ++j) 
            printf(format, data[i][j]);
    }
    else {
        for(int j=0; j<nc; ++j) 
            printf(format, data[i][j]);
    }
    printf("]\n");
}