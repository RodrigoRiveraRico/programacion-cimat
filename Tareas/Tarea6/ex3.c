#include <stdio.h>
#include <stdlib.h>

/// @brief Búsqueda binaria iterativa
///
/// Recordar que búsqueda binaria necesita que el arreglo esté ordenado
/// @param datos Apuntador simple int. El arreglo.
/// @param ini int Índice inicial. Desde dónde se va a buscar (inclusivo).
/// @param end int Índice final. Hasta dónde se va a buscar (inclusivo).
/// @param buscar int Número a buscar.
/// @return int Índice en el arreglo donde está el número a buscar.
/// @retval -1 si el número a buscar no está en el arreglo.
int bin_iter(int *datos, int ini, int end, int buscar);

int main(void){

    // Tamaño de la lista
    int n;
    scanf("%d",&n);
    // Numero de preguntas
    int q;
    scanf("%d",&q);

    // Memoria dinámica para n enteros
    int *a = malloc(n*sizeof *a);
    if(!a){
        return 1;
    }
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    // Buscamos un número en particular.
    // BÚSQUEDA BINARIA ITERATIVA
    int numero;
    for(int i=0;i<q;i++){
        scanf("%d",&numero);
        if(bin_iter(a,0,n-1,numero)==-1){
            printf("NO\n");
            continue;
        }
        printf("YES\n");
    }

    free(a);
    return 0;
}

int bin_iter(int *datos, int ini, int end, int buscar){
    
    while(ini<=end){    // cuando ini > end los índices se cruzaron

        int mitad = ini + (end-ini)/2;

        if(datos[mitad]==buscar){
            return mitad;
        }
        else if(datos[mitad]<buscar){
            ini = mitad + 1;
        }
        else if(datos[mitad]>buscar){
            end = mitad-1;
        }
    }
    return -1;
}