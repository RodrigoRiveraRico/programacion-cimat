#include <stdio.h>
#include <stdlib.h>

/// @brief Tipo dato que se almacena en el nodo
typedef int item;

/// @brief Estructura de nodo para árbol
typedef struct Nodo
{
    item boolean;     // Dato almacenado en el nodo. Lo llamamos boolean para indicar que serán ceros y unos.
    struct Nodo *izq; // Nodo hijo izquierda.
    struct Nodo *der; // Nodo hijo derecha.

} nodo;

/* Árbol a construir

             root
           /      \
          1        0          ← variable x0
        /  \      /  \
       1    0    1    0       ← variable x1
      / \  / \  / \  / \
      1 0  1 0  1 0  1 0      ← variable x2
      . .  . .  . .  . .
      . .  . .  . .  . .
      . .  . .  . .  . .
*/

/** @brief Función que crea un árbol binario recursivamente.
 *
 * El nodo raíz guarda un valor a conveniencia.
 * Para los demás nodos: el nodo hijo izquierdo tendrá 1, el nodo hijo derecho tendrá 0
 *
 * La idea del árbol construido es la representación de una tabla de verdad; cada nivel después de la raíz representa una variable booleana.
 * El recorrido hacia las hojas son las diferentes combinaciones de las variables booleanas.
 * @param dim int Profundidad que tendrá el árbol. Número de variables + raíz.
 * @param valor item Dato del nodo
 * @return nodo * Nodo raíz del árbol. El valor almacenado en este nodo es a conveniencia.
 * @note Se construye un árbol binario perfecto.
 */
nodo *crearArbol(int dim, item valor);

/** @brief Libera memoria dinámica de un árbol binario. Función recursiva.
 *
 * @param root nodo * raíz del árbol.
 */
void freeArbol(nodo *root);

/*
Árbol sobre el que trabaja la función `evaluar`.

          1      ← x0   (Nivel 0)
        /  \
       1    0    ← x1   (Nivel 1)
      / \  / \
      1 0  1 0   ← x2   (Nivel 2)
      . .  . .
      . .  . .
      . .  . .
*/

/**
 *  @brief Función recursiva para evaluar expresiones lógicas en un árbol binario perfecto.
 *
 * La Verdad está definida con un paso de ignición: y = x_{0} ∧ ¬x_{1}
 *
 * Despues (propagación):
 *
 * Para i = 1 hasta d-2: y = y ⊕ ((x_{i-1} ∨ ¬x_{i}) ∧ ¬x_{i+1})
 *
 * Si y = 1 entonces La Verdad = sum_{i=0}^{d-1} x_{i}
 *
 * Si y = 0 entonces La Verdad = 0
 *
 * @param root nodo * El nodo sobre el cual se empieza la evaluación. Raíz del árbol.
 * @param nivel int Nivel actual en el árbol.
 * @param d int Número de variables booleanas.
 * @param x_prev int Valor de nodo.
 * @param x_actual int Valor de nodo.
 * @param y int Resultado de operación lógica.
 * @param la_verdad int Valor acumulado del resultado de las operaciones lógicas.
 * @return int Evaluación del árbol.
 * @note Cada nodo (raíz incluida) debe tener como valor 0 u 1
 */
int evaluar(nodo *root, int nivel, int d,
            int x_prev, int x_actual,
            int y, int la_verdad);

int main(void)
{
    // Cantidad de variables booleanas
    unsigned d;
    scanf("%u",&d);

    // d variables booleanas + 1 raíz.
    // El valor de la raíz será la cantidad de variables booleanas. Esto solo por poner un valor a la raíz.
    item valor_raiz = d;
    nodo *root = crearArbol(d + 1, valor_raiz);
    if (!root)
    {
        return 1;
    }

    /////////////// EVALUACIÓN ///////////////
    int nivel = 0;     // Empezamos en el nivel 0 (desde la variable x_{0}).
    int x_prev = -1;   // En la primera llamada no se utiliza este valor.
    int x_actual = -1; // En la primera llamada no se utiliza este valor.
    int y = -1;        // En la primera llamada no se utiliza este valor.
    int la_verdad = 0; // Como es una suma acumulada hay que inicializar en cero.

    // Evaluación primera mitad de La Divina Verdad (pues estamos calculado para x_{0} = 1)
    int la_verdad_izquierda = evaluar(root->izq, nivel, d, x_prev, x_actual, y, la_verdad);

    // Evalución segunda mitad de la Divina Verdad (pues estamos calculando x_{0} = 0)
    int la_verdad_derecha = evaluar(root->der, nivel, d, x_prev, x_actual, y, la_verdad);

    // Para obtener La Divina Verdad completa sumamos ambos resultados.
    int la_divina_verdad = la_verdad_izquierda + la_verdad_derecha;

    // Resultado final
    printf("%d", la_divina_verdad);

    freeArbol(root);
    return 0;
}
nodo *crearArbol(int dim, item valor)
{
    // static int cont = 0;
    // printf("Llamada recursiva %d\n", ++cont);

    nodo *root = malloc(sizeof *root);
    if (!root)
    {
        return NULL;
    }

    root->boolean = valor;

    if (dim == 1)
    {
        root->izq = NULL;
        root->der = NULL;
        return root;
    }

    root->izq = crearArbol(dim - 1, 1);
    root->der = crearArbol(dim - 1, 0);

    if (!root->izq || !root->der)
    {
        // Hay que liberar lo que sí se pudo construir del nodo actual.
        freeArbol(root->izq);
        freeArbol(root->der);
        // Liberamos el nodo actual.
        free(root);
        return NULL;
    }

    return root;
}

void freeArbol(nodo *root)
{
    if (root == NULL)
        return;

    freeArbol(root->izq);
    freeArbol(root->der);

    free(root);
}

int evaluar(nodo *root, int nivel, int d,
            int x_prev, int x_actual,
            int y, int la_verdad)
{
    // Notemos que para nivel = 0 no se hace ningún cálculo, solo recursividad.

    int x_next = root->boolean;

    // Ignición
    if (nivel == 1)
    {
        y = x_actual && !x_next;
        la_verdad += x_actual + x_next;
    }
    // Propagación
    else if (nivel >= 2)
    {
        y = y ^ ((x_prev || !x_actual) && !x_next);
        la_verdad += x_next;
    }

    // La Verdad
    if (nivel == d - 1)
    {
        if (y == 1)
        {
            return la_verdad;
        }
        else
        {
            return 0;
        }
    }

    ////////////////////// RECURSIVIDAD //////////////////////
    /* Para la siguiente llamada: 
        parámetro x_prev    <--  x_actual
        parámetro x_actual  <--  x_next
    */

    // Recursividad nodo hijo izquierda
    int la_verdad_izq = evaluar(root->izq, nivel + 1, d,
                                x_actual, x_next,
                                y, la_verdad);

    // Recursividad nodo hijo derecha
    int la_verdad_der = evaluar(root->der, nivel + 1, d,
                                x_actual, x_next,
                                y, la_verdad);

    return la_verdad_izq + la_verdad_der;
}