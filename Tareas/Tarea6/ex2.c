#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define OK 0

/// @brief Estructura de queue
typedef struct Queue
{
    int n;                        /**< Numero de nodos */
    struct Posicion *head, *tail; /**< Apuntador a primer nodo y último nodo */
} queue;

/// @brief Estructura de nodo.
typedef struct Posicion
{
    int i_cord; // indice renglon
    int j_cord; // indice columna

    char movimiento;        // U (up), D (down), L (left), R (right)
    struct Posicion *padre; // Nodo padre. Posición anterior en el camino. Permite reconstruir la ruta que se siguió para llegar al nodo actual.
    struct Posicion *next;  // Para queue/lista
} posicion;

/* ------------------------------------------------------------
 * Prototipos
 * ------------------------------------------------------------ */

/// @brief BFS para encontrar el camino más corto en un laberinto binario.
///
/// El laberinto binario se define como:
/// 1 si la casilla es válida
/// 0 si la casilla es prohibida
/// @param N int Número de renglones
/// @param M int Número de columnas
/// @param A int ** Matriz binaria. 1 si la casilla es válida. 0 si la casilla no es prohibida.
/// @param X_ini int indice renglon de inicio
/// @param Y_ini int indice columna de inicio
/// @param X_end int indice renglon de meta
/// @param Y_end int indice columa de meta
/// @return char * Secuencia de movimientos que resuelve el laberinto U, D, L, R
char *solveLaberinto(int N, int M, int **A, int X_ini, int Y_ini, int X_end, int Y_end);

/// @brief Busca la existencia de un nodo en un queue/lista
///
/// Se busca de inicio a fin
/// @param q queue/lista
/// @param X int indice renglon
/// @param Y int indice columna
/// @return TRUE en caso de que el nodo exista; FALSE si el nodo no existe
int buscar(queue *q, int X, int Y);

/// @brief Crear nuevo nodo
/// @param idx_i int indice renglón
/// @param idx_j int indice colummna
/// @param movimiento char U, D, L ,R
/// @param padre nodo padre
/// @return Nodo
posicion *crear_posicion(int idx_i, int idx_j, char movimiento, posicion *padre);

/// @brief En una cadena se recontruye los movimientos desde inicio hasta meta
/// @param meta nodo correspondiente a la meta del laberinto
/// @return char * Secuencia de movimientos U, D ,L ,R
char *reconstruirRuta(posicion *meta);

/// @brief Añade un nuevo nodo al queue/lista
/// @param q queue/lista
/// @param pos nodo
/// @return OK
int addPosicion(queue *q, posicion *pos);

/// @brief Libera memoria de lista ligada
///
/// queue/lista
/// @param head Primer elemento de la lista ligada
void freeList(posicion *head);

/// @brief Imprime lista ligada de inicio a fin
///
/// queue/lista
/// @param head Primer elemento de la lista ligada
void printList(posicion *head);

/// @brief Toma el primer nodo del queue
///
/// La función desconecta el primer nodo y devuelve su dirección de memoria para la manipulación de su información..
/// Es responsabilidad del usuario liberar memoria.
/// @param q queue
/// @return Dirección de memoria del nodo
posicion *removePosicion(queue *q);

/// @brief Crear matriz pidiendo bloque de memoria continua
/// @param N int Renglones
/// @param M int Columnas
/// @return int ** Apuntador 2D
int **crear_matriz(int N, int M);

/// @brief Libera memoria matriz de memoria continua
/// @param matriz int** Matriz
void freeMatriz(int **matriz);

/* ============================================================
 * MAIN
 * ============================================================ */

