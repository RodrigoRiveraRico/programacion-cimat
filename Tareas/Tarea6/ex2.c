#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define TRUE 1
#define FALSE 0
#define ERR_MEM -2
#define ERR_EMPTY -4

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

int shortestDistance(int N, int M, int **A, int X, int Y);
int buscar_visitados(queue *lista, int X, int Y);
posicion *crear_posicion(int idx_i, int idx_j, int conteo);
int addPosicion(queue * q, posicion *pos);
actual * removePosicion(queue *q);
int **crear_matriz(int N, int M);
void freeMatriz(int **matriz);

int main(void){
    
    int N=3;
    int M=3;
    int X=0;
    int Y=0;
    int **A = crear_matriz(N,M);
    if(!A){return 1;}

    A[0][0]=1;
    A[0][1]=0;
    A[0][2]=1;
    A[1][0]=1;
    A[1][1]=1;
    A[1][2]=1;
    A[2][0]=1;
    A[2][1]=0;
    A[2][2]=1;

    /*
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
        */

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    int respuesta = shortestDistance(N,M,A,2,0);
    printf("\n\nRespuesta: %d", respuesta);

    

    freeMatriz(A);
    return 0;
}

int shortestDistance(int N, int M, int **A, int X, int Y){

    //INI

    // Posicion actual
    actual *pos_actual;

    // Queue de posiciones 
    queue posiciones;

    // Lista posiciones visitadas
    queue visitados;

    // Posicion inicial (0,0)
    posicion *pos_inicial = crear_posicion(0,0,0);
    if(!pos_inicial){return ERR_MEM;}

    posiciones.n = 1;
    posiciones.head = pos_inicial;
    posiciones.tail = pos_inicial;

    visitados.n = 1;
    visitados.head = pos_inicial;
    visitados.tail = pos_inicial;

    // Casos triviales

    if(A[0][0]==1 && (X==0 && Y==0)){
        return 0;
    }
    else if(A[0][0]==0){
        return -1;
    }

    // Algortimo para encontrar el camino más corto.

    while(posiciones.n!=0){
        static int chequeo =1;
        printf(">%d<",chequeo);


        pos_actual = removePosicion(&posiciones);

        int up = pos_actual->i_cord - 1;
        int down = pos_actual->i_cord + 1;
        int left = pos_actual->j_cord + 1;
        int right = pos_actual->j_cord - 1;


        if(up >= 0
            && buscar_visitados(&visitados,up,pos_actual->j_cord)==FALSE
            && A[up][pos_actual->j_cord]==1){

                if(up == X && pos_actual->j_cord == Y){
                    return pos_actual->conteo + 1;
                }
                else{
                    posicion *new_pos = crear_posicion(up,pos_actual->j_cord,pos_actual->conteo + 1);
                    if(!new_pos){ERR_MEM;}
                    addPosicion(&visitados, new_pos);
                    addPosicion(&posiciones, new_pos);
                }
            }
        
        if(down < N
            && buscar_visitados(&visitados,down,pos_actual->j_cord)==FALSE
            && A[down][pos_actual->j_cord]==1){
                printf("bajo ");

                if(down==X && pos_actual->j_cord==Y){
                    printf("lleguee ");
                    return pos_actual->conteo + 1;
                }
                else{
                    posicion *new_pos = crear_posicion(down,pos_actual->j_cord,pos_actual->conteo+1);
                    if(!new_pos){ERR_MEM;}
                    addPosicion(&visitados, new_pos);
                    addPosicion(&posiciones, new_pos);
                }
            }


        if(left >= 0 
            && buscar_visitados(&visitados,pos_actual->i_cord,left)==FALSE
            && A[pos_actual->i_cord][left]==1){

                if(pos_actual->i_cord==X && left==Y){
                    return pos_actual->conteo+1;
                }
                else{
                    posicion *new_pos = crear_posicion(pos_actual->i_cord,left,pos_actual->conteo+1);
                    if(!new_pos){ERR_MEM;}
                    addPosicion(&visitados, new_pos);
                    addPosicion(&posiciones, new_pos);
                }
            }
        
        if(right < M 
            && buscar_visitados(&visitados, pos_actual->i_cord,right)==FALSE
            && A[pos_actual->i_cord][right]==1){
                if(pos_actual->i_cord==X && right==Y){
                    return pos_actual->conteo+1;
                }
                else{
                    posicion *new_pos = crear_posicion(pos_actual->i_cord,right,pos_actual->conteo+1);
                    if(!new_pos){ERR_MEM;}
                    addPosicion(&visitados, new_pos);
                    addPosicion(&posiciones, new_pos);
                }
            }

        chequeo++;
    }
    return -1;    
}


int buscar_visitados(queue *lista, int X, int Y){

    posicion *cur = lista->head;

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
    q->tail->next = pos;
    q->n++;
    
    return OK;
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

    free(temp);
    return pos_actual;
}

int **crear_matriz(int N, int M){
    int **mi_matriz = malloc(N*sizeof(int*));
    if(!mi_matriz){return NULL;}

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