#include "node.h"
#include <stdlib.h>
#include <stdio.h>

node *createNode(item dato){
    node *temp = malloc(sizeof *temp);
    if(!temp){
        return NULL;
    }
    temp->data = dato;
    temp->next = NULL;
    return temp;   
}

int addNode(item dato, node *head){
    if(!head){return ERR_EMPTY;}

    node *new = createNode(dato);

    node *curr = head;
    while(curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new;
    return OK;
}

void printList(node *head){
    if(!head){
        printf("\n<>"); // Indica vacío
        return;
    }

    node *curr = head;
    printf("\n");
    while(curr!=NULL){
        printf("<%c> ",curr->data);
        curr = curr->next;
    }

}

void freeList(node *head){
    if(!head){return;}

    node *curr = head;
    while(curr->next!=NULL){
        node *temp = curr->next;
        free(curr);
        curr = temp;
    }
    free(curr);
}
