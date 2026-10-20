#include <stdio.h>
#include <stdlib.h>

#define PUSH_FAIL 2
#define PUSH_OK 3

#define POP_FAIL 4
#define POP_OK 5

typedef struct {
    unsigned int N;      // Cantidad máxima de elementos
    long *dat;           // Arreglo dinámico de capacidad S
    unsigned int ini;    // Inicio del contenedor. Para stack es fijo.
    unsigned int end;    // Índice para colocar el nuevo elemento.
} contenedor;

// Determina si el contenedor está lleno
int isFull(contenedor *c){
    return c->end == c->N;
}

// Determina si el contenedor está vacío
int isEmpty(contenedor *c){
    return c->end == c->ini;
}

// Meter dato en top
int push(contenedor *c, long *val){
    if(isFull(c)){
        return PUSH_FAIL;
    }
    // printf("push: %ld\n",*val);
    c->dat[c->end] = *val;
    c->end++;
    return PUSH_OK;
}

// Sacar dato de top
int pop(contenedor *c, long *val){
    if(isEmpty(c)){
        return POP_FAIL;
    }
    c->end--;
    *val = c->dat[c->end];
    return POP_OK;
}