#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h> // Para usar DBL_MAX o un valor mínimo inicial

/////////////////////////////////////////////////////////////

typedef struct{
    int x;
    int y;
}point2D;

/////////////////////////////////////////////////////////////

double derivable(point2D);
double silla(point2D);
double ondas(point2D);
double himmelblau(point2D);
double gaussiana(point2D);

/////////////////////////////////////////////////////////////

void maximo(int a_x, int a_y, int b_x, int b_y, double *f_max, int *x_max, int *y_max, double (*f)(point2D));
void minimo(int a_x, int a_y, int b_x, int b_y, double *f_min, int *x_min, int *y_min, double (*f)(point2D));

/////////////////////////////////////////////////////////////

int main(void){

    // Primer intervalo
    int a_x, b_x;

    // Segundo intervalo
    int a_y, b_y;

    char funcion_nombre[11];

    scanf("%d %d", &a_x, &b_x);
    scanf("%d %d", &a_y, &b_y);
    getchar();
    scanf("%s",funcion_nombre);

    // Para el máximo
    double *f_max = malloc(sizeof *f_max);
    if(!f_max){return 1;}

    int *x_max = malloc(sizeof *x_max);
    if(!x_max){free(f_max); return 1;}

    int *y_max = malloc(sizeof *y_max);
    if(!y_max){free(x_max); free(f_max); return 1;}

    // Apuntador al mínimo
    double *f_min = malloc(sizeof *f_min);
    if(!f_min){free(y_max); free(x_max); free(f_max); return 1;}

    int *x_min = malloc(sizeof *x_min);
    if(!x_min){free(f_min); free(y_max); free(x_max); free(f_max); return 1;}

    int *y_min = malloc(sizeof *y_min);
    if(!y_min){free(x_min); free(f_min); free(y_max); free(x_max); free(f_max); return 1;}

    /////////////////////////////////////////////////////////////

    if(strcmp(funcion_nombre, "derivable") == 0){
        maximo(a_x, a_y, b_x, b_y, f_max, x_max, y_max, derivable);
        minimo(a_x, a_y, b_x, b_y, f_min, x_min, y_min, derivable);
    }
    else if(strcmp(funcion_nombre, "silla") == 0){
        maximo(a_x, a_y, b_x, b_y, f_max, x_max, y_max, silla);
        minimo(a_x, a_y, b_x, b_y, f_min, x_min, y_min, silla);
    }
    else if(strcmp(funcion_nombre, "ondas") == 0){
        maximo(a_x, a_y, b_x, b_y, f_max, x_max, y_max, ondas);
        minimo(a_x, a_y, b_x, b_y, f_min, x_min, y_min, ondas);
    }
    else if(strcmp(funcion_nombre, "himmelblau") == 0){
        maximo(a_x, a_y, b_x, b_y, f_max, x_max, y_max, himmelblau);
        minimo(a_x, a_y, b_x, b_y, f_min, x_min, y_min, himmelblau);
    }
    else if(strcmp(funcion_nombre, "gaussiana") == 0){
        maximo(a_x, a_y, b_x, b_y, f_max, x_max, y_max, gaussiana);
        minimo(a_x, a_y, b_x, b_y, f_min, x_min, y_min, gaussiana);
    }

    free(y_min); free(x_min); free(f_min); free(y_max); free(x_max); free(f_max);
    return 0;
}

double derivable(point2D p){
    int x = p.x;
    int y = p.y;
    return 2.0*x*x + 3.5*y*y*y;
}
double silla(point2D p){
    int x = p.x;
    int y = p.y;
    return x*x - y*y;
}
double ondas(point2D p){
    int x = p.x;
    int y = p.y;
    return cos(sqrt(x*x + y*y)) + 0.1*sqrt(x*x + y*y);
}
double himmelblau(point2D p){
    int x = p.x;
    int y = p.y;
    return (x*x+y-11)*(x*x+y-11) + (x+y*y-7)*(x+y*y-7);
}
double gaussiana(point2D p){
    int x = p.x;
    int y = p.y;
    return 100.0*exp(-0.05*(x*x+y*y));
}

void maximo(int a_x, int a_y, int b_x, int b_y, double *f_max, int *x_max, int *y_max, double (*f)(point2D)){

    // Ini del valor en f_max
    // DBL_MAX es una constante en C y C++ que representa el valor máximo positivo que puede almacenar un número de punto flotante de doble precisión (double).
    *f_max = -__DBL_MAX__;

    for(int i=a_y;i<b_y;i++){         // Eje y
        for(int j=a_x;j<b_x;j++){     // Eje x

            point2D p;
            p.x = j;
            p.y = i;

            double resultado = f(p);

            if(resultado > *f_max){
                *f_max = resultado;
                *x_max = j;
                *y_max = i;
            }
        }
    }
    printf("%d %d %lf\n", *x_max, *y_max, *f_max);
}

void minimo(int a_x, int a_y, int b_x, int b_y, double *f_min, int *x_min, int *y_min, double (*f)(point2D)){

    // Ini del valor en f_max
    // DBL_MAX es una constante en C y C++ que representa el valor máximo positivo que puede almacenar un número de punto flotante de doble precisión (double).
    *f_min = __DBL_MAX__;

    for(int i=a_y;i<b_y;i++){         // Eje y
        for(int j=a_x;j<b_x;j++){     // Eje x

            point2D p;
            p.x = j;
            p.y = i;

            double resultado = f(p);

            if(resultado < *f_min){
                *f_min = resultado;
                *x_min = j;
                *y_min = i;
            }
        }
    }
    printf("%d %d %lf\n", *x_min, *y_min, *f_min);
}