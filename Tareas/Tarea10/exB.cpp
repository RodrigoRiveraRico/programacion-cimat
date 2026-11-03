#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>

struct nodeFace
{
    unsigned n_v = 3;
    unsigned a, b, c;
    struct nodeFace *next;

    // Constructor
    nodeFace(unsigned a_i, unsigned b_i, unsigned c_i) : a(a_i), b(b_i), c(c_i), next(nullptr) {}
};

struct faceList
{
    struct nodeFace *head;
    // Se pueden incluir más miembros para describir mejor la lista

    // Constructor
    faceList() : head(nullptr) {}

    // Destructor
    ~faceList() { borrar(); }

    void borrar(){

        nodeFace* curr = head;

        while(curr != nullptr){

            nodeFace* temp = curr;
            curr = curr->next;

            delete temp;
        }

        head = nullptr;
    }

    void print_list()
    {
        nodeFace *curr = head;
        while (curr != nullptr)
        {
            std::cout << curr->n_v << " " << curr->a << " " << curr->b << " " << curr->c << "\n";
            curr = curr->next;
        }
    }

    void find_node(unsigned index)
    {

        nodeFace **actual = &head;

        while (*actual != nullptr)
        {

            if ((*actual)->a == index ||
                (*actual)->b == index ||
                (*actual)->c == index)
            {

                nodeFace *temp = *actual;
                *actual = temp->next;

                delete temp;
            }
            else
            {
                actual = &((*actual)->next);
            }
        }
    }
};

struct vertex
{
    float x, y, z;
    unsigned idx;
};

struct Centroide
{
    float x, y, z;
};
static Centroide cm_global;

// Función para calcular el centroide de los vértices
Centroide centroide(const vertex *vertices, unsigned n)
{

    Centroide cm{0.0f, 0.0f, 0.0f};

    for (unsigned j = 0; j < n; j++)
    {
        cm.x += vertices[j].x;
        cm.y += vertices[j].y;
        cm.z += vertices[j].z;
    }

    cm.x /= n;
    cm.y /= n;
    cm.z /= n;

    return cm;
}

// Función distancia euclidiana
float distancia(const vertex *v, const Centroide *cm)
{

    return sqrtf(
        (cm->x - v->x) * (cm->x - v->x) +
        (cm->y - v->y) * (cm->y - v->y) +
        (cm->z - v->z) * (cm->z - v->z));
}

// Función para comparar con qsort (distancia euclidiana al cuadrado)
float distancia2(const vertex *v, const Centroide *cm)
{

    return (cm->x - v->x) * (cm->x - v->x) +
           (cm->y - v->y) * (cm->y - v->y) +
           (cm->z - v->z) * (cm->z - v->z);
}

int comparar_distancias(const void *a, const void *b)
{

    const vertex *verticeA = (const vertex *)a;
    const vertex *verticeB = (const vertex *)b;

    float distanciaA = distancia2(verticeA, &cm_global);
    float distanciaB = distancia2(verticeB, &cm_global);

    if (distanciaA < distanciaB)
        return 1;
    if (distanciaA > distanciaB)
        return -1;

    return 0;
}

int main()
{

    // Número de vértices y caras
    unsigned vertices, faces;

    // Para guardar los caracteres leídos línea por línea
    char line[256];

    // Se lee la cabecera. De aquí obtenemos número de vértices y caras.
    while (fgets(line, sizeof(line), stdin))
    {
        if (strncmp(line, "end_header", 10) == 0)
        {
            break;
        }
        // %*s le indica a sscanf que debe leer el dato pero no guardarlo en ninguna variable (lo descarta).
        else if (strncmp(line, "element vertex", 14) == 0)
        {
            sscanf(line, "%*s %*s %u", &vertices);
        }
        else if (strncmp(line, "element face", 12) == 0)
        {
            sscanf(line, "%*s %*s %u", &faces);
        }
    }

    // Reservamos memoria para guardar los vértices
    vertex *array = new vertex[vertices];

    // Al final del while, line apunta al string "end_header".
    // Queremos empezar a leer los vértices
    // std::cout << "Empezamos a leer los vertices ...\n";
    for (int v = 0; v < vertices; v++)
    {
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%f %f %f", &array[v].x, &array[v].y, &array[v].z);
        array[v].idx = v;
    }
    // std::cout << "Fin lectura de vertices.\n\n";

    // Lista de caras
    faceList lista_caras = faceList();
    nodeFace **actual = &lista_caras.head; // Doble apuntador para poder enlazar la lista nodo a nodo

    // Al final del for, line apunta al string del último vértice.
    // Queremos empezar a leer las caras.
    // std::cout << "Empezamos a leer las caras ...\n";
    for (int c = 0; c < faces; c++)
    {
        unsigned a_idx, b_idx, c_idx;
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%*d %u %u %u", &a_idx, &b_idx, &c_idx);

        nodeFace *nueva_cara = new nodeFace(a_idx, b_idx, c_idx);
        *actual = nueva_cara;       // Enlazamos el nuevo nodo a la lista
        actual = &nueva_cara->next; // Guardamos la dirección del apuntador next del nodo `nueva_cara`
    }
    // std::cout << "Fin lectura de caras.\n\n";

    // Variable global. Para poder usarla en la función de comparación de qsort.
    cm_global = centroide(array, vertices);
    qsort(array, vertices, sizeof(vertex), comparar_distancias);

    int n_erosion = 30;
    for (int k = 0; k < n_erosion; k++)
    {
        unsigned index = array[k].idx;
        lista_caras.find_node(index);
    }

    lista_caras.print_list();

    delete[] array;

    return 0;
}
/*

ply
format ascii 1.0
comment VCGLIB generated
element vertex 10
property float x
property float y
property float z
element face 20
property list uchar int vertex_indices
end_header
0.0 0.0 0.0
1.0 0.0 0.0
1.0 1.0 0.0
0.0 1.0 0.0
0.5 0.5 1.0
0.5 0.5 -1.0
0.5 0.0 0.5
1.0 0.5 0.5
0.5 1.0 0.5
0.0 0.5 0.5
3 0 1 6
3 1 2 7
3 2 3 8
3 3 0 9
3 0 6 9
3 1 7 6
3 2 8 7
3 3 9 8
3 4 0 1
3 4 1 2
3 4 2 3
3 4 3 0
3 5 1 0
3 5 2 1
3 5 3 2
3 5 0 3
3 4 6 7
3 4 7 8
3 5 9 6
3 5 8 9

*/