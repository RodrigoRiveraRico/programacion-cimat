#include <iostream>
#include <cstdlib>  // Para int abs()

// Compilar con AddressSanitizer
// g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined main.cpp -o programa

/** Clase nodo */
class Nodo{
    public:
        // Miembros
        int mmr;    /**< Matchmaking Rating */
        Nodo* izq;  /**< Nodo a la izquierda */
        Nodo* der;  /**< Nodo a la derecha */

        // Constructor
        Nodo(int val) : mmr(val), izq(nullptr), der(nullptr) {}
};

/** Clase árbol de búsqueda binario 
 *  @note  Variable tipo const : obligatorio inicializar en lista de inicialización 
*/
class MatchmakingBST {
private:
    Nodo* Raiz;                     /**< Nodo raíz */
    int Rango_mmr;                  /**< Valor actual Matchmaking Rating del árbol */
    const int RANGO_INICIAL;        /**< Valor Matchmaking Rating base */
    const int PASO_INCREMENTO;      /**< Incremento de Matchmaking Rating */

    /**
     * @brief Función recursiva para insertar o emparejar un jugador.
     * 
     * Siempre que llega un nuevo jugador se recorre el árbol desde la raíz hasta las hojas.
     * 
     * Si no hay emparejamiento: el nuevo jugador es un nodo hoja y se incrementa el Rango_mmr
     * 
     * Si hay emparejamiento: se saca del árbol el nodo jugador con quien hubo emparejamiento, no se inserta el nuevo jugador y se reinicia el valor Rango_mmr al inicial.
     * @param root Nodo* Referencia al nodo raíz del subárbol
     * @param mmr int Valor Matchmaking Rating
     * @note Notar que la referencia Nodo*& permite modificar directamente el apuntador que conecta nodo padre con nodo hijo.
     * @note En privado para que este método no se pueda llamar fuera de la clase.
     */
    void insertarEmparejarRecursivo(Nodo*& root, int mmr){

        // Insertar nuevo jugador
        if(root == nullptr){
            root = new Nodo(mmr);
            Rango_mmr += PASO_INCREMENTO;
            return;         // Por claridad hacemos explícita la salida recursiva
        }
        
        // Se encontró un match (emparejar) : sacar jugador del árbol
        if(match(mmr, root->mmr) == 1){

            std::cout << "Partida encontrada: " << mmr << " vs " << root->mmr << std::endl;

            sacarJugador(root);
            Rango_mmr = RANGO_INICIAL;
            return;         // Por claridad hacemos explícita la salida recursiva
        }

        // Recursividad
        if(mmr < root->mmr){
            insertarEmparejarRecursivo(root->izq, mmr);
        }
        else{
            insertarEmparejarRecursivo(root->der, mmr);
        }
    }

    /**
     * @brief Función para quitar del árbol un nodo jugador preservando la estructura de árbol
     * 
     * Comprueba los tres casos: nodo hoja, nodo con 1 hijo o nodo con 2 hijos.
     * 
     * @param nodo Nodo* Referencia al nodo que se quiere quitar
     * @note Para el caso en que se tiene dos hijos se asgina el valor del nodo sucesor in-order
     */
    void sacarJugador(Nodo*& nodo){

        // Si tiene un hijo o es nodo hoja
        if(nodo->izq == nullptr){
            Nodo* temp = nodo;
            nodo = nodo->der;
            delete temp;
        }

        else if(nodo->der == nullptr){
            Nodo* temp = nodo;
            nodo = nodo->izq;
            delete temp;
        }

        // Entonces tiene dos hijos
        else{
            nodo->mmr = eliminarMinimoRecursivo(nodo->der);
        }
    }

    /**
     * @brief Función recursiva para tratar el caso en que se quiere eliminar un nodo que tiene dos hijos.
     * 
     * Esta función busca el mínimo del subárbol, guarda el valor del mínimo y elimina el nodo preservando la estructura (si es que el nodo mínimo tiene hijo a la derecha)
     * 
     * @param nodo Nodo* Referencia al nodo que se quiere quitar del árbol
     * @return int El valor del mínimo
     */
    int eliminarMinimoRecursivo(Nodo*& nodo){

        if(nodo->izq == nullptr){

            Nodo* temp = nodo;
            int valor = nodo->mmr;

            nodo = nodo->der;
            delete temp;

            return valor;
        }

        return eliminarMinimoRecursivo(nodo->izq);
    }

    // Función para borrar subárbol binario en postorden con parámetro por referencia
    void liberarArbol(Nodo*& root){

        if(root == nullptr){
            return;
        }

        // Liberar subárbol izquierdo
        liberarArbol(root->izq);

        // Liberar subárbol derecho
        liberarArbol(root->der);

        // Liberar raíz
        delete root;

        // Aterrizar apuntador
        root = nullptr;
    }
    
    /** @brief Función booleana 
     * 
     * Criterio de match para insertar o emparejar jugadores
     * @param X int Valor Matchmaking Rating de un jugador
     * @param Y int Valor Matchmaking Rating de otro jugador
     * @return bool 
    */
    bool match(int X, int Y){
        return std::abs(X-Y) <= Rango_mmr;
    }

public:
    // Constructor
    MatchmakingBST(int rank, int step) : Raiz(nullptr), Rango_mmr(rank), RANGO_INICIAL(rank), PASO_INCREMENTO(step) {}

    // Destructor
    ~MatchmakingBST(){ liberarArbol(Raiz); }

    /** @brief Método para insertar o emparejar jugadores 
     * 
     * Observar que al llamar este método solo necesitas indicar el entero mmr. 
     * 
     * Ejemplo : matchmakingBST.insertarEmparejar(100);
     * @param mmr int Matchmaking Rating del jugador
    */
    void insertarEmparejar(int mmr){
        insertarEmparejarRecursivo(Raiz, mmr);
    }
};

int main(){

    // Cantidad de jugadores
    int N;
    std::cin >> N;

    // Rango base de tolerancia
    int rango_inicial;
    std::cin >> rango_inicial;

    // Incremento de tolerancia
    int paso_incremento;
    std::cin >> paso_incremento;

    // Inicialización árbol (vacío)
    MatchmakingBST matchmakingBST(rango_inicial, paso_incremento);

    // Recorrido en el árbol
    for(int i=0;i<N;i++){

        // Puntaje MMR del jugador que acaba de entrar a la fila de matchmaking
        int X;
        std::cin >> X;

        matchmakingBST.insertarEmparejar(X);
    }

    return 0;
}