#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

    int len_s1,len_s2;
    int comparacion;
    char *s1=NULL,*s2=NULL;
    char *menor=NULL;

    scanf("%d",&len_s1);
    scanf("%d",&len_s2);
    
    s1 = malloc((len_s1+1)*sizeof(char));
    if(!s1){
        // Falló asignación de memoria.
        return 1;
    }
    s2 = malloc((len_s2+1)*sizeof(char));
    if(!s2){
        // Falló asignación de memoria.
        return 1;
    }

    // Guardamos cadenas.
    scanf("%s",s1);
    scanf("%s",s2);
    
    comparacion = strcmp(s1,s2);

    if(comparacion == 0){
        // Las cadenas son iguales
        menor = malloc((len_s1+1)*sizeof(char));
        if(!menor){
            // Falló asignación de memoria
            return 1;
        }
        strcpy(menor, s1);
    }
    else if(comparacion > 0){
        // La primera cadena es mayor
        menor = malloc((len_s2+1)*sizeof(char));
        if(!menor){
            // Falló asignación de memoria
            return 1;
        }
        strcpy(menor, s2);
    }
    else{
        // La primera cadena es menor
        menor = malloc((len_s1+1)*sizeof(char));
        if(!menor){
            // Falló asignación de memoria
            return 1;
        }
        strcpy(menor, s1);
    }

    printf("\n%s",menor);
    printf("\n%d",strlen(menor));

    free(s1);
    s1 = NULL;
    free(s2);
    s2 = NULL;
    return 0;
}