
/* Sintaxis de qsort

void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));

> base: Puntero al primer elemento del arreglo que se va a ordenar.
> nitems: Número de elementos que tiene el arreglo.
> size: El tamaño en bytes de cada elemento del arreglo (se obtiene con sizeof).
> compar: Puntero a la función de comparación que define el orden.

>>> Reglas de la función de comparación.
La función de comparación recibe dos punteros (const void *) y debe devolver:
> Un número menor a 0 si el primer elemento va antes que el segundo.
> 0 si ambos elementos son iguales.
> Un número mayor a 0 si el primer elemento va después del segundo.
*/

#include <stdio.h>
#include <stdlib.h>

// Función de comparación para enteros (orden ascendente)
int comparar_enteros(const void *a, const void *b) {
    int int_a = *((const int *)a);  // Primero casteo del apuntador a su verdadero tipo de dato, luego asignamos el valor para la comparación.
    int int_b = *((const int *)b);
    
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int main() {
    int numeros[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    qsort(numeros, n, sizeof(int), comparar_enteros);

    printf("Arreglo ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
}
