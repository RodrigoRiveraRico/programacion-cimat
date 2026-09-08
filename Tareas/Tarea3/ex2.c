#include <stdio.h>

int main(void){

    unsigned char bytes[4]; // Cada entrada es 1Byte

    for(int i=0;i<4;i++){
        int temp;   // La entrada en consola la guardamos como int
        scanf("%d",&temp);
        bytes[i] = (unsigned char)temp;
    }
    
    unsigned int K;
    scanf("%u",&K);

    unsigned int *casteo;
    casteo = (unsigned int *)bytes; // Interpretamos los 4 bloques de 1Byte en 1 bloque de memoria de 4Bytes.

    unsigned int X;
    X = *casteo;

    // printf("En hexadecimal: 0x%X\n", X);

    unsigned int Y = ((X & 0xFFFF0000) >> 16) | ((X & 0x0000FFFF) << 16);

    printf(Y == K ? "SI" : "NO");

    return 0;
}