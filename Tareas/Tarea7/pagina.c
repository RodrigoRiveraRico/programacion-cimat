#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PageNode
{
    long long page_idx;     // índice de la página
    int *memory_patch;      // memoria de la página
    struct PageNode *left;  // página izquierda
    struct PageNode *right; // página derecha
} PageNode;

typedef struct
{
    int N;
    int allocated_count; // número de páginas reservadas
    PageNode *root;      // página raíz
} PagedMemory;

// Inicializa la estructura de datos
PagedMemory *create_paged_memory(int N);

// Inserta una nueva página si no existe, y modifica el nodo target, que es el
// nodo buscado. En particular, esta función también debe mantener la
// estructura de árbol binario. Es decir, debe regresar el nodo raíz en la
// última llamada del stack
PageNode *insert_or_get_page(PagedMemory *mem, PageNode *node, long long page_idx, PageNode **target);

// Busca el árbol binario para la página requerida
PageNode *find_page(PageNode *node, long long page_idx);

// Asigna el valor indicado en el índice. Si no existe, crea la página nueva en el árbol binario
void set_val(PagedMemory *mem, long long idx, int val);

// Regresa el valor en el índice si existe, 0 si no
int get_val(PagedMemory *mem, long long idx);

// Liberar memoria
void freeArbol(PageNode *root);

int main(void)
{

    // Asignamos suficiente memoria para leer los queries
    char opr[6];
    int N;
    long long idx;
    int val;

    PagedMemory *mi_paged_memory = NULL;

    // Ejemplo de uso
    // INIT N : Inicializa tu estructura de datos con una página de tamaño (este siempre será el primer query).
    // SET idx val : Escribe val a idx. Reserva memoria nueva si la página no existe.
    // GET idx : Imprime el valor en el índice idx. Si la página no existe, imprime 0 (no debes reservar memoria si la página no existe).
    // COUNT : Imprime el número total de páginas con memoria reservada.

    // El bucle lee palabra por palabra
    // Usaremos strcmp para comparar cadenas. Si devuelve 0 son iguales.
    // OJO: Limitamos lectura a máximo 5 caracteres (%5s) para proteger el arreglo de 6 elementos.
    while (scanf("%5s", opr) != EOF)
    {

        if (strcmp(opr, "INIT") == 0)
        {
            scanf("%d", &N);
            mi_paged_memory = create_paged_memory(N);
        }

        else if (strcmp(opr, "SET") == 0)
        {
            scanf("%lld %d", &idx, &val);
            set_val(mi_paged_memory, idx, val);
        }

        else if (strcmp(opr, "GET") == 0)
        {
            scanf("%lld", &idx);
            printf("%d\n", get_val(mi_paged_memory, idx));
        }

        else if (strcmp(opr, "COUNT") == 0)
        {
            printf("%d\n", mi_paged_memory->allocated_count);
        }
    }

    freeArbol(mi_paged_memory->root);
    free(mi_paged_memory);

    return 0;
}

PagedMemory *create_paged_memory(int N)
{
    PagedMemory *paged_memory = malloc(sizeof *paged_memory);
    if (!paged_memory)
    {
        return NULL;
    }

    paged_memory->N = N;
    paged_memory->allocated_count = 0;
    paged_memory->root = NULL;

    return paged_memory;
}

PageNode *insert_or_get_page(PagedMemory *mem, PageNode *node, long long page_idx, PageNode **target)
{
    if (node == NULL)
    {
        // La página no existe, la creamos utilizando calloc para inicializarla en 0
        PageNode *new_node = malloc(sizeof *new_node);
        if (!new_node)
        {
            return NULL;
        }
        new_node->page_idx = page_idx;
        new_node->memory_patch = calloc(mem->N, sizeof(int));
        new_node->left = NULL;
        new_node->right = NULL;

        mem->allocated_count++; // Incrementamos el contador en la estructura principal
        *target = new_node;     // Apuntamos target al nuevo nodo creado
        return new_node;
    }

    if (page_idx == node->page_idx)
    {
        // La página ya existe, la asignamos a target
        *target = node;
    }
    else if (page_idx < node->page_idx)
    {
        node->left = insert_or_get_page(mem, node->left, page_idx, target);
    }
    else
    {
        node->right = insert_or_get_page(mem, node->right, page_idx, target);
    }
    return node; // Regresa el nodo actual para reconstruir los enlaces del árbol
}

PageNode *find_page(PageNode *node, long long page_idx)
{
    if (node == NULL || node->page_idx == page_idx)
    {
        return node;
    }

    if (page_idx < node->page_idx)
    {
        return find_page(node->left, page_idx);
    }
    else
    {
        return find_page(node->right, page_idx);
    }
}

void set_val(PagedMemory *mem, long long idx, int val)
{
    if (mem == NULL)
    {
        return;
    }

    long long page_idx = idx / mem->N;
    int offset = idx % mem->N;
    PageNode *target = NULL;
    // Insertamos o recuperamos la página, actualizando la raíz del árbol
    mem->root = insert_or_get_page(mem, mem->root, page_idx, &target);

    if (target != NULL)
    {
        target->memory_patch[offset] = val;
    }
}

int get_val(PagedMemory *mem, long long idx)
{
    if (mem == NULL || mem->root == NULL)
    {
        return 0;
    }

    long long page_idx = idx / mem->N;
    int offset = idx % mem->N;

    PageNode *target = find_page(mem->root, page_idx);
    if (target != NULL)
    {
        return target->memory_patch[offset];
    }

    return 0;
}

void freeArbol(PageNode *root)
{
    if (root == NULL)
        return;

    freeArbol(root->left);
    freeArbol(root->right);

    free(root);
}