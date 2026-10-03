#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define OK 0
#define ERROR_MEMORY -2
#define ERROR_EMPTY -4

typedef struct Queue
{
    int n;
    struct Posicion *head, *tail;
}queue;

typedef struct Posicion // Nodo
{
    int i_cord;
    int j_cord;
    int conteo;
    struct Posicion *next;
}posicion;

typedef struct Actual{
    int i_cord;
    int j_cord;
    int conteo;
}actual;

int solveLaberinto(int N, int M, int **A, int X_ini, int Y_ini, int X_end, int Y_end);
int buscar(queue *q, int X, int Y);
posicion *crear_posicion(int idx_i, int idx_j, int conteo);
int addPosicion(queue * q, posicion *pos);
actual * removePosicion(queue *q);
int **crear_matriz(int N, int M);
void freeMatriz(int **matriz);

void printList(posicion *head);
void freeList(posicion *head);

int main(void){
    
    // Número de Renglones
    int N;
    scanf("%d",&N);
    // Número de Columnas
    int M;
    scanf("%d",&M);
    // Índice de renglón. INICIO
    int X_ini = 0;
    // Índice de columna. INICIO
    int Y_ini = 0;
    // Índice de columna. META
    int X_end = N-1;
    // Índice de columna. META
    int Y_end = M-1;
    // Laberinto
    int **A = crear_matriz(N,M);
    if(!A){return 1;}

    // Rellenamos laberinto
    // char '.' se interpreta como int 1
    // char '#' se interpreta como int 0
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            char temp;
            scanf(" %c",&temp);
            if(temp == '.'){
                A[i][j] = 1;
            }
            else if(temp == '#'){
                A[i][j] = 0;
            }
        }
    }
        
    // Imprimir matriz
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    int respuesta = solveLaberinto(N,M,A,X_ini,Y_ini,X_end,Y_end);

    printf("\n\nRespuesta: %d", respuesta);

    

    freeMatriz(A);
    return 0;
}

int solveLaberinto(int N, int M, int **A, int X_ini, int Y_ini, int X_end, int Y_end){

    //// INI ////

    // Posicion actual
    actual *pos_actual=NULL;

    // Queue de posiciones 
    queue posiciones;

    // Lista posiciones visitadas
    queue visitados;

    // Posicion inicial (X_ini, Y_ini, 0); el cero significa cero pasos acumulados
    // OJO: Pedimos 2 espacios de memorias para que `visitados` y `posiciones` sean independientes.
    posicion *pos_inicial_posicion = crear_posicion(X_ini,Y_ini,0);
    if(!pos_inicial_posicion){return ERROR_MEMORY;}
    posiciones.n = 1;
    posiciones.head = pos_inicial_posicion;
    posiciones.tail = pos_inicial_posicion;

    posicion *pos_inicial_visitado = crear_posicion(X_ini,Y_ini,0);
    if(!pos_inicial_visitado){
        freeList(posiciones.head);
        return ERROR_MEMORY;
    }
    visitados.n = 1;
    visitados.head = pos_inicial_visitado;
    visitados.tail = pos_inicial_visitado;

    //// Casos triviales////

    // Si el inicio coincide con la meta, y es casilla válida
    if(A[X_ini][Y_ini]==1 && (X_end==X_ini && Y_end==Y_ini)){
        freeList(posiciones.head);
        freeList(visitados.head);
        return 0;
    }
    // Si se inicia en una casilla no válida
    else if(A[X_ini][Y_ini]==0){
        freeList(posiciones.head);
        freeList(visitados.head);
        return -1;
    }

    //// Algortimo para encontrar el camino del laberinto. ////
    //// Búsqueda BFS ////

    while(posiciones.n!=0){

        // Posición actual. Se le hizo pop al queue de posiciones
        pos_actual = removePosicion(&posiciones);
        if(!pos_actual){
            freeList(posiciones.head);
            freeList(visitados.head);
            return ERROR_EMPTY;
        }

        // Definimos las 4 direcciones desde la posiciones actual
        int up = pos_actual->i_cord - 1;
        int down = pos_actual->i_cord + 1;
        int left = pos_actual->j_cord - 1;
        int right = pos_actual->j_cord + 1;

        // Pasos acumulados en la posición actual
        int pasos_acumulados = pos_actual->conteo;

        // Ir hacia arriba
        if(up >= 0
            && buscar(&visitados,up,pos_actual->j_cord)==FALSE
            && A[up][pos_actual->j_cord]==1){

            if(up == X_end && pos_actual->j_cord == Y_end){
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return pasos_acumulados+1;
            }
            else{   // OJO se tienen que crear dos espacios de memoria para que `posiciones` y `visitados` sean independientes.
                posicion *nuevo_visitado = crear_posicion(up,pos_actual->j_cord,pasos_acumulados + 1);
                if(!nuevo_visitado){
                    free(pos_actual);
                    freeList(visitados.head);
                    freeList(posiciones.head);
                    return ERROR_MEMORY;
                }
                addPosicion(&visitados, nuevo_visitado);

                posicion *nuevo_posicion = crear_posicion(up,pos_actual->j_cord,pasos_acumulados + 1);
                if(!nuevo_posicion){
                    free(pos_actual);
                    freeList(visitados.head);
                    freeList(posiciones.head);
                    return ERROR_MEMORY;
                }
                addPosicion(&posiciones, nuevo_posicion);
            }
        }
        
        // Ir hacia abajo
        if(down < N
            && buscar(&visitados,down,pos_actual->j_cord)==FALSE
            && A[down][pos_actual->j_cord]==1){

            if(down==X_end && pos_actual->j_cord==Y_end){
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return pasos_acumulados+1;
            }
            else{
                posicion *nuevo_visitado = crear_posicion(down,pos_actual->j_cord,pasos_acumulados+1);
                if(!nuevo_visitado){
                    free(pos_actual);
                    freeList(visitados.head);
                    freeList(posiciones.head);
                    return ERROR_MEMORY;
                }
                addPosicion(&visitados, nuevo_visitado);

                posicion *nuevo_posicion = crear_posicion(down,pos_actual->j_cord,pasos_acumulados+1);
                if(!nuevo_posicion){
                    free(pos_actual);
                    freeList(visitados.head);
                    freeList(posiciones.head);
                    return ERROR_MEMORY;
                }
                addPosicion(&posiciones, nuevo_posicion);
            }
        }

        // Ir hacia la izquierda
        if(left >= 0 
            && buscar(&visitados,pos_actual->i_cord,left)==FALSE
            && A[pos_actual->i_cord][left]==1){

            if(pos_actual->i_cord==X_end && left==Y_end){
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return pasos_acumulados+1;
            }
            else{
                posicion *nuevo_visitado = crear_posicion(pos_actual->i_cord,left,pasos_acumulados+1);
                if(!nuevo_visitado){
                    free(pos_actual);
                    freeList(visitados.head);
                    freeList(posiciones.head);
                    return ERROR_MEMORY;
                }
                addPosicion(&visitados, nuevo_visitado);

                posicion *nuevo_posicion = crear_posicion(pos_actual->i_cord,left,pasos_acumulados+1);
                if(!nuevo_posicion){
                    free(pos_actual);
                    freeList(visitados.head);
                    freeList(posiciones.head);
                    return ERROR_MEMORY;
                }
                addPosicion(&posiciones, nuevo_posicion);
            }
        }
        
        // Ir hacia la derecha
        if(right < M 
            && buscar(&visitados, pos_actual->i_cord,right)==FALSE
            && A[pos_actual->i_cord][right]==1){
            if(pos_actual->i_cord==X_end && right==Y_end){
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return pasos_acumulados+1;
            }
            else{
                posicion *nuevo_visitado = crear_posicion(pos_actual->i_cord,right,pasos_acumulados+1);
                if(!nuevo_visitado){
                    free(pos_actual);
                    freeList(visitados.head);
                    freeList(posiciones.head);
                    return ERROR_MEMORY;
                }
                addPosicion(&visitados, nuevo_visitado);

                posicion *nuevo_posicion = crear_posicion(pos_actual->i_cord,right,pasos_acumulados+1);
                if(!nuevo_posicion){
                    free(pos_actual);
                    freeList(visitados.head);
                    freeList(posiciones.head);
                    return ERROR_MEMORY;
                }
                addPosicion(&posiciones, nuevo_posicion);
            }
        }

        // Para visualizar el queue de posiciones o la lista de visitados
        // printList(visitados.head);
        // printList(posiciones.head);

        free(pos_actual);
        pos_actual=NULL;
    }

    freeList(visitados.head);
    freeList(posiciones.head);
    return -1;    
}

