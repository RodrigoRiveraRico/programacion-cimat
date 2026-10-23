#include <iostream>
// #include <stdexcept> // Para el manejo de errores. Ver método kth_element
using namespace std; // Evitar usarlo por buena práctica

class list_node {
public:
    int value;
    list_node *next;
    list_node *prev;

    // Constructor
    list_node(int val) : value(val), next(nullptr), prev(nullptr) {}
};

class my_list {
private:
  list_node *head;   // apunta al primer nodo de la lista
  list_node *tail;   // apunta al último nodo de la lista
  size_t sz;         // tamaño de la lista
public:
// Constructor
my_list() : head(nullptr), tail(nullptr), sz(0) {}

// Destructor (asumiendo que clear ya ha sido implementado como
// método de la clase)
~my_list() { clear(); }

// Regresa el tamaño de la lista en O(1)
size_t size() {
    return sz;
}

// Borra todos los elementos de la lista en O(n) si existen.
void clear() {
    // Eliminamos nodo por nodo desde el nodo en head hasta el nodo en tail.
    while(head != nullptr){
        list_node *aux = head;
        head = head->next;
        delete aux;
    }
    tail = nullptr;
    sz = 0;
}

// Inserta un nodo con valor `value` al final de la lista en O(1)
void push_back(int value) {

    // Con memoria dinámica
    list_node *new_node = new list_node(value);

    // Si tail es nullptr       : new_node->prev es nullprt
    // Si tail apunta a un nodo : new_node->prev apunta a ese mismo nodo
    new_node->prev = tail;
    
    // Caso en que tail apunte a un nodo : enlazamos nodos
    if(tail != nullptr){
        tail->next = new_node;
    }
    // Caso en que tail sea nullptr : new_node es el primer nodo
    else{
        head = new_node;
    }

    // Actualizamos tail
    tail = new_node;

    // Sumamos el nuevo nodo
    sz++;
}

// Inserta un nodo con valor `value` al principio de la lista en O(1)
void push_front(int value) {
    
    // Con memoria dinámica
    list_node *new_node = new list_node(value);

    // Si head es nullptr       : new_node->next es nullptr
    // Si head apunta a un nodo : new_node->next apunta a ese mismo nodo
    new_node->next = head;

    // Caso en que head apunte a un nodo : enlazamos nodos
    if(head != nullptr){
        head->prev = new_node;
    }
    // Caso en que head sea nullptr : new_node es el primer nodo
    else{
        tail = new_node;
    }

    // Actualizamos head
    head = new_node;

    // Sumamos el nuevo nodo
    sz++;
}

// Regresa el valor del primer nodo de la lista en O(1)
int front() {
    return head->value;
}

// Regresa el valor del último nodo de la lista en O(1)
int back() {
    return tail->value;
}

// Regresa el valor del k-ésimo (0-indexado) nodo en O(n)
int kth_element(size_t k) {
    
    // Si el índice está fuera de rango
    /*
    if( k >= sz ){
        throw std::out_of_range("Indice fuera de rango"); 
    } 
    */

    list_node *nodo = head;
    for(size_t i=0;i<k;i++){
        nodo = nodo->next;
    }

    return nodo->value;
}

// Destruye el primer nodo de la lista en O(1)
void pop_front() {

    // Nodo a eliminar
    list_node *aux = head;

    // Si solo hay un nodo              : head->next es nullptr
    // Si hay otro nodo después de head : head->next apunta a ese nodo.
    head = head->next;

    // Caso nullptr
    if(head == nullptr){
        tail = nullptr;
    }
    // Caso en que haya otro nodo
    else{
        head->prev = nullptr;
    }

    // Eliminamos
    delete aux;

    // Restamos el nodo eliminado
    sz--;
}

// Destruye el último nodo de la lista en O(1)
void pop_back() {

    // Nodo a eliminar
    list_node *aux = tail;

    // Si solo hay un nodo              : tail->prev es nullptr
    // Si hay otro nodo antes de head   : tail->prev apunta a ese nodo.
    tail = tail->prev;

    // Caso nullptr
    if(tail == nullptr){
        head = nullptr;
    }
    // Caso en que haya otro nodo
    else{
        tail->next = nullptr;
    }

    // Eliminamos
    delete aux;

    // Restamos el nodo eliminado
    sz--;    
}

};

