#include <iostream>
#include <vector>

// Definición para el tipo de dato de los nodos
typedef int Item;

/** Clase nodo
 */
class Nodo
{
public:
    // Miembros
    Item dat;  /**< Dato */
    Nodo *izq; /**< Nodo a la izquierda */
    Nodo *der; /**< Nodo a la derecha */

    // Constructor
    Nodo(Item val) : dat(val), izq(nullptr), der(nullptr) {}
};

class BST
{
private:
    Nodo *raiz; /**< Miembro : Apuntador a la raíz */
    int n;      /**< Cantidad de nodos */

    // Función recursiva para insertar un nuevo nodo.
    // Se permiten valores repetidos en el sub-árbol izquierdo
    void insertarRecursivo(Nodo *&root, Item val)
    {
        // Recursivamente buscamos el lugar correcto para poner el nuevo nodo.
        // Caso base : insertar nodo
        if (root == nullptr)
        {
            root = new Nodo(val);
            n++;
            return;
        }
        // Insertar a la izquierda
        else if (val <= root->dat)
        {
            insertarRecursivo(root->izq, val);
        }
        // Insertar a la derecha
        else if (val > root->dat)
        {
            insertarRecursivo(root->der, val);
        }
    }

    // Función recursiva para llenar un vector con los datos del árbol en recorrido In Order
    void llenarInOrderRecursivo(Nodo *root, std::vector<Item> &vector)
    {

        if (root == nullptr)
        {
            return;
        }

        // Nodo izquierdo
        llenarInOrderRecursivo(root->izq, vector);

        // Añadir root al vector
        vector.push_back(root->dat);

        // Nodo derecho
        llenarInOrderRecursivo(root->der, vector);
    }

    // Función recursiva para liberar todo el árbol
    void liberarArbol(Nodo *&root)
    {
        // Si no se está apuntando a ningún nodo
        if (root == nullptr)
        {
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
    BST()
    {
        raiz = nullptr;
        n = 0;
    }

    // Destructor del Árbol BST
    ~BST() { liberarArbol(raiz); }

    // El usuario solo necesita poner el valor del nuevo nodo
    void insertar(Item val)
    {
        insertarRecursivo(raiz, val);
    }

    // Crear un vector con los datos del árbol en In Order
    std::vector<Item> inOrderList()
    {

        std::vector<Item> lista_inorder;

        // Reservamos memoria para n elementos, pero size() es cero.
        lista_inorder.reserve(n);

        // Llenado del vector O(n)
        llenarInOrderRecursivo(raiz, lista_inorder);

        return lista_inorder;
    }
};

int main()
{

    // Cantidad de elementos a insertar
    size_t n;
    std::cin >> n;

    // Init del árbol
    BST mi_arbol = BST();

    // Inserciones
    for (size_t i = 0; i < n; i++)
    {
        Item input;
        std::cin >> input;
        mi_arbol.insertar(input);
    }

    /*
    La idea es construir un vector con los elementos del árbol en recorrido In Order.
    Aunque necesitamos usar memoria extra para almacenar los valores (int) del árbol, 
    la ventaja está en que cada consulta se hace en tiempo O(1); no hay que recorrer el árbol cada vez para cada consulta.
    */

    std::vector<int> lista_inorder = mi_arbol.inOrderList();

    // Consultas O(1)
    int k;
    while (1)
    {
        std::cin >> k;

        if (k == -1)
        {
            break;
        }
        else if (k >= n)
        {
            std::cout << "Fuera de rango\n";
        }
        else
        {
            std::cout << lista_inorder[k] << "\n";
        }
    }

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
