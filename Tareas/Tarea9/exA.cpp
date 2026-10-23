#include <iostream>
#include <string>

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

    // Destructor
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
        // Vale la pena implementar el caso en que la lista esté vacía. head == nullptr
        return head->value;
    }

    // Regresa el valor del último nodo de la lista en O(1)
    int back() {
        // Vale la pena implementar el caso en que la lista esté vacía. tail == nullptr
        return tail->value;
    }

    // Regresa el valor del k-ésimo (0-indexado) nodo en O(n)
    int kth_element(size_t k) {
        // Vale la pena implementar el caso en que el índice esté fuera de rango. k >= sz

        list_node *nodo = head;
        for(size_t i=0;i<k;i++){
            nodo = nodo->next;
        }

        return nodo->value;
    }

    // Destruye el primer nodo de la lista en O(1)
    void pop_front() {
        // Vale la pena implementar el caso en que la lista esté vacía. head == nullptr

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
        // Vale la pena implementar el caso en que la lista esté vacía. tail == nullptr

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

int main(){

    string operacion;
    int valor;
    size_t indice;
    my_list *mi_lista = nullptr;

    while(cin >> operacion){

        // Se garantiza que esta instrucción solo aparece una vez y es la primera.
        if(operacion == "INIT"){
            mi_lista = new my_list;
        }

        else if(operacion =="SIZE"){
            cout << mi_lista->size() << endl;
        }
        else if(operacion == "CLEAR"){
            mi_lista->clear();
        }
        else if(operacion == "PUSH_BACK"){
            cin >> valor;
            mi_lista->push_back(valor);
        }
        else if(operacion == "PUSH_FRONT"){
            cin >> valor;
            mi_lista->push_front(valor);
        }
        // Se garantiza que esta operación no se manda a llamar en lista vacía.
        else if(operacion == "FRONT"){
            cout << mi_lista->front() << endl;
        }
        // Se garantiza que esta operación no se manda a llamar en lista vacía.
        else if(operacion == "BACK"){
            cout << mi_lista->back() << endl;
        }
        // Se garantiza que esta operación no se manda a llamar en lista vacía.
        else if(operacion == "K_ELEMENT"){
            cin >> indice;
            cout << mi_lista->kth_element(indice) << endl;
        }
        // Se garantiza que esta operación no se manda a llamar en lista vacía.
        else if(operacion == "POP_FRONT"){
            mi_lista->pop_front();
        }
        // Se garantiza que esta operación no se manda a llamar en lista vacía.
        else if(operacion == "POP_BACK"){
            mi_lista->pop_back();
        }
    }

    delete mi_lista;

    return 0;
}