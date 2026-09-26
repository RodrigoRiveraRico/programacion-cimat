#include <stdio.h>
#include <stdlib.h>

// La implementación consiste en tomar una cadena y intercambia con '\0' cada ' ' (espacio) que se vea.
// El intercambio se hace en cada llamada:
// "ab cd e\0" --> "ab\0cd e\0" --> "ab\0cd\0e\0"
// Si llega una cadena nueva, se reemplaza y se obtendrán nuevos tokens
// Si llega NULL, se generan los tokens de la cadena actual en cada llamada.
// Se retorna el índice del inicio del siguiente token.
// Se retorna NULL cuando no hay más tokens.
char *mi_strtok(char *s);

int main(void){

    // Tamaño cadena
    int N;
    scanf("%d",&N);
    
    // Con memoria dinámica asignamos un espacio de N+1
    char *mi_string = malloc((N+1) * sizeof *mi_string);  // Añadir espacio para '\0' del final de la cadena.
    if(!mi_string){
        return 1;
    }

    // Consumimos el espacio en blanco que separa el entero del string en consola
    fgetc(stdin);   // stdin para leer desde consola
    fgets(mi_string, N+1, stdin);

    char *token = mi_strtok(mi_string);
    while(token!=NULL){
        printf("%s\n",token);
        token = mi_strtok(NULL); 
    }

    free(mi_string);
    return 0;
}
char *mi_strtok(char *s){

    // Índice actual sobre la cadena
    // Variable estática para recordar índice entre llamadas
    static char *idx_actual = NULL;

    // Llega una cadena nueva.
    if(s!=NULL){
        idx_actual = s;
    }

    // En cada llamada a la función hay que revisar la posición actual del índice.
    // A) Se está al final de la cadena ya no hay más tokens o B) la cadena es vacía.
    if(*idx_actual=='\0' || idx_actual==NULL){
        return NULL;
    }

    // Saltamos todos los espacio en blanco antes del siguiente caracter distinto a un espacio.
    // Es decir, apuntamos al siguiente caracter distinto a espacio.
    while(*idx_actual==' '){
        idx_actual++;
    }

    // Caso en que después de saltar todos los espacios se haya llegado al final de la cadena.
    if(*idx_actual=='\0'){
        return NULL;
    }

    // Índice inicio de token
    char *idx_token = idx_actual;

    // Buscamos el índice donde termina el token
    while(*idx_actual!=' ' && *idx_actual!='\0'){
        idx_actual++;
    }

    // Caso en que hayamos llega a un espacio
    if(*idx_actual==' '){
        *idx_actual = '\0';
        idx_actual++;   
    }

    // Notemos que si llegamos al final del string no hay que avanzar el apuntador idx_actual
    return idx_token;   // Return del inicio del token.
}