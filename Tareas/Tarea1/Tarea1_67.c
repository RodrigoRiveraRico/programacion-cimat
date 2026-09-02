#include <stdio.h>

int main(void){

    int n,m,x;
    double tasa_mensual = 0.005; 
    int cont = 0;
    double total;
    
    scanf("%d",&n);
    scanf("%d",&m);
    scanf("%d",&x);

    total = n;
    printf("%d %f",cont, total);
    do{
        printf("\n");
        total = total*(1+tasa_mensual)+m;
        cont++;
        printf("%d %f",cont, total);
    }while(total < x);

    return 0;
}