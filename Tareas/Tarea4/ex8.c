#include <stdio.h>
#include <stdlib.h>

#define SI "\nYES"
#define NO "\nNO"

/// @brief Determina si la cadena t aparece al menos una vez en la cadena s
/// @param s Cadena base
/// @param n Tamaño de la cadena
/// @param t Cadena para comparar
/// @return "YES" si la cadena t es subcadena de s; "NO" en caso contario
void comparacion(char *s, unsigned n, char *t);

int main(void){

    // Leer longitud de la cadena
    unsigned n;
    scanf("%u",&n);
    
    // Leer la cadena de longitud n
    char string[n+1]; // +1 para '\0'.
    scanf("%s",string);

    // Cantidad q de preguntas
    unsigned q;
    scanf("%u",&q);

    // Apuntador a string
    char *pts=NULL;
    for(int i=0;i<q;i++){
        // Leer m que es la longitud de cadenas a comparar
        unsigned m;
        scanf("%u",&m);

        pts = malloc((m+1) * sizeof *pts);
        if(!pts){return 1;}
        // Leer la cadena de longitud m
        scanf("%s",pts);

        // Comparación...
        comparacion(string, n, pts);

        free(pts); pts=NULL;
    }
    return 0;
}

void comparacion(char *s, unsigned n, char *t){

    int i=0;
    int j=0;
    while(s[i]!='\0'){
        // Caso en que estemos comparando desde el inicio de cadena t
        if(j==0){
            if(s[i]==t[j]){
                j++;
                i++;
                if(t[j]=='\0'){
                    printf(SI);
                    return;
                }
            }
            else{
                // Solo avanzamos el índice de la cadena s
                i++;
            }
            continue;
        }
        // Caso en que estemos comparando después del inicio de cadena t
        if(s[i]==t[j]){
            j++;
            i++;
            if(t[j]=='\0'){
                printf(SI);
                return;
            }
        }
        else{
            // Volvemos al inicio de cadena t
            // La siguiente búsqueda la hacemos desde el último indice i revisado de la cadena s
            j=0;
        }
    }
    printf(NO);
    return;
}
