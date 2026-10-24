#include <iostream>

template <typename T>
class Par {
private:
    T positivo;
    T negativo;
public:
    Par(T numero) : positivo(numero), negativo(-numero) {}

    void printValues() {std::cout << "Positivo: " << positivo << " Negativo: " << negativo << std::endl;}

    void imprimirBits();
};

int main(){

    // Cantidad de elementos
    unsigned t;
    std::cin >> t;

    for(int i=0;i<t;i++){

        // precision = 1 para 16 bits
        // precision = 2 para 32 bits
        unsigned precision;
        std::cin >> precision;
    
        // 16 bits <short>
        if(precision == 1){

            short numero;
            std::cin >> numero;

            Par<short> base_10(numero);
            base_10.imprimirBits();
        }

        // 32 bits <int>
        if(precision == 2){

            int numero;
            std::cin >> numero;

            Par<int> base_10(numero);
            base_10.imprimirBits();
        }        
    }
    return 0;
}

template <typename T>
void Par<T>::imprimirBits()
{
    int numBits = sizeof(T) * 8; // Multiplicación por 8 ya que hay 8 bits/byte

    // Número positivo
    for(int i=numBits-1; i>=0; i--){
        short bit = (positivo >> i) & 1;
        std::cout << bit;
    }
    std::cout << std::endl;

    // Número negativo
    for(int i=numBits-1; i>=0; i--){
        short bit = (negativo >> i) & 1;
        std::cout << bit;
    }
    std::cout << std::endl;
}
