#include <iostream>
#include <cstdlib>  // Para malloc, calloc y free

/** 
 * @brief Estructura para representar un arreglo 3D tetraedro
 * 
 */
typedef struct {
    int ***data;     /**< Arreglo plano con los datos */
    size_t   ndim;   /**< Número de dimensiones. Debe ser 3 */
    size_t   lays;   /**< Número de capas */
} Array3d;

/**
 * @brief Reserva memoria para una arreglo 3D tetraedro.
 * 
 * Técnica de memoria contigua
 * @param nl Número de capas
 * @return Array3d* struct
 */
Array3d *array3d_alloc(int nl){
    // Reservamos memoria para la estructura 3D
    Array3d* array = (Array3d *) malloc(sizeof(Array3d));
    if(!array) {
        return NULL;
    } 
    // Reservamos memoria para nl capas
    array->data = (int ***) malloc(nl*sizeof(int **));
    if(array->data==NULL) {
        free(array);
        return NULL;
    }

    // Reservamos memoria para (nl)(nl+1)/2 renglones
    array->data[0] = (int **) malloc((nl*(nl+1)/2)*sizeof(int *));
    if(array->data[0]==NULL){
        free(array->data);
        free(array);
        return NULL;
    }

    // Cada capa apunta al inicio de sus respectivos renglones
    for(int i=1;i<nl;i++){
        array->data[i] = array->data[i-1] + i;
    }

    // Reservamos memoria para (nl)(nl+1)(nl+2)/6 elementos
    array->data[0][0] = (int *) calloc(nl*(nl+1)*(nl+2)/6, sizeof(int)); // calloc inicializa en ceros
    if(array->data[0][0]==NULL){
        free(array->data[0]);
        free(array->data);
        free(array);
        return NULL;
    }
    // Cada renglón apunta al inicio de sus respectivas columnas
    for (int i = 1; i < nl; i++) {
        array->data[i][0] = array->data[0][0] + (i*(i+1)*(i+2)/6);

        for (int j = 1; j <= i; j++) {
            array->data[i][j] = array->data[i][j-1] + j;
        }
    }
    array->ndim = 3;
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

// Llenar el arreglo 3D tetraedro con números secuenciales
void array3d_fill_sequential(Array3d* tetraedro, int nl){
    for(int i=0; i<(nl*(nl+1)*(nl+2)/6); i++){
        tetraedro->data[0][0][i] = i+1;
    }
}

// Llenar el arreglo siguiendo la fórmula matriz[i][j][k] = (i + 2j + 3k) (mod 10)
void array3d_fill_formula(Array3d* tetraedro, int nl){
    for(int i = 0; i < nl; i++){
        for(int j = 0; j <= i; j++){
            for(int k = 0; k <= j; k++){
                tetraedro->data[i][j][k] = (i+2*j+3*k) % 10;
            }
        }
    }
}

// Sumar todos los elementos del arreglo 3D
long suma_elementos(Array3d* tetraedro, int nl){
    long suma = 0;
    for(int i=0; i<(nl*(nl+1)*(nl+2)/6); i++){
        suma += tetraedro->data[0][0][i];
    }
    return suma;
}

int main(){

    // Número de capas
    int nl;
    std::cin >> nl;

    Array3d *tetraedro = array3d_alloc(nl);

    array3d_fill_formula(tetraedro, nl);

    // Imprimir el arreglo 3D de forma plana
    // for(int i=0; i<(nl*(nl+1)*(nl+2)/6); i++){
    //     std::cout << tetraedro->data[0][0][i] << " ";
    // }
    // std::cout << std::endl;

    std::cout << suma_elementos(tetraedro, nl);

    freeArray3d(tetraedro);

    return 0;
}