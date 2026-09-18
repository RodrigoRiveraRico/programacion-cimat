#include "queue.h"

void queueInit(queue *q){
    q->ini = 0;
    q->end = 0;
    return;
}

boolean queueIsEmpty(queue *q){
    return q->end == q->ini;
}

boolean queueIsFull(queue *q){
    return q->end - q->ini == N;
}

unsigned int queueSize(queue *q){
    return q->end - q->ini;
}

int queueEnqueue(queue *q, item t){
    if(queueIsFull(q)){
        return ERR_FULL;
    }
    q->dat[q->end % N] = t;
    q->end++;
    return OK;
}

int queueDequeue(queue *q, item *t){
    if(queueIsEmpty(q)){
        return ERR_EMPTY;
    }
    *t = q->dat[q->ini % N]; // OJO con la asignación *t
    q->ini++;
    return OK;
}

int queueFront(queue *q, item *t){
    if(queueIsEmpty(q)){
        return ERR_EMPTY;
    }
    *t = q->dat[q->ini];
    return OK;
}