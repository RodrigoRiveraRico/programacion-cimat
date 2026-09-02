#include <stdio.h>

int main(void){
    char C;
    char S[30];
    int D;
    unsigned int U;
    float F;

    scanf("%c %s %d %u %f",&C,&S,&D,&U,&F);
    printf("[%c] Servidor: %s | Temp: %dC | HexID: %x | Load: %e%%",C,S,D,U,F);

    return 0;
}