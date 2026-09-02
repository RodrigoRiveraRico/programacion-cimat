#include <stdio.h>

int main(void){
    int n;
    int disponibles;
    int inOut;
    const char *veredicto = "NO"; // Puntero a caracter constante

    scanf("%d",&n);
    disponibles = n;
    scanf("%d",&inOut);

    while(inOut!=2){
        disponibles += inOut == 1 ? -1 : 1;
        scanf("%d",&inOut);

        if(disponibles<0){
            veredicto = "SI";
            break;
        }
    }
    while(inOut!=2){
        scanf("%d",&inOut);
        continue;
    }
    printf("%s",veredicto);

    return 0;
}