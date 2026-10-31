#include <iostream>
#include <cstdlib>  // Para int abs()

class Nodo{
    public:
        // Miembros
        int mmr;
        Nodo* izq;
        Nodo* der;

        // Constructor
        Nodo(int val) : mmr(val), izq(nullptr), der(nullptr) {}
};

class MatchmakingBST {
private:
    Nodo* Raiz;
    int Rango_mmr;
    const int RANGO_INICIAL;
    const int PASO_INCREMENTO;
    bool borrar(Nodo*, int){}
    bool insertar_emparejar(Nodo*, int){}
public:
    // Constructor
    MatchmakingBST(int rank, int step) : Raiz(nullptr), Rango_mmr(rank), RANGO_INICIAL(rank), PASO_INCREMENTO(step) {}

    // Destructor
    //~TMatchmakingBST(){}

    // Tenemos tres casos:
    // 1. El nodo está aterrizado : agregamos nuevo nodo.
    // 2. NO se cumple la condición de match : hay que continuar bajando.
    // 3. SÍ se cumple la condición de mathc : eliminar nodo del árbol. 
    void agregarJugador(Nodo*& root, int mmr)
    {   
        // Caso base: si el árbol está vacío o se llegó a un hijo nulo, crear el nodo
        if(root == nullptr){
            root = new Nodo(mmr);
            Rango_mmr += PASO_INCREMENTO;
        }

        else if(match(mmr, root->mmr) == 0){

            if(mmr < root->mmr){
                agregarJugador(root->izq, mmr);
            }

            else {
                agregarJugador(root->der, mmr);
            }
        }

        else{
            Nodo* contrincante = sacarJugador(root);
            Rango_mmr = RANGO_INICIAL;
        }

    }
    
    Nodo* sacarJugador(Nodo*& nodo){

        // Si es nodo hoja
        if(nodo->izq == nullptr && nodo->der == nullptr){
            delete nodo;
            return nullptr;
        }
        
        // Si tiene ambos hijos
        else if(nodo->izq != nullptr && nodo->der != nullptr){

        }

        // Si solo tiene un hijo
        else{
            Nodo* aux = nodo;
            if(nodo->izq != nullptr){
                
            }
            else(nodo->der != nullptr){

            }

        }

    }


    bool match(int X, int Y){
        return std::abs(X-Y) < Rango_mmr;
    }
};



int main(){


    return 0;
}