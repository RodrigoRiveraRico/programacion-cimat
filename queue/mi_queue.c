#include <stdio.h>
#include "queue.h"


// Ejemplo de uso de la libreria queue.c
int main(void){

    queue *mi_queue;

    queueInit(mi_queue); 

    if(queueEnqueue(mi_queue, 'A') == OK){
        printf("\nSe guarda: %c",'A');
    }

    char a[1];
    if(queueFront(mi_queue,a)==OK){
        printf("\nEl primer elemento es: %c",a[0]);
    }

    return 0;
}