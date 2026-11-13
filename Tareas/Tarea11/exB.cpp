#include <iostream>
#include <vector>

void mostrarVector(const std::vector<int>& v){
    size_t num_elementos = v.size();
    // std::cout << "[";
    for(size_t i=0; i<num_elementos; i++)
        std::cout << v[i] << " ";
    // std::cout << "]";
    std::cout << "\n";
}

void shellsort(std::vector<int>& v) {

    size_t N = v.size();

    // Iteración sobre cada salto
    for(size_t gap = N/2; gap > 0; gap/=2){

        // Iteración sobre cada elemento consecutivo a partir del índice gap
        for(size_t i=gap; i<N; i++){

            // Valor del elemento actual
            int key = v[i];

            // Índice del elemento gap-unidades anterior
            int j = i - gap; // Usamos int para poder asignar valores negativos

            // Seletion sort considerando el gap hacia atrás
            while(j>=0 && v[j]>key){

                v[j+gap] = v[j];

                j = j - gap;
            }

            v[j+gap] = key;

        }

        if(gap==N/2){
            // Mostrar vector después de hacer sort cuando gap == N/2
            mostrarVector(v);
        }

    }
}

int main(){

    // Número de elementos
    size_t N;
    std::cin >> N;

    // Declaración del vector
    std::vector<int> arreglo(N);

    // Llenado del vector
    for(size_t i=0;i<N;i++){
        std::cin >> arreglo[i];
    }

    shellsort(arreglo);
    mostrarVector(arreglo);

    return 0;
}

/*
8
9 8 3 7 5 6 4 1
*/