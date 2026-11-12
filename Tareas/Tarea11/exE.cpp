#include <iostream>
#include <vector>

void mostrarMatriz(std::vector<std::vector<int>> M, size_t row, size_t col){
    for(size_t i=0;i<row;i++){
        for(size_t j=0; j<col;j++){
            std::cout << M[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool hasCycle(size_t nodo, int padre, std::vector<bool>& visitados, const std::vector<std::vector<int>>& adj){
    visitados[nodo] = true;
    size_t N = adj.size();

    for(size_t i = 0; i < N; ++i){
        // Verificamos si existe una arista entre el nodo actual y el nodo 'i'
        if(adj[nodo][i] == 1){
            // Si el vecino es el padre, lo ignoramos
            if(static_cast<int>(i) == padre){
                continue;
            }

            // Si no ha sido visitado, exploramos recursivamente
            if(!visitados[i]){
                if(hasCycle(i, static_cast<int>(nodo), visitados, adj)){
                    return true;
                }
            } 
            // Si ya fue visitado y no es el padre, encontramos un ciclo
            else {
                return true;
            }
        }
    }
    return false;
}

int main(){
    
    // Número de nodos
    size_t n;
    std::cin >> n;
    // Número de enlaces
    size_t m;
    std::cin >> m;

    // Matriz : Vector de vectores
    // Matriz de adyacencia
    std::vector<std::vector<int>> adj(n, std::vector<int>(n,0)); // Matriz de nxn inicializada en ceros

    // Llenar matriz
    for(size_t t=0; t<m; t++){
        size_t nodoA, nodoB;
        std::cin >> nodoA >> nodoB;

        // Matriz simétrica
        adj[nodoA-1][nodoB-1] = 1;
        adj[nodoB-1][nodoA-1] = 1;
    }

    // mostrarMatriz(adj, n, n);

    // Vector de nodos visitados
    std::vector<bool> visitados(n, false);

    size_t u;
    for(u=0; u<n; u++){
        // Si no ha sido visitado
        if(visitados[u] == false){
            if(hasCycle(u, -1, visitados, adj) == true){
                std::cout << "YES";
                break;
            }
        }
    }
    if(u==n){
        std::cout << "NO";
    }

    return 0;
}
/*
4 4
1 2
2 3
3 4
4 2
> YES

6 5
1 3
3 2
5 3
4 5
5 6
> NO
*/