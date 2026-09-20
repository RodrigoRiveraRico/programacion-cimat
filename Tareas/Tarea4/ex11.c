#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long aleatorio(unsigned d);

int main(void){

    // Probar función
    srand(time(NULL));

    for(unsigned d=1;d<=18;d++){
        printf("%llu\n",aleatorio(d));
    }

    // Mensaje para omegaup
    // printf("(2^31)-1 = TOO SMALL");

    return 0;
}

unsigned long long aleatorio(unsigned d){

    unsigned long long resultado = 0;

    resultado = (rand() % 9) + 1; // El dígito más significativo (el primero de la izquierda) está entre 1 y 9.

    for(int i=1;i<d;i++){

        resultado = resultado * 10 + (rand() % 10); // Multiplicar por 10 el resultado anterior es equivalente a desplazar los dígitos un espacio a la izquierda.
    }

    return resultado;
}