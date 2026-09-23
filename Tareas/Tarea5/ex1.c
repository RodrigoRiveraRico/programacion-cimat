#include <stdio.h>
#include <stdlib.h>

#define FALLO -1
#define OK 0

#define PUSH_F_OK 1
#define PUSH_F_FAIL 2

#define POP_F_OK 3
#define POP_F_FAIL 4

#define PUSH_B_OK 5
#define PUSH_B_FAIL 6

#define POP_B_OK 7
#define POP_B_FAIL 8

typedef struct {
    unsigned int N;          // Tamaño del arreglo
    char *dat;               // Elementos
    unsigned int ini, end;   // índices
} contenedor;

// (Cantidad de elementos): Muestra el número actual de clientes en la fila.
void numberElements(contenedor *c);
// Función que calcula si el contenedor está vacío
int isEmpty(contenedor *c);
// Función que calcula si el contenedor está lleno
int isFull(contenedor *c);
// Formarse normalmente (Push Back): Los clientes llegan al final de la fila.
int pushBack(contenedor *c, char *d);
// (Push Front): Recibe un carácter y colará a ese cliente a la cabeza de la fila.
int pushFront(contenedor *c, char *d);
// (Pop Back): El cliente al final de la fila se arrepiente y se retira.
int popBack(contenedor *c, char *d);
// Subir a la montaña rusa (Pop Front): El cliente que sigue sube a los carros y deja la fila.
int popFront(contenedor *c, char *d);
//  Imprimirá el tipo de operación y su resultado
void reportar(int id, char d);

int main(void){
    int N;
    // printf("\n >N=");
    scanf("%d",&N); // Capacidad máxima de la fila. 1 <= N <= 1000
    int comando;    // Comando
    char *d = malloc(sizeof *d);
    if(!d){
        return FALLO;
    }

    contenedor *fila = malloc(sizeof *fila);
    if(!fila){
        free(d);
        return FALLO;
    }
    // Init
    fila->N = N;
    fila->ini = 0;
    fila->end = 0;
    fila->dat = malloc(N*sizeof *fila->dat);
    if(!fila->dat){
        free(d);
        free(fila);
        return FALLO;
    }

    // Ciclo personas formadas
    while (1){
        // printf("\n >comando=");
        scanf("%d",&comando);
        if(comando==-1){
            free(d);
            free(fila->dat);
            free(fila);
            return OK;
        }
        
        if(comando==0){
            numberElements(fila);
        }
        else if(comando==1){
            scanf(" %c",d);
            reportar(pushFront(fila,d),*d); // Primero se ejecutan los parámetros de `reportar` y luego la función `pushFront`
        }
        else if(comando==2){
            int output = popFront(fila,d);  // popFront modifica a d
            reportar(output,*d);
        }
        else if(comando==3){
            scanf(" %c",d);
            reportar(pushBack(fila,d),*d); // Primero se ejecutan los parámetro de `reportar` y luego la función `pushBack`
        }
        else if(comando==4){
            int output = popBack(fila,d);   // popBack modifica a d
            reportar(output,*d);
        }
    }
}

void numberElements(contenedor *c){
    printf("n: %u\n",c->end - c->ini);
}

int isEmpty(contenedor *c){
    return c->end == c->ini;
}

int isFull(contenedor *c){
    return c->end - c->ini == c->N;
}

int pushBack(contenedor *c, char *d){
    if(isFull(c)){
        return PUSH_B_FAIL;
    }
    c->dat[c->end % c->N] = *d;
    c->end++;
    return PUSH_B_OK;
}

int pushFront(contenedor *c, char *d){
    if(isFull(c)){
        return PUSH_F_FAIL;
    }
    // Mover cada elemento un espacio
    unsigned n = c->end - c->ini;    // Tamaño actual de la fila
    for(unsigned i=0;i<n;i++){
        c->dat[(c->end - i) % c->N] = c->dat[(c->end - i - 1) % c->N];
    }
    c->end++;
    c->dat[c->ini % c->N] = *d;
    return PUSH_F_OK;
}

int popBack(contenedor *c, char *d){
    if(isEmpty(c)){
        return POP_B_FAIL;
    }
    c->end--;
    *d = c->dat[c->end % c->N];
    return POP_B_OK;
}

int popFront(contenedor *c, char *d){
    if(isEmpty(c)){
        return POP_F_FAIL;
    }
    *d = c->dat[c->ini % c->N]; // Guardamos quién estaba enfrente
    c->ini++;
    return POP_F_OK;
}

void reportar(int id, char d){
    if(id==PUSH_F_OK){
        printf("Push F: %c\n",d);
    }
    else if(id==PUSH_F_FAIL){
        printf("Push F: ERROR\n");
    }

    else if(id==POP_F_OK){
        printf("Pop F: %c\n",d);
    }
    else if(id==POP_F_FAIL){
        printf("Pop F: ERROR\n");
    }

    else if(id==PUSH_B_OK){
        printf("Push B: %c\n",d);
    }
    else if(id==PUSH_B_FAIL){
        printf("Push B: ERROR\n");
    }

    else if(id==POP_B_OK){
        printf("Pop B: %c\n",d);
    }
    else if(id==POP_B_FAIL){
        printf("Pop B: ERROR\n");
    }
}