int main(void)
{

    // Número de Renglones
    int N;
    scanf("%d", &N);
    // Número de Columnas
    int M;
    scanf("%d", &M);
    // Índice de renglón. INICIO
    int X_ini = 0;
    // Índice de columna. INICIO
    int Y_ini = 0;
    // Índice de columna. META
    int X_end = N - 1;
    // Índice de columna. META
    int Y_end = M - 1;
    // Laberinto
    int **A = crear_matriz(N, M);
    if (!A)
    {
        return 1;
    }

    // Leer laberinto
    // char '.' se interpreta como int 1
    // char '#' se interpreta como int 0
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char temp;
            scanf(" %c", &temp);
            if (temp == '.')
            {
                A[i][j] = 1;
            }
            else if (temp == '#')
            {
                A[i][j] = 0;
            }
        }
    }

    // Imprimir matriz en binario
    // for(int i=0;i<N;i++){
    //     for(int j=0;j<M;j++){
    //         printf("%d ",A[i][j]);
    //     }
    //     printf("\n");
    // }

    // Solución laberito
    char *respuesta = solveLaberinto(N, M, A, X_ini, Y_ini, X_end, Y_end);
    if (!respuesta)
    {
        // printf("\nNo existe solución.");
        return 0;
    }
    else
    {
        // printf("\nRuta: ");
        printf("%s", respuesta);
        // printf("\nPasos: %zu",strlen(respuesta));
        free(respuesta);
    }

    freeMatriz(A);
    return 0;
}

