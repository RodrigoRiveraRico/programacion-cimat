// Tarea 5

#include <stdio.h>
#include <stdlib.h>

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
void numberElements(contenedor *c){
    printf("n: %u\n",c->end - c->ini);
}

// Función que calcula si el contenedor está vacío
int isEmpty(contenedor *c){
    return c->end == c->ini;
}

// Función que calcula si el contenedor está lleno
int isFull(contenedor *c){
    return c->end - c->ini == c->N;
}

// Formarse normalmente (Push Back): Los clientes llegan al final de la fila.
int pushBack(contenedor *c, char *d){
    if(isFull(c)){
        return PUSH_B_FAIL;
    }
    c->dat[c->end % c->N] = *d;
    c->end++;
    return PUSH_B_OK;
}

// (Push Front): Recibe un carácter y colará a ese cliente a la cabeza de la fila.
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

// (Pop Back): El cliente al final de la fila se arrepiente y se retira.
int popBack(contenedor *c, char *d){
    if(isEmpty(c)){
        return POP_B_FAIL;
    }
    c->end--;
    *d = c->dat[c->end % c->N];
    return POP_B_OK;
}

// Subir a la montaña rusa (Pop Front): El cliente que sigue sube a los carros y deja la fila.
int popFront(contenedor *c, char *d){
    if(isEmpty(c)){
        return POP_F_FAIL;
    }
    *d = c->dat[c->ini % c->N]; // Guardamos quién estaba enfrente
    c->ini++;
    return POP_F_OK;
}

//  Imprimirá el tipo de operación y su resultado
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