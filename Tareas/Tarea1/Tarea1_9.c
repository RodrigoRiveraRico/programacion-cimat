#include <stdio.h>

int main(void){
    unsigned short base = 1024; // %hu
    unsigned long res; // %lu

    for(unsigned short i=1;i<101;i++){
        res = base * i;
        printf("\n %hu * %3hu = %lu",base,i,res);
    }
    return 0;
}