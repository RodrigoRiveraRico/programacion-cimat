#include <stdio.h>
#include <math.h>

int main(void){

    float a,b,c,D,x,y;

    printf("\n Para ax^2 + bx + c = 0  ...");
    printf("\n Ingresa el coeficiente 'a': ");
    scanf("%f",&a);
    printf("\n Ingresa el coeficiente 'b': ");
    scanf("%f",&b);
    printf("\n Ingresa el coeficiente 'c': ");
    scanf("%f",&c);

    D = b*b - 4*a*c;

    if(D<0){
        printf("\n Raices complejas");
    }
    else if(D==0){
        x = -b/(2*a);
        printf("\n Raiz de multiplicidad 2. La raiz es: %f",x);
    }
    else{
        x = (-b + sqrt(D))/(2*a);
        y = (-b - sqrt(D))/(2*a);
        printf("\n La raices son %f y %f", x,y);
    }

    return 0;
}