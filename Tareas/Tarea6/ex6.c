#include <stdio.h>
#include <stdlib.h>

/*
             root
            /    \
           1      0
          / \    / \
         1   0  1   0
        / \ / \ / \ / \
       ...
*/

typedef int item;

typedef struct Nodo
{
    item boolean;
    struct Nodo *izq;
    struct Nodo *der;

}nodo;

typedef struct Arbol
{
    struct Nodo *izq;
    struct Nodo *der;

}arbol;

void arbolBinarioRecursivo(nodo *root, item valor, int dim);

int main(void){

    arbol *root = malloc(sizeof *root);
    if(!root){return 1;}

    root->izq = malloc(sizeof *root->izq);
    if(!root->izq){
        free(root);
        return 1;
    }

    root->der = malloc(sizeof *root->der);
    if(!root->der){
        free(root->izq);
        free(root);
        return 1;
    }

    arbolBinarioRecursivo(root->izq, 1, 3);
    arbolBinarioRecursivo(root->der, 0, 3);

    // if(root->der->izq->izq->der == NULL){printf("Es null :D");}
    
    // Free de root...
    return 0;
}

void arbolBinarioRecursivo(nodo *root, item valor, int dim){
    static int cont = 0;
    // printf("Llamada recursiva %d\n",++cont);

    // CASO BASE: Llegamos a los nodos que son las hojas del árbol
    if(dim==1){
        root->boolean = valor;
        root->izq = NULL;
        root->der = NULL;
        return;
    }

    // CASO RECURSIVO: Creamos los hijos izquierda y derecha del nodo actual
    root->boolean = valor;

    root->izq = malloc(sizeof *root->izq);
    root->der = malloc(sizeof *root->der);


    arbolBinarioRecursivo(root->izq,1,dim-1);
    arbolBinarioRecursivo(root->der,0,dim-1);
    
    return;
}