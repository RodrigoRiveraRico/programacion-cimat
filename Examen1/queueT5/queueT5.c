#include <stdio.h>
#include <stdlib.h>

#define ENQUEUE_OK 1
#define ENQUEUE_FAIL 2

#define DEQUEUE_OK 3
#define DEQUEUE_FAIL 4

typedef struct {
    unsigned int N;      // Capacidad máxima de la fila
    char *dat;           // Arreglo dinámico de capacidad N
    unsigned int ini;    // Índice del frente de la fila
    unsigned int end;    // Índice del final de la fila
} queue;

// Función que calcula si queue está vacío
int isEmpty(queue *q){
    return q->end == q->ini;
}

// Función que calcula si queue está lleno
int isFull(queue *q){
    return q->end - q->ini == q->N;
}

//  Agrega un nuevo visitante (un carácter) al final de la fila
int enqueue(queue *q, char *d){
    if(isFull(q)){
        return ENQUEUE_FAIL;
    }
    q->dat[q->end % q->N] = *d;
    q->end++;
    return ENQUEUE_OK;
}

// Retira al visitante al frente de la fila 
int dequeue(queue *q, char *d){
    if(isEmpty(q)){
        return DEQUEUE_FAIL;
    }
    *d = q->dat[q->ini % q->N]; // Guardamos quién estaba enfrente
    q->ini++;
    return DEQUEUE_OK;
}

// Imprimir resultado de la operación para alguna fila id
void reportar(int op, char d, int id){
    if(op==ENQUEUE_FAIL){
        printf("Push[%d]: ERROR\n",id);
    }
    else if(op==ENQUEUE_OK){
        printf("Push[%d]: %c\n",id,d);
    }

    else if(op==DEQUEUE_FAIL){
        printf("Pop[%d] = ERROR\n",id);
    }
    else if(op==DEQUEUE_OK){
        printf("Pop[%d] = %c\n",id,d);
    }
}

// Imprime el número de personas formadas en la fila
void personasFormadas(queue *q){

    unsigned n = q->end - q->ini;
    printf("n[%d] = %u\n",n);
    
}