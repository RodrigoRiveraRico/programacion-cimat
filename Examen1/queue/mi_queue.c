#include <stdio.h>
#include "queue.h"


// Ejemplo de uso de la libreria queue.c
int main(void){

    queue mi_queue;

    queueInit(&mi_queue); 

    item elemento = 'A';
    if(queueEnqueue(&mi_queue, &elemento) == OK){
        printf("\nSe guarda: %c",'A');
    }

    char a[1];
    if(queueFront(&mi_queue,a)==OK){
        printf("\nEl primer elemento es: %c",a[0]);
    }

    return 0;
}