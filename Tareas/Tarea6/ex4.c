#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define FALLO 1
// #define ERR_EMPTY 2

typedef int item;

/// @brief Estructura de nodo. Lista doblemente ligada
typedef struct Node{
    item data;
    struct Node *next;  // Apuntador a siguiente nodo
    struct Node *prev;  // Apuntador a anterior nodo
}node;

////////////////////////////////////////////////////////////
/////////////////    PROTOTIPOS  ///////////////////////////
////////////////////////////////////////////////////////////

/// @brief Hace la unión de dos listas.
///
/// Ambas listas deben ser doblemente ligadas.
/// Ambas listas deben estar ordenadas no-decrecientemente.
/// La función une ambas listas en orden no-decreciente.
/// @param head_1 node* Apuntador a estructura de nodo. Lista doblemente ligada.
/// @param head_2 node* Apuntador a estructura de nodo. Lista doblemente ligada.
/// @return node* Apuntador al inicio de la unión de ambas listas.
node * unionListsInOrder(node *head_1, node *head_2);

/// @brief Crea un nuevo nodo
/// @param dato El dato que se guarda en el nodo
/// @return Nodo
node *createNode(item dato);

/// @brief Añade un nuevo nodo al final de la lista
///
/// Se recorre la lista desde el inicio hasta el final y es ahí donde pone el nuevo nodo.
/// Función para listas doblemente ligadas sin apuntador al último elemento (sin tail).
/// @param dato El dato que se guarda en el nodo
/// @param head Apuntador a la cabeza de la lista
/// @return int OK si se agregó nodo; FALLO en caso contrario
int addNode(item dato, node *head);

/// @brief Libera toda la lista
/// @param head Apuntador a la cabeza de la lista
/// @note Es responsabilidad del usuario hacer NULL al apuntador despúes de usar la función.
void freeList(node *head);

/// @brief Imprime la lista de inicio a fin.
/// @param head Apuntador a la cabeza de la lista
void printListFromFront(node *head);

/// @brief Imprime la lista de fin a inicio.
///
/// La función está construida para listas doblemente ligadas, pero que solo tienen apuntador al primer elemento de la lista.
/// La función recorre toda la lista desde el inicio hasta llegar al final y desde ahí imprime recorriendo hacia atrás.
/// @param head Apuntador a la cabeza de la lista
void printListFromBack(node *head);

////////////////////////////////////////////////////////////
/////////////////    PROTOTIPOS NO USADOS  /////////////////
////////////////////////////////////////////////////////////
/*
int addNextNode(node *cur, node *new);
node * updateHead(node *head);
*/



////////////////////////////////////////////////////////////
/////////////////    MAIN  /////////////////////////////////
////////////////////////////////////////////////////////////

int main(void){

    //** Longitud primera lista **//
    int N;
    scanf("%d",&N);

    //** Longitud segunda lista **//
    int M;
    scanf("%d",&M);

    //** ini de la primera lista **//
    node *lista_1 = malloc(sizeof *lista_1);
    if(!lista_1){
        return 1;
    }
    /* data de lista_1 tiene basura.
     * Al final de la inicializacion liberamos el nodo basura y actualizamos el head de la lista.
     */
    lista_1->next=NULL;
    lista_1->prev=NULL;

    //** Leer datos para la primera lista **//
    for(int i=0;i<N;i++){
        item dato;
        scanf("%d", &dato);
        if(addNode(dato, lista_1)==OK){
            continue;
        }
        else {
            freeList(lista_1);
            return 1;
        }
    }
    /* Borramos nodo basura y actualizamos head */
    node *basura = lista_1;
    lista_1 = lista_1->next;
    lista_1->prev = NULL;   // Recordar que es lista doblemente ligadas
    free(basura);
    basura = NULL;

    //** ini de la segunda lista **//
    node *lista_2 = malloc(sizeof *lista_2);
    if(!lista_2){
        freeList(lista_1);
        return 1;
    }
    /* data de lista_2 tiene basura.
     * Al final de la inicializacion liberamos el nodo basura y actualizamos el head de la lista.
     */
    lista_2->next=NULL;
    lista_2->prev=NULL;

    //** Leer datos para la segunda lista **//
    for(int i=0;i<M;i++){
        item dato;
        scanf("%d", &dato);
        if(addNode(dato, lista_2)==OK){
            continue;
        }
        else {
            freeList(lista_1);
            freeList(lista_2);
            return 1;
        }
    }
    /* Borramos nodo basura y actualizamos head */
    basura = lista_2;
    lista_2 = lista_2->next;
    lista_2->prev = NULL;   // Recordar que es lista doblemente ligada.
    free(basura);
    basura = NULL;

    //** Visualización **//
    // printf("Primera lista:");
    // printListFromFront(lista_1);
    // printf("\n");
    // printf("Segunda lista:");
    // printListFromFront(lista_2);
    // printf("\n");

    // printf("Operaciones...\n");
    node *lista_ordenada = unionListsInOrder(lista_1,lista_2);
    // OJO la función no elimina los apuntadores
    // OJO la función devuelve un apuntador al inicio de la lista ordenada de la unión de las dos listas originales
    lista_1 = NULL; // La lista a la que ahora apunta este apuntador no necesariamente es la original.
    lista_2 = NULL; // LA lista a la que ahora apunta este apuntador no necesariamente es la original.

    //** Visualización unión de ambas listas ordenada **/
    // printf("Union: ");
    printListFromFront(lista_ordenada);
    printListFromBack(lista_ordenada);

    freeList(lista_ordenada);
    return 0;
}