char *solveLaberinto(int N, int M, int **A, int X_ini, int Y_ini, int X_end, int Y_end)
{

    //// INI ////

    // Queue de posiciones
    queue posiciones;

    // Lista posiciones visitadas
    queue visitados;

    // Posicion inicial
    /*
     * Tenemos dos nodos independientes:
     *
     *    posiciones       visitados
     *         |               |
     *         v               v
     *       nodo Q          nodo V
     *
     * El nodo de visitados será el que forme parte
     * de la cadena de padres.
     */
    // OJO: Pedimos 2 espacios de memorias para que `visitados` y `posiciones` sean independientes.
    posicion *pos_inicial_visitado = crear_posicion(X_ini, Y_ini, '\0', NULL);
    if (!pos_inicial_visitado)
    {
        return NULL;
    }
    visitados.n = 1;
    visitados.head = pos_inicial_visitado;
    visitados.tail = pos_inicial_visitado;

    /*
     * El nodo de la queue apunta mediante "padre"
     * al nodo correspondiente de visitados.
     */
    posicion *pos_inicial_posicion = crear_posicion(X_ini, Y_ini, '\0', pos_inicial_visitado);
    if (!pos_inicial_posicion)
    {
        freeList(visitados.head);
        return NULL;
    }
    posiciones.n = 1;
    posiciones.head = pos_inicial_posicion;
    posiciones.tail = pos_inicial_posicion;

    //// Casos triviales////

    // Si el inicio coincide con la meta, y es casilla válida
    if (A[X_ini][Y_ini] == 1 && (X_end == X_ini && Y_end == Y_ini))
    {
        freeList(posiciones.head);
        freeList(visitados.head);
        char *ruta = malloc(sizeof(char));
        if (!ruta)
        {
            return NULL;
        }
        ruta[0] = '\0';
        return ruta;
    }
    // Si se inicia en una casilla no válida
    else if (A[X_ini][Y_ini] == 0)
    {
        freeList(posiciones.head);
        freeList(visitados.head);
        return NULL;
    }

    //// Algortimo para encontrar el camino más corto del laberinto. ////
    //// Búsqueda BFS ////

    while (posiciones.n != 0)
    {

        // Posición actual. Se le hizo pop al queue de posiciones.
        /*
         * Sacamos una posición de la queue.
         *
         * IMPORTANTE:
         * removePosicion NO libera el nodo.
         */
        posicion *pos_actual = removePosicion(&posiciones);
        if (!pos_actual)
        {
            freeList(posiciones.head);
            freeList(visitados.head);
            return NULL;
        }

        // Definimos las 4 direcciones desde la posiciones actual
        int up = pos_actual->i_cord - 1;
        int down = pos_actual->i_cord + 1;
        int left = pos_actual->j_cord - 1;
        int right = pos_actual->j_cord + 1;

        /*
         * pos_actual->padre es el nodo correspondiente
         * en la lista de visitados.
         *
         * Ese nodo es el que utilizaremos como padre
         * de los nuevos nodos.
         */
        posicion *padre = pos_actual->padre;

        // Ir hacia arriba
        if (up >= 0 && buscar(&visitados, up, pos_actual->j_cord) == FALSE && A[up][pos_actual->j_cord] == 1)
        {

            /*
             * Creamos el nodo que permanecerá en visitados.
             *
             * Su padre es la posición actual.
             */
            posicion *nuevo_visitado = crear_posicion(up, pos_actual->j_cord, 'U', padre);
            if (!nuevo_visitado)
            {
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return NULL;
            }
            addPosicion(&visitados, nuevo_visitado);

            /*
             * ¿Llegamos a la meta?
             */
            if (up == X_end && pos_actual->j_cord == Y_end)
            {
                char *ruta = reconstruirRuta(nuevo_visitado);
                /*
                 * Ya no necesitamos el nodo actual
                 * de la queue.
                 */
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return ruta;
            }

            /*
             * Creamos la copia para la queue.
             *
             * Su padre apunta al nodo que acabamos
             * de introducir en visitados.
             */
            posicion *nuevo_posicion = crear_posicion(up, pos_actual->j_cord, 'U', nuevo_visitado);
            if (!nuevo_posicion)
            {
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return NULL;
            }
            addPosicion(&posiciones, nuevo_posicion);
        }

        // Ir hacia abajo
        if (down < N && buscar(&visitados, down, pos_actual->j_cord) == FALSE && A[down][pos_actual->j_cord] == 1)
        {

            posicion *nuevo_visitado = crear_posicion(down, pos_actual->j_cord, 'D', padre);
            if (!nuevo_visitado)
            {
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return NULL;
            }
            addPosicion(&visitados, nuevo_visitado);

            if (down == X_end && pos_actual->j_cord == Y_end)
            {
                char *ruta = reconstruirRuta(nuevo_visitado);
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return ruta;
            }

            posicion *nuevo_posicion = crear_posicion(down, pos_actual->j_cord, 'D', nuevo_visitado);
            if (!nuevo_posicion)
            {
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return NULL;
            }
            addPosicion(&posiciones, nuevo_posicion);
        }

        // Ir hacia la izquierda
        if (left >= 0 && buscar(&visitados, pos_actual->i_cord, left) == FALSE && A[pos_actual->i_cord][left] == 1)
        {

            posicion *nuevo_visitado = crear_posicion(pos_actual->i_cord, left, 'L', padre);
            if (!nuevo_visitado)
            {
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return NULL;
            }
            addPosicion(&visitados, nuevo_visitado);

            if (pos_actual->i_cord == X_end && left == Y_end)
            {
                char *ruta = reconstruirRuta(nuevo_visitado);
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return ruta;
            }

            posicion *nuevo_posicion = crear_posicion(pos_actual->i_cord, left, 'L', nuevo_visitado);
            if (!nuevo_posicion)
            {
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return NULL;
            }
            addPosicion(&posiciones, nuevo_posicion);
        }

        // Ir hacia la derecha
        if (right < M && buscar(&visitados, pos_actual->i_cord, right) == FALSE && A[pos_actual->i_cord][right] == 1)
        {

            posicion *nuevo_visitado = crear_posicion(pos_actual->i_cord, right, 'R', padre);
            if (!nuevo_visitado)
            {
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return NULL;
            }
            addPosicion(&visitados, nuevo_visitado);

            if (pos_actual->i_cord == X_end && right == Y_end)
            {
                char *ruta = reconstruirRuta(nuevo_visitado);
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return ruta;
            }

            posicion *nuevo_posicion = crear_posicion(pos_actual->i_cord, right, 'R', nuevo_visitado);
            if (!nuevo_posicion)
            {
                free(pos_actual);
                freeList(visitados.head);
                freeList(posiciones.head);
                return NULL;
            }
            addPosicion(&posiciones, nuevo_posicion);
        }

        // Para visualizar el queue de posiciones o la lista de visitados
        // printList(visitados.head);
        printList(posiciones.head);

        /*
         * Ya terminamos de utilizar la posición de la queue.
         *
         * NO liberamos pos_actual->padre porque pertenece
         * a visitados.
         */
        free(pos_actual);
        pos_actual = NULL;
    }
    /* --------------------------------------------------------
     * BFS terminó sin encontrar la meta
     * -------------------------------------------------------- */
    freeList(visitados.head);
    freeList(posiciones.head);
    return NULL;
}

