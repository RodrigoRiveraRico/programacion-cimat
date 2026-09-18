#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float error(float *sol, float *b, int dim);

int main(void){
    int n;
    float **L,*b,*x,*Lx;

    // Asignación dinámica de memoria
    // printf("\nIngresa n: ");
    scanf("%d",&n);

    L = malloc(n * sizeof(float *));
    if(!L){return 1;}
    for(int i=0;i<n;i++){
        L[i] = malloc((i+1)*sizeof(float));
        if(!L[i]){
            for(int k=0;k<i;k++){
                free(L[k]);
            }
            free(L);
            return 1;
        }
    }

    b = malloc(n*sizeof(float));
    if(!b){
        for(int k=0;k<n;k++){
            free(L[k]);
        }
        free(L);
        return 1;
    }

    x = malloc(n*sizeof(float));
    if(!x){
        for(int k=0;k<n;k++){
            free(L[k]);
        }
        free(L); free(b);
        return 1;
    }

    Lx = malloc(n*sizeof(float));
    if(!Lx){
        for(int k=0;k<n;k++){
            free(L[k]);
        }
        free(L); free(b); free(x);
        return 1;
    }

    // Entradas a consola
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            // printf("\nIngresa L %d%d ",i,j);
            scanf("%f",&L[i][j]);
        }
    }
    
    for(int i=0;i<n;i++){
        // printf("\nIngresa b %d ",i);
        scanf("%f",&b[i]);
    }

    // Solución al sistema Lx = b
    float suma;
    for(int i=0;i<n;i++){
        suma = 0;
        for(int j=0;j<i;j++){
            suma+=L[i][j]*x[j];
        }
        x[i]=(b[i]-suma)/L[i][i];
    }

    // Salida a consola de la solución Lx = b
    for(int i=0;i<n;i++){
        printf("\n%f ",x[i]);
    }

    // Cálculo del vector Lx
    for(int i=0;i<n;i++){
        Lx[i] = 0;
        for(int j=0;j<=i;j++){
            Lx[i] += L[i][j] * x[j];
        }
    }

    // Salida a consola del error de comprobación
    float e = error(Lx, b, n);
    printf("\n%e",e);

    // Liberamos memoria
    for(int k=0;k<n;k++){
        free(L[k]);
    }
    free(L); free(b); free(x); free(Lx);
    return 0;
}

float error(float *sol, float *b, int dim){

    float e = 0.0f;

    for(int i=0;i<dim;i++){
        e += fabsf(sol[i] - b[i]);
    }

    return e;
}