////////////////////////////////////////////////////////////
/////////////////    FUNCIONES  ////////////////////////////
////////////////////////////////////////////////////////////

node *unionListsInOrder(node *head_1, node *head_2){

    node *prev_1 = head_1;
    node *cur_1 = head_1->next;
    
    while(head_2!=NULL){

        // Tomar el primer elementos de la segunda lista
        node * cur_2 = head_2;
        // Avanzar el head
        head_2 = head_2->next;
        // Desconectar primer elemento
        cur_2->next=NULL;
        cur_2->prev=NULL;
        // printf("Dato obtenido de segunda lista: <%d>\n",cur_2->data);


        // ¿Nodo_2 va antes de head_1?
        if(cur_2->data < head_1->data){
            head_1->prev = cur_2;
            cur_2->next = head_1;
            head_1 = cur_2;

            prev_1 = cur_2;
            cur_1 = cur_2->next;
            // printf("Dato pegado al inicio de la lista <%d>\n",cur_2->data);
            continue;
        }

        // ¿Nodo_2 va entre Nodo_1_{i-1} y Nodo_1_{i}?
        while(cur_1!=NULL && 
            (cur_2->data < prev_1->data || cur_1->data < cur_2->data))
            {
            prev_1 = cur_1;
            cur_1 = cur_1->next;
        }
        // Si estamos dentro de la lista
        if(cur_1!=NULL){
            prev_1->next = cur_2;
            cur_2->prev = prev_1;
            cur_2->next = cur_1;
            cur_1->prev = cur_2;

            prev_1 = cur_2;
            // printf("Dato pegado en medio de la lista: <%d>\n", cur_2->data);
        }
        // Si llegamos al final de la lista
        else{
            prev_1->next = cur_2;
            cur_2->prev = prev_1;

            prev_1 = cur_2;
            cur_1 = cur_2->next;    // Será NULL. Las siguientes ejecuciones pegará los elementos restantes de la segunda lista.
            // printf("Dato pegado al final de la lista: <%d>\n", cur_2->data);
        }
    }
    return head_1;
}

node *createNode(item dato){
    node *temp = malloc(sizeof *temp);
    if(!temp){
        return NULL;
    }
    temp->data = dato;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;   
}

int addNode(item dato, node *head){

    node *new = createNode(dato);
    if(!new){return FALLO;}

    node *curr = head;
    while(curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new;
    new->prev = curr;
    return OK;
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

void printListFromFront(node *head){
    if(!head){
        printf("\n"); // Indica vacío
        return;
    }

    node *curr = head;
    // printf("\n");
    while(curr!=NULL){
        printf("%d ",curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void printListFromBack(node *head){
    if(!head){
        printf("\n");   // Indica vacío
        return;
    }

    node *curr=head;
    // Avanzamos al final de la lista.
    while(curr->next!=NULL){
        curr = curr->next;
    }

    // Imprimimos de fin a inicio
    while(curr!=NULL){
        printf("%d ",curr->data);
        curr = curr->prev;
    }
    printf("\n");
}


////////////////////////////////////////////////////////////
///////////    FUNCIONES NO USADAS NI PROBADAS  ////////////
////////////////////////////////////////////////////////////

/*
int addNextNode(node *cur, node *new){
    if(!cur || !new){return ERR_EMPTY;}

    // Añadir al final de la lista
    if(cur->next==NULL){
        cur->next = new;
        new->next = NULL;
        return OK;
    }

    node *temp = cur->next;
    cur->next = new;
    new->next = temp;
    return OK;
}

// No olvidar actualizar head
int addPrevNode(node *cur, node *new){
    if(!cur || !new){return ERR_EMPTY;}

    // Añadir al inicio de la lista
    if(cur->prev==NULL){
        new->next = cur;
        new->prev = NULL;
    return OK;
    }

    node *temp = cur->prev;
    cur->prev = new;
    new->prev = temp;
    return OK;
}

// Actualiza head
node * updateHead(node *head){
    if(!head){return NULL;}

    while(head->prev!=NULL){
        head = head->prev;
    }
    return head;
}
*/