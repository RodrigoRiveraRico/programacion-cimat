#include <iostream>

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
        size_t altura;  /**< Altura del nodo */

        // Constructor
        Nodo(Item val) : dat(val), izq(nullptr), der(nullptr), altura(1) {}
};

class ArbolAVL {
private:
    Nodo* raiz; /**< Miembro : Apuntador a la raíz */

    // Función para obtener la altura de un nodo
    size_t getAltura(Nodo*& nodo){
        // Si no se está apuntando a ningún nodo
        if(nodo==nullptr){
            return 0;
        }

        return nodo->altura;
    }
    
    // Función para calcular el factor de balance
    int getFactorBalance(Nodo*& root) {
        // Si no se está apuntando a ningún nodo
        if(root==nullptr){
            return 0;
        }

        // OJO size_t puede ser más grande que int. Posible pérdida de datos en la conversión.
        return static_cast<int>(getAltura(root->izq) - getAltura(root->der));
    }

    // Función para rotación derecha sobre nodo root
    void rotacion_derecha(Nodo*& root) {}

    // Función para rotación izquierda sobre nodo root
    void rotacion_izquierda(Nodo*& root) {}

    // Función recursiva para insertar un nuevo nodo.
    void insertarRecursivo(Nodo*& root, Item val) {
        // Recursivamente buscamos el lugar correcto para poner el nuevo nodo
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

        // Actualizamos el valor de la altura del nodo root (notar que esto aplica a cada nodo en la recursión)
        root->altura = 1 + max(getAltura(root->izq), getAltura(root->der));

        // Evaluar los 4 casos de rotación
        // Caso LL
        if(getFactorBalance(root) > 1 && getFactorBalance(root->izq) >= 0){
            rotacion_derecha(root);
        }
        // Caso RR
        else if(getFactorBalance(root) < -1 && getFactorBalance(root->der) <= 0){
            rotacion_izquierda(root);
        }
        // Caso LR
        else if(getFactorBalance(root) > 1 && getFactorBalance(root->izq) < 0){
            rotacion_izquierda(root->izq);
            rotacion_derecha(root);
        }
        // Caso RL
        else if(getFactorBalance(root) < -1 && getFactorBalance(root->der) > 0){
            rotacion_derecha(root->der);
            rotacion_izquierda(root);
        }
    }

    // Función recursiva para imprimir en preorder
    void imprimirPreorderRecursivo(Nodo*& root) {
        
        if(root == nullptr){
            return;
        }

        std::cout << root->dat << " ";

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
    // Constructor del Árbol AVL
    ArbolAVL() { raiz = nullptr; }

    // Destructor del Árbol AVL
    ~ArbolAVL() { liberarArbol(raiz); }

    // El usuario solo necesita poner el valor del nuevo nodo
    void insertar(Item val){
        insertarRecursivo(raiz, val);
    }
   
    // Imprimir Árbol en preorder
    void imprimirPreorder() {
        imprimirPreorderRecursivo(raiz);
    }

};

int main(){

    ArbolAVL mi_arbol = ArbolAVL();

    mi_arbol.insertar(10);
    mi_arbol.insertar(5);
    mi_arbol.insertar(30);
    mi_arbol.insertar(40);

    mi_arbol.imprimirPreorder();


    return 0;
}

/*
5
10
20
30
40
50
*/

