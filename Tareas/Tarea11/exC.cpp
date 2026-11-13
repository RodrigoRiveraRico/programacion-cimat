#include <iostream>
#include <cstdlib> // Para abs()


// Definición para el tipo de dato de los nodos
typedef int Item;

// Función auxiliar para calcular el máximo (alturas)
size_t max(size_t A, size_t B){
    return A > B ? A : B;
}

/** Clase nodo 
  * Diremos que la altura del nodo es la cantidad máxima de nodos que hay a la izquierda o derecha, y que están en un mismo camino.
  * Cada nodo hoja tiene altura 1.
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
    // No se permiten datos repetidos en el árbol.
    void insertarRecursivo(Nodo*& root, Item val) {
        // Recursivamente buscamos el lugar correcto para poner el nuevo nodo.
        // Caso base : insertar nodo
        if(root == nullptr){
            root = new Nodo(val);
            return;
        }
        // Insertar a la izquierda
        else if(val < root->dat){
            insertarRecursivo(root->izq, val);
        }
        // Insertar a la derecha
        else if(val > root->dat){
            insertarRecursivo(root->der, val);
        }
        // Ignorar el nodo. Ya existe el dato en el árbol.
        else{
            return;
        }
    }
 
    // Función recursiva para determinar si el nodo root está balanceado o no.
    int isBalancedRecursivo(Nodo* root){

        // Si no se apunta a un nodo, la altura es cero.
        if(root==nullptr){
            return 0;
        }

        int depth_izq = isBalancedRecursivo(root->izq);
        int depth_der = isBalancedRecursivo(root->der);

        // Buscamos propagar -1 si el árbol está desbalanceado
        if(depth_izq == -1 || depth_der == -1 || abs(depth_izq - depth_der) > 1){
            return -1;
        }
        // Calculamos la altura del nodo root
        else{
            return 1 + max(depth_izq, depth_der);
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

    bool isBalanceado() { 
        if(isBalancedRecursivo(raiz) >= 0){
            std::cout << "True";
            return true;
        }
        else{
            std::cout << "False";
            return false;
        }
    }
   
    // Imprimir Árbol en preorder
    void imprimirPreorder() {
        imprimirPreorderRecursivo(raiz);
    }

};

int main(){

    // Cantidad de elementos a insertar
    size_t n;
    std::cin >> n;

    // Init del árbol
    BST mi_arbol = BST();

    // Inserciones
    for(size_t i=0; i<n; i++){
        Item input;
        std::cin >> input;
        mi_arbol.insertar(input);
    }

    // Comprobar balanceo
    mi_arbol.isBalanceado();

    return 0;
}