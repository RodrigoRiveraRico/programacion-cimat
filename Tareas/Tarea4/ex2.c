#include <stdio.h>

#define REPETIDOS 1
#define DISTINTOS 0

/** @brief Función que determina si hay elementos repetidos en un vector
 * 
 * @param v Apuntador a vector con n elementos no negativos
 * @param n Número de elementos en el vector
 * 
 * @return 0 si son distintos; 1 si hay al menos un número repetido
 */
int repetidos(unsigned *v, unsigned n);

/** @brief Bubble Sort.
 * 
 * El ordenamiento es in-place.
 * 
 * @param arr Apuntador a un arreglo 1D
 * @param N El número de elementos en el array
 * 
 * @return void
*/
void bu_sort(unsigned *arr, unsigned int N);

int main(void){
    
    // Total de números
    unsigned n;
    scanf("%u",&n);

    // Los n números
    unsigned vec[n];
    for(int i=0;i<n;i++){
        // printf("->");
        scanf("%u",&vec[i]);
    }

    // Imprimimos veredicto
    printf(repetidos(vec,n)==REPETIDOS ? "YES" : "NO");

    return 0;
}

int repetidos(unsigned *v, unsigned n){

    // Ordenamos de menor a mayor
    bu_sort(v,n);

    // Checamos si el siguiente es igual al anterior
    for(int i=1;i<n;i++){
        if(v[i]==v[i-1]){
            return REPETIDOS;
        }
    }
    return DISTINTOS;
}

void bu_sort(unsigned *arr, unsigned int N){

    int i,k;
    float temp;

    for(k=0;k<(N-1);k++){
        for(i=0;i<N-1-k;i++){
            if(arr[i]>arr[i+1]){
                temp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = temp;
            }
        }
    }
}