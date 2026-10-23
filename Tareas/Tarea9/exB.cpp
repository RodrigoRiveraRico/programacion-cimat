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
  int circular;   // Flag para determinar si la lista es circular. 0 : False 1 : True
public:
    // Constructor (Lista lineal)
    my_list() : head(nullptr), tail(nullptr), sz(0), circular(0) {}

    // Destructor (solo lista lineal)
    ~my_list() { clear(); }
    
    // Para acceder a head
    list_node *get_head() const { return head; }

    // Regresa el tamaño de la lista en O(1)
    size_t size() {
        return sz;
    }

    // Regresa si la lista es circular (1) o no (0).
    int is_circular(){
        return circular;
    }

    // Convertimos una lista lineal en una circular.
    void make_circular(){
        // Si no hay nodos en la lista
        if(sz == 0){
            return;
        }

        // Si ya es circular
        if(circular == 1){
            return;
        }

        tail->next = head;
        head->prev = tail;
        tail = nullptr;     // No usamos este apuntador. Conviene hacerlo nulo.

        circular = 1;
    }

    // Convertimos una lista circular en una lineal.
    void make_linear(){
        // Si no hay nodos en la lista
        if(sz == 0){
            return;
        }

        // Si ya es lineal
        if(circular == 0){
            return;
        }

        tail = head->prev;  // Reasignamos tail. Solo existía head.
        // Rompemos ciclo
        tail->next = nullptr;
        head->prev = nullptr;

        circular = 0;
    }

    // Borra todos los elementos de la lista en O(n) si existen. (Solo lista lineal)
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
    /*
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
    */

    // Regresa el valor del primer nodo de la lista en O(1)
    /*
    int front() {
        // Vale la pena implementar el caso en que la lista esté vacía. head == nullptr
        return head->value;
    }
    */

    // Regresa el valor del último nodo de la lista en O(1)
    /*
    int back() {
        // Vale la pena implementar el caso en que la lista esté vacía. tail == nullptr
        return tail->value;
    }
    */

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
    /*
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
    */

    // Destruye el último nodo de la lista en O(1)
    /*
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
    */

   // Destruye un nodo de la lista en O(1)
    void pop_node(list_node *node){

        // Si no hay nada que borrar
        if(node == nullptr){
            return;
        }

        // Si hay nodo a la izquierda
        if(node->prev != nullptr){
            node->prev->next = node->next;
        }
        // Si no hay nodo a la izquierda : era head
        else{
            head = node->next;
        }

        // Si hay nodo a la derecha
        if(node->next != nullptr){
            node->next->prev = node->prev;
        }
        // Si no hay nodo a la derecha : era tail
        else {
            tail = node->prev;
        }

        delete node;
        sz--;
    }

};

int main(){

    // Número de personas
    int n;
    cin >> n;

    // Número de pasos
    int k;
    cin >> k;

    // Primero, creamos una lista lineal
    my_list mi_lista = my_list();

    // Llenamos la lista con valores desde 1 hasta n
    for(int i=1;i<=n;i++){
        mi_lista.push_back(i);
    }

    // Guardamos head
    list_node *head = mi_lista.get_head();
    // Hacemos que la lista sea circular
    mi_lista.make_circular();

    /*   
    for(int i=0;i<20;i++){
        cout << mi_lista.kth_element(i) << endl;
    }
    */ 
   
    // Empezamos desde head
    list_node *actual = head;

    while(head != head->next){
        // Rendimiento. Para no hacer exceso de iteraciones. Recordar que buscamos simular un ciclo.
        int pasos = k % (int)mi_lista.size();

        for(int i=1;i<pasos;i++){
            head = head->next;
        }

        // Este nodo se va a eliminar
        list_node *muere = head->next;

        cout << "muere el nodo " << muere->value << endl;
        // Borramos
        mi_lista.pop_node(muere);

        for(int i=0;i<mi_lista.size();i++){
        cout << mi_lista.kth_element(i) << endl;
    }

        head = head->next;
    }

    cout << "sobrevive el nodo "; 
    cout << head->value << endl;

    mi_lista.make_linear();

    return 0;
}