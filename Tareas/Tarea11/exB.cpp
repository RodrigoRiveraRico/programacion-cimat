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
            size_t j = i - gap;
            std::cout << j << " ";

            // Seletion sort considerando el gap hacia atrás
            while(j>=0 && v[j]>key){

                v[j+gap] = v[j];

                j = j - gap;    // Size_t no puede ser negativo!!
            }
            
        }
        std::cout << "\n";

    }
}

int main(){
    

    std::vector<int> arr = {12, 34, 54, 2, 3};

    shellsort(arr);

    return 0;
}