/*
int front() const {
    if (head == nullptr) {
        throw std::out_of_range("Lista vacia");
    }

    return head->value;
}

int back() const {
    if (tail == nullptr) {
        throw std::out_of_range("Lista vacia");
    }

    return tail->value;
}*/


int main() {
    my_list mi_lista;

    mi_lista.push_back(10);
    mi_lista.push_back(20);
    mi_lista.push_front(5);

    std::cout << "Tamano: " << mi_lista.size() << '\n';
    std::cout << "Primero: " << mi_lista.front() << '\n';
    std::cout << "Ultimo: " << mi_lista.back() << '\n';
    std::cout << "Elemento 1: "
              << mi_lista.kth_element(1) << '\n';

    mi_lista.pop_front();
    mi_lista.pop_back();

    std::cout << "Tamano final: " << mi_lista.size() << '\n';

    return 0;
}

/* El destructor se ejecuta automaticamente?

¡Sí\! En C++, el destructor se ejecuta automáticamente cuando un objeto llega al final de su tiempo de vida. No necesitas llamarlo manualmente.

En tu implementación, tienes este destructor:

cpp
```
~my_list() {
    clear();
}
```

Esto significa que, cuando un objeto de tipo `my_list` deja de existir, se ejecuta `clear()` para liberar todos los nodos que la lista haya reservado con `new`.

## 1. ¿Cuándo se ejecuta?

### Caso A: Al salir de una función

Considera tu `main()`:

cpp
```
int main() {
    my_list mi_lista;

    mi_lista.push_back(10);
    mi_lista.push_back(20);

    std::cout << mi_lista.size() << '\n';

    return 0;
}
```

Ocurre lo siguiente:

1. Se crea `mi_lista`.

Se ejecuta el constructor `my_list()`. Inicialmente, `head` y `tail` son `nullptr` y `sz` es `0`.

2. Se insertan dos nodos.

`push_back()` reserva memoria para los nodos con `new`.

3. Termina `main()`.

`mi_lista` sale de su tiempo de vida y C++ llama automáticamente a `~my_list()`.

4. Se ejecuta `clear()`.

Se liberan los nodos y se evita dejar esa memoria reservada sin necesidad.

## 2. ¿Y si creo un objeto dentro de un bloque?

cpp
```
int main() {
    std::cout << "Antes\n";

    {
        my_list lista;
        lista.push_back(10);

        std::cout << "Dentro del bloque\n";
    } // Aquí se ejecuta el destructor.

    std::cout << "Despues\n";
}
```

La salida será:

text
```
Antes
Dentro del bloque
Despues
```

Aunque no veas una llamada explícita al destructor, este se ejecuta al cerrar el bloque `}` en el que se declaró `lista`.

## 3. ¿Debo llamar al destructor manualmente?

No. No hagas esto:

cpp
```
lista.~my_list(); // No recomendado
```

Si llamas manualmente al destructor de un objeto que sigue dentro de su tiempo de vida, puedes provocar que se liberen sus recursos y que después se vuelva a ejecutar el destructor automáticamente. Eso puede ocasionar errores graves, como liberar la misma memoria dos veces.

En cambio, si quieres vaciar la lista sin destruir el objeto, utiliza:

cpp
```
lista.clear();
```

La lista seguirá existiendo y podrás insertar nuevos nodos.

## 4. ¿Qué pasa con los objetos creados con `new`?

Hay una diferencia importante:

cpp
```
my_list a;                 // Destructor automático al salir del ámbito.
my_list* b = new my_list;  // El destructor no se ejecuta al salir del ámbito.
```

En el segundo caso, `b` es un puntero a un objeto creado dinámicamente. Debes gestionar su tiempo de vida; si usas `delete b`, se ejecutará el destructor de `my_list`.

En C++ moderno, generalmente es preferible usar `std::unique_ptr` para administrar este tipo de objetos automáticamente.

En resumen: en tu programa, `~my_list()` se ejecuta automáticamente cuando `mi_lista` sale de su ámbito. El destructor llama a `clear()`, y este libera los nodos que la lista creó. Esa es precisamente una de las funciones más importantes de un destructor en una clase que administra memoria.
*/