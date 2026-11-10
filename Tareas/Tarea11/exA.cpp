#include <iostream>
#include <vector>
#include <algorithm> // Para función min()

void mostrarVector(const std::vector<int>& v){
    size_t num_elementos = v.size();
    // std::cout << "[";
    for(size_t i=0; i<num_elementos; i++)
        std::cout << v[i] << " ";
    // std::cout << "]";
    std::cout << "\n";
}

void merge(std::vector<int>& v, size_t left, size_t mid, size_t right){

    // Número de elementos mitad izquierda
    size_t n1 = mid - left + 1;
    // Número de elementos mitad derecha
    size_t n2 = right - mid;

    // Vectores temporales. L : mitad izquierda. R : mitad derecha.
    std::vector<int> L(n1), R(n2);

    // Copiamos data en los vectores temporales
    for(size_t i=0; i<n1; i++){
        L[i] = v[left + i];
    }
    for(size_t j=0; j<n2; j++){
        R[j] = v[mid + 1 + j];
    }
    
    // Índices para movernos en los vectores
    size_t i=0;
    size_t j=0;
    size_t k=left;

    // Hacemos merge ordenando el vector original
    while(i<n1 && j <n2){
        if(L[i]<=R[j]){
            v[k] = L[i];
            i++;
        }
        else{
            v[k] = R[j];
            j++;
        }
        k++;
    }

    // Colocamos los elementos restantes de L[]
    while(i<n1){
        v[k] = L[i];
        i++;
        k++;
    }

    // Colocamos los elementos restante de R[]
    while(j<n2){
        v[k] = R[j];
        j++;
        k++;
    }
}

int main(){

    size_t N;
    std::cin >> N;

    // Vector de tamaño N
    std::vector<int> numeros(N);

    // Llenado del vector
    for(size_t i=0; i<N; i++)
        std::cin >> numeros[i];

    // Empezamos con un ancho de 2 elementos
    size_t ancho = 2;

    // Condición para el ancho
    while(ancho < 2*N){

        // Iteración sobre el vector
        size_t left = 0;
        while(left < N){

            // Función mínimo para no salirnos del vector
            size_t right = std::min(left + ancho - 1, N-1);
            size_t mid = left + ancho/2 - 1;

            // std::cout << left << " " << mid << " " << right << " " << "\n";

            // Verificamos que existan elementos en ambas mitades
            if(mid < right){
                merge(numeros, left, mid, right);
            }
            
            // Inicio del siguiente bloque de tamaño igual al ancho
            left += ancho;
        }
        // Vector ordenado después de tomar bloques de ancho igual a 2
        if(ancho==2){
            mostrarVector(numeros);
        }

        // Aumentamos el ancho
        ancho*=2;
    }
    mostrarVector(numeros);

    return 0;
}

/*
10
38 10 11 82 9 3 43 27 2 1

11
38 10 11 82 9 3 43 27 2 1 0

5
5 4 3 2 1

11
11 10 9 8 7 6 5 4 3 2 1

4
2 3 4 1

7
38 27 43 3 9 82 10
*/