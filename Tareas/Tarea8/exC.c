#include <stdio.h>
#include <stdlib.h>

#define ERROR_REALLOC -1

// int filtrar_unicos(int *arr, int n);
int filtrar_unicos(int **arr, int n);

int main(void){

    // Cantidad de elementos en el arreglo
    int N;
    scanf("%d", &N);

    // Creación del arreglo
    int *arr = malloc(N * sizeof *arr);
    if(!arr){
        return 1;
    }

    // Elementos del arreglo
    for(int i=0;i<N;i++){
        scanf("%d", &arr[i]);
    }

    // Filtro
    int filtro_size = filtrar_unicos(&arr, N);
    if(filtro_size == ERROR_REALLOC){
        free(arr);
        return 1;
    }
    // Número de números únicos.
    printf("%d\n", filtro_size);
    
    // Los números únicos
    for(int i=0;i<filtro_size;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    return 0;
}

int filtrar_unicos(int **arr, int n)
{  
    if(n==0){   // Lista vacía
        return 0;
    }

    // Puntero auxiliar para movernos en el arreglo
    int *aux = *arr;

    // Índice auxiliar para colocar elementos únicos
    // Siempre se deja al primer elemento, entonces empezamos en el índice 1.
    int k=1;

    // Recorremos todo el arreglo, desde índice 1 al n-1
    for(int i=1;i<n;i++){

        // Revisamos si ya está el elemento actual. Desde índice 0 al k-1
        int j;
        for(j=0;j<k;j++){

            // Si ya está
            if(aux[j] == aux[i]){
                break;
            }
        }
        // Si no está: Colocamos el elemento en la posición k
        if(j==k){
            int temp = aux[k];
            aux[k] = aux[i];
            aux[i] = temp;
            k++;
        }
    }
    
    // realloc modifica el tamaño de la memoria de forma segura.
    int *ptr_temp = realloc(aux, k * sizeof *ptr_temp);
    if(!ptr_temp){
        // Si realloc falla 'aux' sigue siendo válido.
        // No lo liberamos aquí. La liberación se hace en main.
        return ERROR_REALLOC;
    }

    // free(aux) NO VA AQUÍ! realloc ya se encargó de gestionar esa memoria.
    /*
    Cuando se utiliza realloc(aux, ...), la función hace una de dos cosas de forma automática:
    1. Reutiliza el bloque de memoria original de aux y solo cambia su tamaño (en cuyo caso ptr_temp tendrá la misma dirección que aux).
    2. Reserva un nuevo bloque de memoria en otro lado, copia los datos viejos al nuevo lugar y libera automáticamente el bloque original de aux.
    */

    // Asignamos el nuevo bloque al puntero original del main
    *arr = ptr_temp;

    return k;   // Desde el índice 0 al k-1 hay k elementos únicos en orden de aparición.
}