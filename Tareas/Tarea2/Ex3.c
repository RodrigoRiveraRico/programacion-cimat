#include <stdio.h>

int esPar(unsigned int);

int main(void){

    unsigned int t; // %u
    unsigned int n;
    unsigned int m;
    unsigned int potencia;
    unsigned int divide_n;

    scanf("%u",&t);
    

    for(int i=0;i<t;i++){
        scanf("%u",&n);
        potencia = 2;

        if(esPar(n)){
            while(potencia <= n ){
                if(n % potencia == 0){
                    divide_n = potencia;
                }
                potencia *= 2;
            }
            printf("%u\n",divide_n);
        }
        else{
            m = n+2;
            printf("%u\n",m % 3 == 0 ? 8*m : m*m);
        }
    }

    return 0;
}

int esPar(unsigned int n){
    return n % 2 == 0 ? 1 : 0;
}