#include <stdio.h>
#include <stdlib.h>

#define OK 0 // En el estándar de C, en main(), el 0 es ejecución exitosa.
#define FALLO 1

#define PUSH_FAIL 2
#define PUSH_OK 3

#define POP_FAIL 4
#define POP_OK 5

typedef struct {
    unsigned int N;      // Cantidad máxima de elementos
    long *dat;           // Arreglo dinámico de capacidad S
    unsigned int ini;    // Inicio del contenedor. Para stack es fijo.
    unsigned int end;    // Índice para colocar el nuevo elemento.
} contenedor;

/// @brief Cálculo de los términos de la sucesión de Fabionacci
///
/// @param c Estructura de stack
/// @param N int Parámetro de la sucesión N >= 1
/// @param K int Cantidad de términos de la sucesión K >= 1
void fabionacci(contenedor *c, int N, int K);
// Determina si el contenedor está lleno
int isFull(contenedor *c);
// Determina si el contenedor está vacío
int isEmpty(contenedor *c);
// Meter dato en top
int push(contenedor *c, long *val);
// Sacar dato de top
int pop(contenedor *c, long *val);

int main(void){

    // N el parámetro de la serie
    // S la capacidad máxima del stack provisto a Fabionacci
    // K la cantidad de términos de la serie que se desean calcular y mostrar x_k
    // Debe ser S > 1
    int N,S,K;
    scanf("%d",&N); // 1 <= N <= 100
    scanf("%d",&S); // 1 <= S <= 100
    scanf("%d",&K); // 1 <= K <= 1000

    contenedor *stack = malloc(sizeof *stack);
    if(!stack){
        return FALLO;
    }
    // INI
    stack->N = S;
    stack->ini = 0;
    stack->end = 0;
    stack->dat = malloc(S*sizeof *stack->dat);
    if(!stack->dat){
        free(stack);
        return FALLO;
    }

    // Fabionacci
    fabionacci(stack,N,K);

    free(stack->dat);
    free(stack);
    return OK;
}

void fabionacci(contenedor *c, int N, int K){
    int output;
    long suma;
    long val;
    static long x = 0;  // Término x_k
                        // Se inicializa una vez como cero.
                        // Guarda el último valor adquirido para la siguiente ejecución de la función

    // Limites de la suma
    long lim_inf, lim_sup;

    for(int k=0;k<K;k++){

        if(x==0){     // x == 0 significa calcular el caso base
            lim_inf=1;
            lim_sup=(long)N;
        }
        else{   // x != 0 significa calcular el término x_k
            lim_inf=x;
            lim_sup=x+(long)N-1;
        }

        // Algoritmo de fabionacci
        // k-esimo término de fabionacci
        for(long i=lim_inf;i<=lim_sup;i++){
            output = push(c,&i);
            if(output==PUSH_OK){
                continue;
            }
            else if(output==PUSH_FAIL){
                // printf(">>unstack...\n");
                suma = 0;   // Cada que se hace unstack inicializamos suma acumulada en cero
                while(!isEmpty(c)){
                    pop(c,&val);    // Actualiza el valor de 'val'
                    suma+=val;
                }
                // Aquí hacemos mínimo 2 push, por lo que S > 1
                push(c,&suma); // Push suma acumulada
                push(c,&i);    // Push elemento que se quedó en espera
                suma=0;
            }
        }
        // printf(">>final unstack...\n");
        suma = 0;   // Cada que se hace unstack inicializamos suma acumulada en cero
        while(!isEmpty(c)){
            pop(c,&val);    // Actualiza el valor de 'val'
            suma+=val;
        }
        x = suma;           // Término x_k de la serie Fabionacci
                            // El contenedor ha quedado vacío
        // printf("x_{%d} = ",k);
        printf("%ld\n",x);  
    }
}

int isFull(contenedor *c){
    return c->end == c->N;
}

int isEmpty(contenedor *c){
    return c->end == c->ini;
}

int push(contenedor *c, long *val){
    if(isFull(c)){
        return PUSH_FAIL;
    }
    // printf("push: %ld\n",*val);
    c->dat[c->end] = *val;
    c->end++;
    return PUSH_OK;
}

int pop(contenedor *c, long *val){
    if(isEmpty(c)){
        return POP_FAIL;
    }
    c->end--;
    *val = c->dat[c->end];
    return POP_OK;
}