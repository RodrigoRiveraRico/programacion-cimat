#include <stdio.h>

int main(void){
    unsigned int l,r;
    unsigned int suma=0;

    scanf("%u",&l);
    scanf("%u",&r);

    suma = r*(r+1)/2 - (l-1)*(l)/2;
    // printf("%u\n",suma);

    for(int i=l;i<=r;i++){
        // Comillas simples para %c <-- caracter
        // Comillas dobles para %s <-- cadena
        printf(suma%i==0 ? "YES\n" : "NO\n");
    }

    return 0;
}