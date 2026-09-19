#include <stdio.h>

void print_float_bits(float);

int main(void){

    float flotante;
    scanf("%f",&flotante);

    print_float_bits(flotante);

    return 0;
}

void print_float_bits(float f){

    // Apunta a un flotante
    // Los bits se entienden en el estándar IEEE-754
    float *dirMem = &f;

    unsigned int *casteo;
    // Reinterpretación: Apunta a un entero sin signo de 32 bits
    // Los bits se entienden como un número binario de toda la vida.
    casteo = (unsigned int *)dirMem;

    // Desreferenciación: 32 bits
    unsigned int bits = *casteo;

    // Vamos desde el bit más significativo al menos significativo (izquierda a derecha)
    for (int i = 31; i >= 0; i--) {
        // Movemos el bit de interés i-posiciones a la derecha hasta alcanzar la posición cero.
        // En esta posición hacemos operador & con el bit 1
        // Si la operación es 1, entonces el bit de interés está prendido; 0 si el bit de interés está apagado.
        unsigned int bit = (bits >> i) & 1;

        // Imprimir desde el bit más significativo al menos significativo.
        printf("%u", bit);
    }
}
    
