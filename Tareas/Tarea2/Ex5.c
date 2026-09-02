#include <stdio.h>

int main(void){
    unsigned int t,l,r,suma;

    scanf("%u",&t);
    for(int i=0;i<t;i++){
        suma = 0;
        scanf("%u",&l);
        scanf("%u",&r);

        for(int j=l;j<=r;j++){
            if(j%3!=0 && j%5==3){
                suma+=j;
            }
        }
        printf("%u\n",suma);
    }

    return 0;
}