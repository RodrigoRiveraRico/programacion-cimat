#include <iostream>
#include <cstdlib> // Para abs()


// Definición para el tipo de dato de los nodos
typedef int Item;

// Función auxiliar para calcular el máximo (alturas)
size_t max(size_t A, size_t B){
    return A > B ? A : B;
}

/** Clase nodo 
  */
class Nodo{
    public:
        // Miembros
        Item dat;       /**< Dato */
        Nodo* izq;      /**< Nodo a la izquierda */
        Nodo* der;      /**< Nodo a la derecha */

        // Constructor
        Nodo(Item val) : dat(val), izq(nullptr), der(nullptr) {}
};

class BST {
private:
    Nodo* raiz; /**< Miembro : Apuntador a la raíz */

    // Función recursiva para insertar un nuevo nodo.
    // Se permiten valores repetidos en el sub-árbol izquierdo
    void insertarRecursivo(Nodo*& root, Item val) {
        // Recursivamente buscamos el lugar correcto para poner el nuevo nodo.
        // Caso base : insertar nodo
        if(root == nullptr){
            root = new Nodo(val);
            return;
        }
        // Insertar a la izquierda
        else if(val <= root->dat){
            insertarRecursivo(root->izq, val);
        }
        // Insertar a la derecha
        else if(val > root->dat){
            insertarRecursivo(root->der, val);
        }
    }

    // Función recursiva para imprimir en preorder
    // Nota: Usamos Nodo* pues no modificamos el apuntador recibido.
    void imprimirPreorderRecursivo(Nodo* root) {
        
        if(root == nullptr){
            return;
        }

        std::cout << root->dat << "\n";

        imprimirPreorderRecursivo(root->izq);
        imprimirPreorderRecursivo(root->der);
    }

    // Función recursiva para imprimir en inorder
    void imprimirInOrderRecursivo(Nodo* root, int* contador, int max){

        if(root == nullptr || *contador > max){
            return;
        }

        imprimirInOrderRecursivo(root->izq,contador,max);

        if(*contador > max){
            return;
        }

        // Procesar root
        std::cout << root->dat << " ";
        *contador++;

        if(*contador > max){
            return;
        }

        imprimirInOrderRecursivo(root->der,contador,max);
    }

    // Función recursiva para liberar todo el árbol
    void liberarArbol(Nodo*& root){
        // Si no se está apuntando a ningún nodo
        if(root==nullptr){
            return;
        }

        // Recurividad hacia el hijo izquierdo
        liberarArbol(root->izq);
        // Recursividad hacia el hijo derecho
        liberarArbol(root->der);
        // Liberar
        delete root;
        // Aterrizar
        root = nullptr;
    }
    
public:
    // Constructor del Árbol BST
    BST() { raiz = nullptr; }

    // Destructor del Árbol BST
    ~BST() { liberarArbol(raiz); }

    // El usuario solo necesita poner el valor del nuevo nodo
    void insertar(Item val){
        insertarRecursivo(raiz, val);
    }
   
    // Imprimir Árbol en preorder
    void imprimirPreorder() {
        imprimirPreorderRecursivo(raiz);
    }

    // Imprimir Árbol en inorder
    void imprimirInOrder(int max){
        int contador = 0;
        imprimirInOrderRecursivo(raiz, &contador, max);
    }

};

int main(){

    // Cantidad de elementos a insertar
    size_t n;
    // std::cin >> n;

    n = 6;

    // Init del árbol
    BST mi_arbol = BST();

    // Inserciones
    // for(size_t i=0; i<n; i++){
    //     Item input;
    //     std::cin >> input;
    //     mi_arbol.insertar(input);
    // }

    mi_arbol.insertar(30);
    mi_arbol.insertar(10);
    mi_arbol.insertar(50);
    mi_arbol.insertar(20);
    mi_arbol.insertar(10);
    mi_arbol.insertar(40);

    int max = 4;
    mi_arbol.imprimirInOrder(max);

    return 0;
}

/*
6
30
10
50
20
10
40
*/

/*
// Recorrido In-Order adaptado para buscar el k-ésimo elemento más pequeño
bool buscarKInOrder(Nodo *raiz, int k, int *contador, int *resultado) {
    if (raiz == NULL) {
        return false;
    }

    // 1. Buscar en el subárbol izquierdo
    if (buscarKInOrder(raiz->izq, k, contador, resultado)) {
        return true; // Si ya se encontró abajo, sube la señal de parada
    }

    // 2. Procesar la raíz actual
    if (*contador == k) {
        *resultado = raiz->valor;
        return true; // Se encontró el elemento, se detiene la recursión
    }
    (*contador)++; // Incrementar los nodos válidos visitados hasta ahora

    // 3. Buscar en el subárbol derecho
    return buscarKInOrder(raiz->der, k, contador, resultado);
}


int k;
    // Procesar consultas dinámicamente una por una
    while (scanf("%d", &k) == 1 && k != -1) {
        int contador = 0;
        int resultado = 0;

        // Se hace un recorrido completo/parcial desde la raíz en cada iteración
        if (buscarKInOrder(raiz, k, &contador, &resultado)) {
            printf("%d\n", resultado);
        } else {
            printf("Fuera de rango\n");
        }
    }
        
*/