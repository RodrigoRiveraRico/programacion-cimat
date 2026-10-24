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
  int circular;      // Flag para determinar si la lista es circular. 0 : False. 1 : True
public:
    // Constructor (Lista lineal)
    my_list() : head(nullptr), tail(nullptr), sz(0), circular(0) {}

    // Destructor (Lista lineal)
    ~my_list() { clear(); }
    
    // Para acceder a head
    list_node *get_head() const { return head; }

    // Regresa el tamaño de la lista en O(1)
    size_t size() {
        return sz;
    }

    // Convertir lista lineal en lista circular
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

        tail = head->prev;  // Reasignamos tail. Solo existía apuntador a head en una lista circular.

        // Rompemos ciclo
        tail->next = nullptr;
        head->prev = nullptr;

        circular = 0;
    }

    // Borra todos los elementos de la lista en O(n) si existen. (Lista lineal)
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

    // Inserta un nodo con valor `value` al final de la lista en O(1) (Lista lineal)
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

    // Regresa el valor del k-ésimo (0-indexado) nodo en O(n) (Notar que empieza desde head)
    int kth_element(size_t k) {
        // Vale la pena implementar el caso en que el índice esté fuera de rango. k >= sz

        list_node *nodo = head;
        for(size_t i=0;i<k;i++){
            nodo = nodo->next;
        }

        return nodo->value;
    }

   // Destruye un nodo de la lista en O(1) (Lista circular y lineal)
    void pop_node(list_node *node){

        // Si no hay nada que borrar
        if(node == nullptr){
            return;
        }

        ///// CASOS ESPECIALES LISTA CIRCULAR /////

        // Si el nodo apunta así mismo (es solo un nodo)
        if(circular ==  1 && node  == node->next){
            delete node;
            head = nullptr;
            sz--;
            return;
        }
            
        // Si hay más de un nodo y hay que eliminar a head
        if(circular == 1 && node == head){
            head = head->next;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            sz--;
            return;
        }

        ///// INSTRUCCIONES VÁLIDAS TANTO PARA LISTA LINEAL COMO CIRCULAR /////

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
        return;
   
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

    // Hacemos que la lista sea circular
    mi_lista.make_circular();

    // Empezamos dessde head
    list_node *actual = mi_lista.get_head();

    // Mientras haya más de un nodo
    while(actual != actual->next){

        // Rendimiento. Para no hacer exceso de iteraciones. Recordar que iteramos sobre un círculo.
        int pasos = k % (int)mi_lista.size();

        // Hacemos los pasos de forma que el nodo a eliminar sea el previo del nodo `actual`.
        // Esto por que en la siguiente iteración comenzamos a contar desde el nodo `actual`.
        for(int i=0;i<=pasos;i++){
            actual = actual->next;
        }

        // Nodo a eliminar
        list_node *muere = actual->prev;

        // Mensaje a pantalla
        // cout << "muere el nodo " << muere->value << endl;

        // Borramos
        mi_lista.pop_node(muere);

        // Imprimir lista actual (visualización vertical)
        // for(int i=0;i<mi_lista.size();i++){
        //     cout << mi_lista.kth_element(i) << endl;
        // }
    }

    // Mensaje a pantalla sobreviviente
    // cout << "sobrevive el nodo "; 
    cout << actual->value << endl;

    // El destructor está implementado para listas lineales. Hay que convertir a lista lineal.
    mi_lista.make_linear();

    return 0;
}