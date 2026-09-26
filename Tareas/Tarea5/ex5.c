/*******
> input:
24
Hello World from omegaUp
3
om?

> output:
o
o
om
om

///////////////7

> input:
20
color olor coor oor
7
c?ol?or

> output:
color
olor
coor
oor
*******/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int boolean;


/// @brief Función recursiva para verificar si el patrón coincide con la cadena en la posición actual.
///
/// Recorremos la cadena s la cantidad de caracteres que tiene el patrón p.
/// La función mira un paso hacia adelante: *(p + 1) == '?'.
/// Si se cumple la condición, el caracter *p puede aparecer o no aparecer.
/// Si *p aparece en s, entonces avanzamos una posición en s y dos posiciones en p. Hacemos recursividad en la posición s+1 y p+2.
/// Si *p no aparece en s, como es un carácter opcional, solo avanzamos en p dos posiciones. Hacemos recursividad en la posición s y p+2.
/// Si *(p + 1) != '?' debe haber coincidencia exacta entre *s y *p.
/// @param s Cadena
/// @param p Cadena Expresión regular (patrón)
/// @return true or false
boolean match_patron(char *s, char *p);

/// @brief Imprimir la subcadena exacta de 's' que hizo match con 'p'
///
/// Imprime carácter por carácter en la consola.
/// @param s Cadena
/// @param p Cadena Expresión regular (patrón)
void imprimir_match(char *s, char *p);

int main() {
    int n, m;

    // Leer longitud de s
    scanf("%d",&n);

    // Reservar memoria para s (+1 para el carácter nulo)
    char *s = malloc((n + 1) * sizeof *s);
    if(!s){
        return 1;
    }
    fgetc(stdin);   // Consumir espacio en blanco entre entradas
    fgets(s, n + 1, stdin); // stdin para leer desde consola

    // Leer longitud de p
    scanf("%d",&m);

    // Reservar memoria para p
    char *p = malloc((m + 1) * sizeof *p);
    if(!p){
        free(s);
        return 1;
    }
    fgetc(stdin);
    fgets(p, m + 1, stdin);


    // Buscar ocurrencias recorriendo cada índice de la cadena s
    for (int i = 0; i <= n; i++){
        if (match_patron(&s[i], p)){
            imprimir_match(&s[i], p);
        }
    }


    free(s);
    free(p);
    return 0;
}

boolean match_patron(char *s, char *p){

    // Caso base.
    // Si llegamos al final del patrón, es una coincidencia exitosa
    if (*p == '\0'){
        return TRUE;
    }

    // Verificar si el siguiente carácter en el patrón es '?'
    if (*(p + 1) == '?'){
        // Opción 1: El carácter anterior (*p) NO aparece (0 veces).
        // Verificamos coincidencia entre *s y *(p+2).
        if (match_patron(s, p + 2)) {
            return TRUE;
        }
        
        // Opción 2: El carácter anterior (*p) SÍ aparece (1 vez).
        // Verificamos coincidencia entre *(s+1) y *(s+2).
        if (*s != '\0' && *s == *p) {
            return match_patron(s + 1, p + 2);
        }
        
        return FALSE;
    }

    // Caso no hay '?' adelante, los caracteres deben ser idénticos.
    if (*s != '\0' && *s == *p) {
        return match_patron(s + 1, p + 1);
    }

    return FALSE;
}

void imprimir_match(char *s, char *p) {

    while (*p != '\0'){
        if (*(p + 1) == '?'){
            // Si el patrón tomó la opción de que el carácter SÍ aparecía
            if (*s == *p){
                putchar(*s); // escribe un único carácter en la salida estándar (consola stdout)
                s++;
            }
            p += 2; // Saltamos el carácter y el '?'
        } 
        else{
            putchar(*s);
            s++;
            p++;
        }
    }
    putchar('\n');
}