#include <stdio.h>

// Función recursiva para convertir decimales a binarios
void decimalToBinary(unsigned dec);

int main(void){

    // Decimal a convertir
    unsigned n;
    scanf("%u",&n);

    decimalToBinary(n);

    return 0;
}

void decimalToBinary(unsigned dec)
{
    if(dec==1 || dec ==0){
        printf("%u",dec);
        return;
    }

    decimalToBinary(dec/2);
    printf("%u",dec%2);
}