int buscar(queue *q, int X, int Y)
{

    posicion *cur = q->head;

    // Recorremos la lista de inicio a fin
    while (cur != NULL)
    {
        if (cur->i_cord == X && cur->j_cord == Y)
        {
            return TRUE;
        }
        cur = cur->next;
    }
    return FALSE;
}

posicion *crear_posicion(int idx_i, int idx_j, char movimiento, posicion *padre)
{
    posicion *new = malloc(sizeof *new);
    if (!new)
    {
        return NULL;
    }
    new->i_cord = idx_i;
    new->j_cord = idx_j;
    new->movimiento = movimiento;
    new->padre = padre;
    new->next = NULL;
    return new;
}

char *reconstruirRuta(posicion *meta)
{
    /*
     * Primero contamos cuántos movimientos tiene
     * la ruta.
     */
    int longitud = 0;
    posicion *actual = meta;

    while (actual->padre != NULL)
    {
        longitud++;
        actual = actual->padre;
    }

    /*
     * Reservamos:
     *
     * longitud caracteres
     * +
     * '\0'
     */
    char *ruta = malloc((longitud + 1) * sizeof(char));
    if (!ruta)
    {
        return NULL;
    }

    ruta[longitud] = '\0';

    /*
     * Ahora recorremos desde la meta hacia el inicio.
     *
     * Por eso escribimos desde el final hacia el inicio.
     */
    actual = meta;
    for (int i = longitud - 1; i >= 0; i--)
    {
        ruta[i] = actual->movimiento;
        actual = actual->padre;
    }
    return ruta;
}

int addPosicion(queue *q, posicion *pos)
{
    if (q->head == NULL)
    {
        q->head = pos;
        q->tail = pos;
    }
    else
    {
        q->tail->next = pos;
        q->tail = pos; // No olvidar actualizar tail
    }
    q->n++;
    return OK;
}

void freeList(posicion *head)
{
    while (head != NULL)
    {
        posicion *temp = head->next;
        free(head);
        head = temp;
    }
}

void printList(posicion *head)
{
    if (!head)
    {
        printf("\n<>"); // Indica vacío
        return;
    }

    posicion *curr = head;
    printf("\n");
    while (curr != NULL)
    {
        // (<indice_renglón><indice_columna><movimiento_realizado>)
        printf("(<%d><%d><%c>) ", curr->i_cord, curr->j_cord, curr->movimiento);
        curr = curr->next;
    }
}

posicion *removePosicion(queue *q)
{
    if (!q->head)
    {
        return NULL;
    }
    posicion *pos_actual = q->head;
    q->head = q->head->next;
    q->n--;

    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    /*
     * Desconectamos el nodo de la queue.
     *
     * IMPORTANTE:
     * todavía no lo liberamos.
     * solveLaberinto lo hará después de utilizarlo.
     */
    pos_actual->next = NULL;

    return pos_actual;
}

int **crear_matriz(int N, int M)
{
    int **mi_matriz = malloc(N * sizeof(int *));
    if (!mi_matriz)
    {
        return NULL;
    }

    // Bloque de memoria continua para los elementos de la matriz
    mi_matriz[0] = malloc(N * M * sizeof(int));
    if (!mi_matriz[0])
    {
        free(mi_matriz);
        return NULL;
    }
    for (int i = 1; i < N; i++)
    {
        mi_matriz[i] = mi_matriz[i - 1] + M;
    }
    return mi_matriz;
}

void freeMatriz(int **matriz)
{
    free(matriz[0]);
    free(matriz);
}