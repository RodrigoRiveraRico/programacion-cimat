#include <stdio.h>

/** @brief Función que copia una cadena.
 * 
 * La función recibe el apuntador a destino e internamente hace la copia de la cadena.
 * 
 * @param dest Apuntador destino
 * @param src Apuntador origen
 * 
 * @return void
*/
void my_strcpy(char *dest, const char *src);

int main(void){

    // Tamaño cadena original
    int n;
    scanf("%d",&n);

    // Cadena original de tamaño n más terminador '\0'
    char src[n+1];
    scanf("%s",src);

    // Cadena destino, copia exacta de la original
    char dest[n+1];

    // Imprimimos cadena desde el destino
    my_strcpy(dest, src);
    printf("%s",dest);

    return 0;
}

void my_strcpy(char *dest, const char *src){
    int i=0;

    while(src[i]!='\0'){
        dest[i]=src[i];
        i++;
    }
    dest[i]='\0';
}