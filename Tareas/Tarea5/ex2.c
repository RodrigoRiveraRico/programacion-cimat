#include <stdio.h>
#include <stdlib.h>

#define FALLO -1
#define OK 0

#define ENQUEUE_OK 1
#define ENQUEUE_FAIL 2

#define DEQUEUE_OK 3
#define DEQUEUE_FAIL 4

typedef struct {
    unsigned int N;      // Capacidad máxima de la fila
    char *dat;           // Arreglo dinámico de capacidad N
    unsigned int ini;    // Índice del frente de la fila
    unsigned int end;    // Índice del final de la fila
} queue;

// Función que calcula si queue está vacío
int isEmpty(queue *q);
// Función que calcula si queue está lleno
int isFull(queue *q);
//  Agrega un nuevo visitante (un carácter) al final de la fila
int enqueue(queue *q, char *d);
// Retira al visitante al frente de la fila 
int dequeue(queue *q, char *d);
// Imprimir resultado de la operación para alguna fila
void reportar(int op, char d, int id);
// Imprime el número de personas formadas en cada fila
void personasFormadas(queue *q, int K);

int main(void){

    char *d = malloc(sizeof *d);
    if(!d){
        return FALLO;
    }

    int K; // 1 <= K <= 100
    scanf("%d",&K);
    int N; // 1 <= N <= 1000
    scanf("%d",&N);

    queue *filas = malloc(K*sizeof *filas);
    if(!filas){
        free(d);
        return FALLO;
    }

    // Init
    int i;
    for(i=0;i<K;i++){
        filas[i].N = N;
        filas[i].ini = 0;
        filas[i].end = 0;
        filas[i].dat = malloc(N*sizeof *filas[i].dat);
        if(!filas[i].dat){
            for(int j=0;j<i;j++){
                free(filas[j].dat);
            }
            free(filas);
            free(d);
            return FALLO;
        }
    }

    // Ciclo personas formadas
    int operacion;
    int fila;
    while(1){
        scanf("%d",&operacion);
        if(operacion==-1){
            for(int j=0;j<K;j++){
                free(filas[j].dat);}
            free(filas);
            free(d);
            return OK;
        }

        if(operacion==0){
            personasFormadas(filas,K);
        }
        else if(operacion==1){  // enqueue
            // caracter
            scanf(" %c",d);
            // fila
            scanf("%d",&fila);
            int output = enqueue(&filas[fila],d);
            reportar(output,*d,fila);

        }
        else if(operacion==2){  //dequeue de todas las filas
            for(int i=0;i<K;i++){
                int output = dequeue(&filas[i],d);
                reportar(output,*d,i);
            }
        }
    }
}

int isEmpty(queue *q){
    return q->end == q->ini;
}

int isFull(queue *q){
    return q->end - q->ini == q->N;
}

int enqueue(queue *q, char *d){
    if(isFull(q)){
        return ENQUEUE_FAIL;
    }
    q->dat[q->end % q->N] = *d;
    q->end++;
    return ENQUEUE_OK;
}

int dequeue(queue *q, char *d){
    if(isEmpty(q)){
        return DEQUEUE_FAIL;
    }
    *d = q->dat[q->ini % q->N]; // Guardamos quién estaba enfrente
    q->ini++;
    return DEQUEUE_OK;
}

void reportar(int op, char d, int id){
    if(op==ENQUEUE_FAIL){
        printf("Push[%d]: ERROR\n",id);
    }
    else if(op==ENQUEUE_OK){
        printf("Push[%d]: %c\n",id,d);
    }

    else if(op==DEQUEUE_FAIL){
        printf("Pop[%d] = ERROR\n",id);
    }
    else if(op==DEQUEUE_OK){
        printf("Pop[%d] = %c\n",id,d);
    }
}

void personasFormadas(queue *q, int K){
    for(int i=0;i<K;i++){
        unsigned n = q[i].end - q[i].ini;
        printf("n[%d] = %u\n",i,n);
    }
}
