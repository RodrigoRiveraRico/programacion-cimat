#ifndef QUEUE_H
#define QUEUE_H

#define TRUE  1
#define FALSE 0

#define N 5

typedef char item;
typedef int boolean;

#define ERR_EMPTY 1
#define ERR_FULL  2
#define OK        4

/// @brief Estructura de queue FIFO
typedef struct{
    item dat[N]; ///< Elementos de queue 
    unsigned int ini,end;   ///< ini el índice del primer elemento; end el índice donde se almacenará el siguiente elemento
} queue;

/// @brief Inicializa queue
/// @param q Estructura queue
void queueInit(queue *q);

/// @brief Revisa si queue es vacío
/// @param q Estructura queue
/// @return boolean Retorna 1 si está vacío; 0 en caso contrario
boolean queueIsEmpty(queue *q);

/// @brief Revisa si queue está lleno
/// @param q Estructura queue
/// @return boolean Retorna 1 si está lleno; 0 en caso contrario
boolean queueIsFull(queue *q);

/// @brief Devuelve el tamaño del queue
/// @param q Estrucutra queue
/// @return int Retorna el tamaño del queue. El número de elementos actuales
unsigned int queueSize(queue *q);

/// @brief Ingresa un nuevo dato al queue
///
/// Ciclamos el queue con operaciones módulo %N.
/// @param q Estructura queue
/// @param t char Dato que se quiere guardar
/// @return int Retorna ERR_FULL si está lleno; OK si se realizó el enqueue
int queueEnqueue(queue *q, item t);

/// @brief Saca el primer elemento del queue
///
/// Ciclamos el queue con operaciones módulo %N.
/// @param q Estructura queue
/// @param t Apuntador simple. Aquí guardamos el elemento retirado
/// @return int Retorna ERR_EMPTY si está vacío; OK si se realizó el dequeue
int queueDequeue(queue *q, item *t);

/// @brief Vistazo al primer elemento del queue
/// @param q Estructura queue
/// @param t Apuntador simple. Aquí guardamos el primer elemento
/// @return int Retorna ERR_EMPTY si está vacío; OK si existe el elemento
int queueFront(queue *q, item *t);

#endif