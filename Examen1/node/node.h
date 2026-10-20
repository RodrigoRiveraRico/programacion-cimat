#ifndef NODE_H
#define NODE_H

#define OK 1
#define ERR_EMPTY 2

typedef char item;

typedef struct Node{
    item data;
    struct Node *next;
}node;

/// @brief Crea un nuevo nodo
/// @param dato El dato que se guarda en el nodo
/// @return Nodo
node *createNode(item dato);

/// @brief Añade un nuevo nodo al final de la lista
/// @param dato El dato que se guarda en el nodo
/// @param head Apuntador a la cabeza de la lista
/// @return int OK si se agregó nodo; ERR_EMPTY en caso contrario
int addNode(item dato, node *head);

/// @brief Imprime la lista
/// @param head Apuntador a la cabeza de la lista
void printList(node *head);

/// @brief Libera toda la lista
/// @param head Apuntador a la cabeza de la lista
/// @note Es responsabilidad del usuario hacer NULL al apuntador despúes de usar la función.
void freeList(node *head);

#endif