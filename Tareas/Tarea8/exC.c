#include <stdio.h>
#include <stdlib.h>

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
    if(filtro_size == -1){
        free(arr);
        return 1;
    }
    printf("<%d>\n", filtro_size);
    
    for(int i=0;i<filtro_size;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    return 0;
}

/*int filtrar_unicos(int *arr, int n)
{  
    if(!arr){
        return 0;   // Arreglo vacío
    }

    // Índice auxiliar para colocar elementos únicos
    // Siempre se deja al primer elemento, entonces empezamos en el índice 1.
    int k=1;

    // Recorremos todo el arreglo, desde índice 1 al n-1
    for(int i=1;i<n;i++){

        // Revisamos si ya está el elemento actual. Desde índice 0 al k-1
        int j;
        for(j=0;j<k;j++){

            // Si ya está
            if(arr[j] == arr[i]){
                break;
            }
        }
        // Si no está: Colocamos el elemento en la posición k
        if(j==k){
            int temp = arr[k];
            arr[k] = arr[i];
            arr[i] = temp;
            k++;
        }
    }
    
    // realloc
    int *ptr_temp = realloc(arr, k * sizeof *ptr_temp);
    if(!ptr_temp){
        return -1;  // Salida de error
    }

    
    return k;   // Desde el índice 0 al k-1 hay k elementos únicos en orden de aparición.
}
*/

int filtrar_unicos(int **arr, int n)
{  
    if(!arr){
        return 0;   // Arreglo vacío
    }

    // Índice auxiliar para colocar elementos únicos
    // Siempre se deja al primer elemento, entonces empezamos en el índice 1.
    int k=1;

    // Recorremos todo el arreglo, desde índice 1 al n-1
    for(int i=1;i<n;i++){

        // Revisamos si ya está el elemento actual. Desde índice 0 al k-1
        int j;
        for(j=0;j<k;j++){

            // Si ya está
            if(arr[0][j] == arr[0][i]){
                break;
            }
        }
        // Si no está: Colocamos el elemento en la posición k
        if(j==k){
            int temp = arr[0][k];
            arr[0][k] = arr[0][i];
            arr[0][i] = temp;
            k++;
        }
    }

    /*for(int i=0;i<n;i++){
        printf("%d ", arr[0][i]);
    }*/
    
    // realloc
    int *ptr_temp = realloc(arr[0], k * sizeof *ptr_temp);
    if(!ptr_temp){
        return -1;  // Salida de error
    }

    for(int i=0;i<n;i++){
        printf("%d ", arr[0][i]);
    }


    free(arr[0]);
    printf("aqui se rompe");
    arr[0] = ptr_temp;
    
    
    return k;   // Desde el índice 0 al k-1 hay k elementos únicos en orden de aparición.
}