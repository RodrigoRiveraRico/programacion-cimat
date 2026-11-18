#include <iostream>
#include <random>
#include <cmath>    // Para std::log2

// Definición para el tipo de dato de los nodos
typedef int Item;

// Función auxiliar para calcular el máximo (alturas)
// Nota: Hay que implementar un template
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

class Tree {
private:
    Nodo* raiz; /**< Miembro : Apuntador a la raíz */

    // Función para obtener la altura de un nodo
    // Nota: Usamos Nodo* pues no modificamos el apuntador recibido.
    size_t getAltura(Nodo* nodo){
        // Si no se está apuntando a ningún nodo
        if(nodo==nullptr){
            return 0;
        }

        return nodo->altura;
    }
    
    // Función para calcular el factor de balance
    // Nota: Usamos Nodo* pues no modificamos el apuntador recibido.
    int getFactorBalance(Nodo* root) {
        // Si no se está apuntando a ningún nodo
        if(root==nullptr){
            return 0;
        }

        // OJO size_t puede ser más grande que int. Posible pérdida de datos en la conversión.
        return static_cast<int>(getAltura(root->izq)) - static_cast<int>(getAltura(root->der));
    }

    // Función auxiliar para actualizar la altura de un nodo root.
    void actualizarAltura(Nodo* root){
    if(root == nullptr){
        return;
    }

    root->altura = 1 + max(
        getAltura(root->izq),
        getAltura(root->der)
    );
}

    // Función para rotación derecha sobre nodo root
    void rotacion_derecha(Nodo*& root) {
        Nodo* y = root;
        Nodo* x = root->izq;

        y->izq = x->der;
        x->der = y;

        root = x;

        actualizarAltura(y);
        actualizarAltura(x);
    }

    // Función para rotación izquierda sobre nodo root
    void rotacion_izquierda(Nodo*& root) {
        Nodo* x = root;
        Nodo* y = root->der;

        x->der = y->izq;
        y->izq = x;

        root = y;

        actualizarAltura(x);
        actualizarAltura(y);
    }

    // Función recursiva para insertar un nuevo nodo (árbol AVL)
    // No se permiten datos repetidos en el árbol.
    void insertarRecursivoAVL(Nodo*& root, Item val) {
        // Recursivamente buscamos el lugar correcto para poner el nuevo nodo.
        // Caso base : insertar nodo
        if(root == nullptr){
            root = new Nodo(val);
            return;
        }
        // Insertar a la izquierda
        else if(val < root->dat){
            insertarRecursivoAVL(root->izq, val);
        }
        // Insertar a la derecha
        else if(val > root->dat){
            insertarRecursivoAVL(root->der, val);
        }
        // Ignorar el nodo. Ya existe el dato en el árbol.
        else{
            return;
        }

        // Actualizamos el valor de la altura del nodo root (notar que esto aplica a cada nodo en la recursión)
        actualizarAltura(root);

        int balance = getFactorBalance(root);

        // Evaluar los 4 casos de rotación
        // Caso LL
        if(balance > 1 && getFactorBalance(root->izq) >= 0){
            rotacion_derecha(root);
        }
        // Caso RR
        else if(balance < -1 && getFactorBalance(root->der) <= 0){
            rotacion_izquierda(root);
        }
        // Caso LR
        else if(balance > 1 && getFactorBalance(root->izq) < 0){
            rotacion_izquierda(root->izq);
            rotacion_derecha(root);
        }
        // Caso RL
        else if(balance < -1 && getFactorBalance(root->der) > 0){
            rotacion_derecha(root->der);
            rotacion_izquierda(root);
        }
    }

    // Función recursiva para insertar un nuevo nodo (árbol BST)
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