int buscar(queue *q, int X, int Y){

    posicion *cur = q->head;

    // Recorremos la lista de inicio a fin
    while(cur!=NULL){
        if(cur->i_cord==X && cur->j_cord==Y){
            return TRUE;
        }
        cur = cur->next;
    }
    return FALSE;
}

posicion *crear_posicion(int idx_i, int idx_j, int conteo){
    posicion *new = malloc(sizeof *new);
    if(!new){return NULL;}
    new->i_cord = idx_i;
    new->j_cord = idx_j;
    new->conteo = conteo;
    new->next = NULL;
    return new;
}

int addPosicion(queue * q, posicion *pos){
    if(q->head==NULL){
        q->head = pos;
        q->tail = pos;
    }
    else{
        q->tail->next = pos;
        q->tail = pos;  // No olvidar actualizar tail
    }
    q->n++;
    return OK;
}

void freeList(posicion *head){
    while(head != NULL){
        posicion *temp = head->next;
        free(head);
        head = temp;
    }
}

void printList(posicion *head){
    if(!head){
        printf("\n<>"); // Indica vacío
        return;
    }

    posicion *curr = head;
    printf("\n");
    while(curr!=NULL){
        // (<indice_renglón><indice_columna><pasos_acumulados>)
        printf("(<%d><%d><%d>) ",curr->i_cord,curr->j_cord,curr->conteo);
        curr = curr->next;
    }
}


actual * removePosicion(queue *q){
    if(!q->head){
        return NULL;
    }
    actual *pos_actual = malloc(sizeof *pos_actual);
    if(!pos_actual){return NULL;}

    pos_actual->conteo = q->head->conteo;
    pos_actual->i_cord = q->head->i_cord;
    pos_actual->j_cord = q->head->j_cord;

    posicion *temp = q->head;

    q->head = q->head->next;
    q->n--;

    // No olvidar actualizar tail
    if(q->head==NULL){
        q->tail=NULL;
    }

    free(temp);
    return pos_actual;
}

int **crear_matriz(int N, int M){
    int **mi_matriz = malloc(N*sizeof(int*));
    if(!mi_matriz){return NULL;}

    // Bloque de memoria continua para los elementos de la matriz
    mi_matriz[0] = malloc(N*M*sizeof(int));
    if(!mi_matriz[0]){
        free(mi_matriz);
        return NULL;
    }
    for(int i=1;i<N;i++){
        mi_matriz[i] = mi_matriz[i-1] + M;
    }
    return mi_matriz;
}

void freeMatriz(int **matriz){
    free(matriz[0]);
    free(matriz);    
}