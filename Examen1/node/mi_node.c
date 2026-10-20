#include <stdio.h>
#include "node.h"

int main(void){

    node *head = NULL;

    head = createNode('A');

    for(int i=1;i<5;i++){
        addNode('A'+i, head);
    }
    
    printList(head);

    freeList(head);
    head=NULL;

    return 0;
}