        // Actualizamos el valor de la altura del nodo root (notar que esto aplica a cada nodo en la recursión)
        actualizarAltura(root);
    }

    // Función recursiva para insertar un nuevo nodo (insertar a la raíz)
    void insertarRecursivoARaiz(Nodo*& root, Item val){
        // Recursivamente buscamos el lugar correcto para poner el nuevo nodo.
        // Caso base : insertar nodo
        if(root == nullptr){
            root = new Nodo(val);
            return;
        }
        // Insertar a la izquierda y rotación derecha
        else if(val < root->dat){
            insertarRecursivoARaiz(root->izq, val);
            if(root->izq != nullptr){
                rotacion_derecha(root);
            }
        }
        // Insertar a la derecha y rotación izquierda
        else if(val > root->dat){
            insertarRecursivoARaiz(root->der, val);
            if(root->der != nullptr){
                rotacion_izquierda(root);
            }
        }
        // Ignorar el nodo. Ya existe el dato en el árbol.
        else{
            return;
        }

        // Actualizamos el valor de la altura del nodo root (notar que esto aplica a cada nodo en la recursión)
        actualizarAltura(root);
    }

    /**
     * @brief Función recursiva para insertar un nuevo nodo a la raíz de forma probabilista
     * 
     * Dada una probabildad y una distribución uniforme en el intervalo [0,1] 
     * se opta por el algoritmo de inserción a la raíz sobre el nodo en cuestión si el número aleatorio generado es menor que la probabilidad dada.
     * 
     * Notar que la elección entre el algoritmo de insertar a la raíz e instar como un BST ordinario se hace en cada paso recursivo (no necesariamente el nuevo nodo quedará como raíz del árbol).
     * @param root Nodo*& Referencia a un nodo
     * @param val Item Valor del nodo
     * @param proba double Probabilidad de que el nodo se inserte a la raíz
     * @param gen Referencia al generador de números aleatorios
     */
    void insertarRecursivoAleatorio(Nodo*& root, Item val, double proba, std::mt19937& gen){

        // Recursivamente buscamos el lugar correcto para poner el nuevo nodo.
        // Caso base : insertar nodo
        if(root == nullptr){
            root = new Nodo(val);
            return;
        }

        // Genera un número decimal aleatorio entre 0.0 y 1.0
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        double aleatorio = dist(gen);

        // Insertar a la raíz con cierta probabilidad
        if(aleatorio < proba){
            // Insertar a la izquierda y rotación derecha
            if(val < root->dat){
                insertarRecursivoAleatorio(root->izq, val, proba, gen);
                if(root->izq != nullptr){
                    rotacion_derecha(root);
                }
            }
            // Insertar a la derecha y rotación izquierda
            else if(val > root->dat) {
                insertarRecursivoAleatorio(root->der, val, proba, gen);
                if(root->der != nullptr){
                    rotacion_izquierda(root);
                }
            }
            // No se permiten valores repetidos
            else{
                return;
            }
        }
        // Insertar como un BST ordinario
        else{
            // Insertar a la izquierda
            if(val < root->dat){
                insertarRecursivoAleatorio(root->izq, val, proba, gen);
            }
            // Insertar a la derecha
            else if(val > root->dat){
                insertarRecursivoAleatorio(root->der, val, proba, gen);
            }
            // No se permiten valores repetidos
            else{
                return;
            }
        }

        // Actualizamos el valor de la altura del nodo root (notar que esto aplica a cada nodo en la recursión)
        actualizarAltura(root);
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
    // Constructor del Árbol AVL
    Tree() { raiz = nullptr; }

    // Destructor del Árbol AVL
    ~Tree() { liberarArbol(raiz); }

    // El usuario solo necesita poner el valor del nuevo nodo
    void insertarAVL(Item val){
        insertarRecursivoAVL(raiz, val);
    }

    void insertarAleatorio(Item val, double proba, std::mt19937& gen){
        insertarRecursivoAleatorio(raiz, val, proba, gen);
    }
    
    // Imprimir Árbol en preorder
    void imprimirPreorder() {
        imprimirPreorderRecursivo(raiz);
    }

    // Imprimir altura del Árbol
    size_t Altura() {
        return getAltura(raiz);
    }

};

int main(){

    // Inicializar el generador de números aleatorios con una semilla real
    std::random_device rd;
    std::mt19937 gen(rd());

    // Cantidad de elementos a insertar
    size_t n;
    std::cin >> n;

    // Inicializar árbol
    Tree mi_arbol = Tree();

    // Definir la probabilidad
    double proba = 0.32;

    // Inserciones
    for(size_t i=0;i<n;i++){
        Item input;
        std::cin >> input;
        mi_arbol.insertarAleatorio(input, proba, gen);
    }

    // Imprimir en preorder
    // std::cout << "\n";
    // mi_arbol.imprimirPreorder();

    // Altura minima optima de un BST
    int opt = std::log2f(n) + 1;
    // std::cout << "log: " << opt << "\n";

    // Altura de mi_arbol
    size_t h = mi_arbol.Altura();
    // std::cout << "h: " << h << "\n";

    // Salida a consola
    // Esta operación debe de poderse hacer con un template de max() definida arriba
    double max = ( 0.0 > 1.0 - static_cast<double>(h-opt)/1000.0 ? 0.0 : 1.0 - static_cast<double>(h-opt)/1000.0 );
    std::cout << max;


    return 0;
}
