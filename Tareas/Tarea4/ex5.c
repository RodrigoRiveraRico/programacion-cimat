#include <stdio.h>
#include <stdlib.h>

/** @brief Función que calcula la media muestral.
 * 
 * @param datos Apuntador a un arreglo 1D donde están los datos.
 * @param n El tamaño del arreglo.
 * 
 * @return La media muestral.
 */
double media(double *datos, int n);

/** @brief Función que calcula la varianza muestral.
 * 
 * @param datos Apuntador a un arreglo 1D donde están los datos.
 * @param n El tamaño del arreglo.
 * 
 * @return La varianza muestral.
 */
double varianza(double *datos, int n);

int main(void){
    
    // Leer n
    int n;
    scanf("%d",&n);

    // Leer datos
    // Memoria dinámica
    double *datos=NULL;
    datos = malloc(n* sizeof *datos);
    if(!datos){
        return 1;
    }
    for(int i=0;i<n;i++){
        scanf("%lf",datos+i);
    }

    // Imprimimos la varianza muestral
    double var = varianza(datos, n);
    printf("%.4f",var);

    free(datos);
    return 0;
}

double media(double *datos, int n)
{
    double suma=0.0;
    for(int i=0;i<n;i++){
        suma += datos[i];
    }
    return suma/(double)n;
}

double varianza(double *datos, int n)
{
    double suma=0.0;
    double mu = media(datos,n);

    for(int i=0;i<n;i++){
        double diferencia = datos[i]-mu;
        suma += (diferencia)*(diferencia);
    }

    return suma/(double)(n-1);
}