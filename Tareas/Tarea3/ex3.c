#include <stdio.h>
#include <stdlib.h>

#define MEMORY_ERROR(P) if(!P){return 1;}
#define LIBERAR(P) free(P);

int main(void){

    unsigned int m,n;
    char *s=NULL,*t=NULL;

    scanf("%u",&n);
    t = malloc((n+1)*sizeof(char));
    MEMORY_ERROR(t)    
    scanf("%s",t);

    scanf("%u",&m);
    s = malloc((m+1)*sizeof(char));
    MEMORY_ERROR(s)
    scanf("%s",s);

    if(n>m){
        printf("\n%d",0);
        LIBERAR(s)
        LIBERAR(t)
        return 0;
    }

    int contador=0;
    int ocurrencias;
    for(int i=0;i<m-n+1;i++){   
        ocurrencias = 0;
        for(int j=0;j<n;j++){
            if(t[j]==s[i+j]) {
                ocurrencias++;
            }
        }
        if(ocurrencias==n){
            contador++;
        } 
    }
    printf("\n%d",contador);

    LIBERAR(s)
    LIBERAR(t)

    return 0;
}

/*
20
TAGGTAGCAGGAGGAGGAGG
20
TAGGTAGCAGGAGGAGGAGG
4
AGGA
20
TAGGTAGCAGGAGGAGGAGG
*/