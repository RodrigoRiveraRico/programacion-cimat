#include <stdio.h>
#include <stdlib.h>

typedef int item;

typedef struct Nodo
{
    item boolean;
    struct Nodo *izq;
    struct Nodo *der;

} nodo;

/* Árbol a construir

             root
            /    \
           1      0
          / \    / \
         1   0  1   0
        / \ / \ / \ / \
       ...
*/
/** @brief Función que crea un árbol binario recursivamente.
  *
  * El nodo raíz puede tener cualquier valor.
  * Para los demás nodos: el nodo hijo izquierdo tendrá 1, el nodo hijo derecho tendrá 0
  * 
  * La idea del árbol construido es la representación de una tabla de verdad; cada nivel después de la raíz representa una variable booleana. 
  * El recorrido hacia las hojas son las diferentes combinaciones de las variables booleanas.
  * @param dim int Profundidad que tendrá el árbol
  * @param valor item Dato del nodo
  * @return nodo * Nodo raíz del árbol
  */
nodo *crearArbol(int dim, item valor);

/** @brief Libera memoria dinámica de un árbol binario. Función recursiva.
 * 
 * @param root nodo * raíz del árbol.
 */
void freeArbol(nodo *root);

int main(void)
{
    // Cantidad de variables booleanas
    unsigned d;
    d=3;

    // d variables booleanas + 1 raíz.
    // El valor de la raíz será la cantidad de variables booleanas. Esto solo por poner un valor a la raíz.
    nodo *root = crearArbol(d+1, d);
    if (!root)
    {
        return 1;
    }
    printf("%d", root->izq->der->izq->boolean);

    
    freeArbol(root);
    return 0;
}
nodo *crearArbol(int dim, item valor)
{
    static int cont = 0;
    printf("Llamada recursiva %d\n", ++cont);

    
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