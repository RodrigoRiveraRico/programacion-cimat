#include <stdio.h>

/**
 * @brief Función recursiva del algoritmo de Euclides para calcular el máximo común divisor mcd(a,b).
 * 
 * Si a > b, entonces mcd(a,b) = mcd(b, a mod b)
 * 
 * @param a unsigned long Número.
 * @param b unisgned long Número.
 * @return unisgned long Máximo Común Divisor mcd(a,b).
 * 
 * @note El usuario debe garantizar que ambos parámetros no sean cero al mismo tiempo.
 */
unsigned long euclidesRecursivo(unsigned long a, unsigned long b);

int main(void){

    unsigned long a,b;
    scanf("%lu", &a);
    scanf("%lu", &b);

    printf("%lu", euclidesRecursivo(a,b));

    return 0;
}

unsigned long euclidesRecursivo(unsigned long a, unsigned long b){

    // Convención: mcd(100, 0) = 100
    // El caso base de la recursión es b == 0
    if(a==0 || b==0){
        return a > b ? a : b;
    }

    unsigned long aux;
    if(a < b){
        aux = b;
        b = a;
        a = aux; 
    }

    return euclidesRecursivo(b, a % b);
}