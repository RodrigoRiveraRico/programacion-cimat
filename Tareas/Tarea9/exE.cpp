#include <iostream>

class list_node
{
public:
    int value;
    list_node *next;

    // Constructor
    list_node(int val) : value(val), next(nullptr) {}
};

class my_list
{
private:
    list_node *head; // apunta al primer nodo de la lista
    list_node *tail; // apunta al último nodo de la lista
    size_t sz;       // tamaño de la lista
public:
    // Constructor
    my_list() : head(nullptr), tail(nullptr), sz(0) {}

    // Destructor
    ~my_list() { clear(); }

    // Borra todos los elementos de la lista en O(n) si existen.
    void clear()
    {
        // Eliminamos nodo por nodo desde el nodo en head hasta el nodo en tail.
        while (head != nullptr)
        {
            list_node *aux = head;
            head = head->next;
            delete aux;
        }
        tail = nullptr;
        sz = 0;
    }

    // Inserta un nodo con valor `value` al final de la lista en O(1)
    void push_back(int value)
    {

        // Con memoria dinámica
        list_node *new_node = new list_node(value);

        // Caso en que tail apunte a un nodo : enlazamos nodos
        if (tail != nullptr)
        {
            tail->next = new_node;
        }
        // Caso en que tail sea nullptr : new_node es el primer nodo
        else
        {
            head = new_node;
        }

        // Actualizamos tail
        tail = new_node;

        // Sumamos el nuevo nodo
        sz++;
    }

    // Extiende una lista en O(n)
    void append_copy(const my_list &other) // Paso por referencia
    {

        // Guardar el tamaño de la lista si queremos copiar una sobre sí misma: se evita bucle infinito.
        size_t other_size = other.sz;
        // Apuntador para recorrer la lista
        list_node *actual = other.head;

        for (int i = 0; i < other_size; i++)
        {
            push_back(actual->value);
            actual = actual->next;
        }
    }

    // Imprime los elementos de una lista en O(n)
    void printList()
    {
        list_node *actual = head;
        while (actual != nullptr)
        {
            std::cout << actual->value << " ";
            actual = actual->next;
        }
        std::cout << "\n";
    }
};

int main()
{

    // Número de listas
    unsigned n;
    std::cin >> n;

    // Apuntador a n listas
    my_list *list_set = new my_list[n];

    // Llenamos las n listas
    for (unsigned i = 0; i < n; i++)
    {
        // Tamaño de la i-ésima lista
        unsigned size;
        std::cin >> size;

        for (unsigned k = 0; k < size; k++)
        {
            int data;
            std::cin >> data;
            list_set[i].push_back(data);
        }
    }

    // Cantidad de operaciones
    unsigned q;
    std::cin >> q;

    for (unsigned k = 0; k < q; k++)
    {

        // Listas a considerar.
        // Valores entre 1 y n.
        unsigned lst_i, lst_j;
        std::cin >> lst_i; // Lista i
        std::cin >> lst_j; // Lista j

        // Listas indexadas desde 0
        lst_i--;
        lst_j--;

        list_set[lst_i].append_copy(list_set[lst_j]);
    }

    // Elección de una lista
    unsigned L;
    std::cin >> L;
    // Listas indexadas desde 0
    L--;
    list_set[L].printList();

    // OJO: Este delete se corresponde con new[]
    delete[] list_set;

    return 0;
}