#include <iostream>
#include <vector>

// El valor de k corresponde con el valor del nodo. A partir de este nodo (raíz) se hace el recorrido en preorder.
void preorder(const std::vector<size_t>& izq, const std::vector<size_t>& der, const size_t k){

    // Caso base: El valor del nodo es cero (no hay nodos hijos).
    if(k==0){
        return;
    }
    // Imprimir nodo padre
    std::cout << k << " ";

    // Imprimir nodo hijo izquierdo
    preorder(izq, der, izq[k]);

    // Imprimir nodo hijo derecho.
    preorder(izq, der, der[k]);
}

int main(){

    // Número de nodos
    size_t n;
    std::cin >> n;

    /*
    Representaremos cada hijo izquierdo y cada hijo derecho como elementos en vectores.
    Cada índice se corresponde con el nodo padre.
    Nota: El índice cero del vector no se utilizará.
    Nota: El tamaño del vector es n+1 para lograr identificar que los nodos hoja no tiene hijos.
    */
    std::vector<size_t> izq(n+1);
    std::vector<size_t> der(n+1);

    for (size_t i = 1; i < n; i++)
    {
        char C;
        std::cin >> C;

        size_t u;
        std::cin >> u;

        size_t nodo = i+1;

        if(C == 'L'){
            izq[u] = nodo;
        }
        else if(C == 'R'){
            der[u] = nodo;
        }
    }

    // Preorder desde el nodo (raíz) 1
    preorder(izq, der, 1);

    return 0;
}

/*
7
R 3
R 1
L 6
L 3
L 1
L 2
*/