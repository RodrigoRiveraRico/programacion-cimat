#include <stdio.h>
#include <stdlib.h>

int main(void){

    float x, eval, factor, *coef;
    unsigned int n;

    scanf("%f",&x);
    scanf("%u",&n);

    coef = (float *)malloc((n+1)*sizeof(float));
    if(!coef){
        printf("\nNo hay memoria para almacenar los coeficientes");
        return 1;
    }

    // Guardamos los coeficientes
    // El primer elemento es a_0
    // El último elemento es a_n
    for(int i=0;i<(n+1);i++){
        scanf("%f",&coef[i]);
    }

    // Evaluación polinomio
    eval = 0.0f;
    factor = 1.0f;
    for(int i=0;i<(n+1);i++){
        eval += coef[i] * factor;
        factor *= x;
    }
    printf("\n%.4f",eval);

    // Evaluación derivada
    eval = 0.0f;
    factor = 1.0f;
    for(int i=1;i<(n+1);i++){
        eval += i * coef[i] * factor;
        factor *= x;
    }
    printf("\n%.4f",eval);

    // Coeficientes derivada
    for(int i=1;i<(n+1);i++){
        printf("\n%.4f", i * coef[i]);
    }

    free(coef);
    return 0;
}