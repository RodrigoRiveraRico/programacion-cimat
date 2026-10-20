#include <stdio.h>

// Definición de la estructura para cada objeto
typedef struct {
    char name;
    int size;
    int val;
} Item;

// Número total de tipos de objetos disponibles
#define N 5

// Arreglo global que almacena los objetos
Item items[N];

/* Función recursiva para resolver el problema de la mochila (Knapsack)
 * > Si la capacidad `cap` es menor que el tamaño del objeto más pequeño, la condición `(space = cap - items[i].size) >= 0` nunca se cumplirá. 
 * El ciclo terminará, no entrará a ningún `if`, y la función devolverá `max = 0`.
 * > Itera a través de los 5 objetos (i desde 0 hasta 4) para intentar meter cada uno en la mochila.
 * > `if ( (space = cap - items[i].size) >= 0 )` verifica si el objeto actual cabe en el espacio disponible. Si cabe, calcula el espacio restante (`space`).
 * > `if ( (t = knap(space) + items[i].val) > max )` realiza una llamada recursiva con el espacio restante, 
 * le suma el valor del objeto actual y lo compara con el valor máximo encontrado hasta el momento (`max`). 
 * Si es mayor, actualiza `max` y registra el índice del objeto en `maxi`.
 * > Devuelve el valor máximo total que se puede acumular con esa capacidad.
 */
int knap(int cap) {
    int i, space, max, t;
    int maxi = -1;

    for (i = 0, max = 0; i < N; i++) {
        if ((space = cap - items[i].size) >= 0) {
            if ((t = knap(space) + items[i].val) > max) {
                max = t;
                maxi = i;
            }
        }
    }
    return max;
}

int main() {
    // Inicialización de los 5 objetos con datos de prueba (Nombre, Tamaño/Peso, Valor)
    items[0] = (Item){'A', 2, 3};   // Objeto A: tamaño 2, valor 3
    items[1] = (Item){'B', 3, 4};   // Objeto B: tamaño 3, valor 4
    items[2] = (Item){'C', 4, 5};   // Objeto C: tamaño 4, valor 5
    items[3] = (Item){'D', 5, 8};   // Objeto D: tamaño 5, valor 8
    items[4] = (Item){'E', 9, 10};  // Objeto E: tamaño 9, valor 10

    // Capacidad máxima de la mochila para la prueba
    int capacidad = 4;
    
    // Ejecución del algoritmo
    int valor_maximo = knap(capacidad);

    // Impresión del resultado
    printf("--- Problema de la Mochila ---\n");
    printf("Capacidad de la mochila: %d\n", capacidad);
    printf("Valor maximo obtenido: %d\n", valor_maximo);

    return 0;
}
