#include <iostream>
#include <vector>

// Contador intercambios en quick sort
static int global_N_q = 0;
// Contador intercambio en heap sort
static int global_N_h = 0;

////////////////////////////////////////////////////////////////////////////////
///////////////////// FUNCIONES AUXILIARES /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Función auxiliar para intercambiar elementos
 *
 * @param a Referencia a un elemento del arreglo
 * @param b Referencia a un elemento del arreglo
 */
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

/**
 * @brief Función auxiliar para imprimir el arreglo
 *
 * @param arr vector<int> El arreglo
 * @param ini int Índice inicio del arreglo
 * @param end int Índice final del arreglo
 */
void printArr(std::vector<int> &arr, int ini, int end)
{
    for (int i = ini; i <= end; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// QUICK SORT /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Función de partición para quick sort.
 *
 * Toma como pivote al último elemento del arreglo y ordena.
 * @param arr vector<int> El arreglo
 * @param ini int Índice inicio del arreglo
 * @param end int Índice final del arreglo
 * @return int Índice del pivote después de ordenar
 */
int partition(std::vector<int> &arr, int ini, int end)
{

    // Pivote : Último elemento del arreglo
    int pivote = arr[end];

    // Índice auxiliar para intercambios
    int i = ini - 1;
    // Índice que recorre el arreglo
    int j = ini;

    // Algoritmo de ordenamiento en función del pivote
    while (j < end)
    {
        // Mandamos a la izquierda todo aquello que sea menor al pivote
        if (arr[j] < pivote)
        {
            swap(arr[j], arr[++i]);

            global_N_q++; // Contador de intercambios
        }

        j++;
    }

    // Colocar el pivote en su correcta posición
    swap(arr[j], arr[++i]);

    global_N_q++; // Contador de intercambios

    // Índice del pivote después de ordenar
    return i;
}

/**
 * @brief Función quick sort
 *
 * La función ordena tomando como pivote el último elemento del sub-arreglo (ver función partition)
 * @param arr vector<int> Sub-arreglo
 * @param ini int Índice inicio del sub-arreglo
 * @param end int Índice final del sub-arreglo
 */
void quickSort(std::vector<int> &arr, int ini, int end)
{

    // Caso base.
    // Si los índices se cruzan es porque no hay elementos que ordenar.
    // Si los índice son iguales, solo hay un elemento.
    if (end - ini <= 0)
    {
        return;
    }

    // Índice del pivote
    int pivote_idx = partition(arr, ini, end);

    // Sub-arreglo izquierdo
    quickSort(arr, ini, pivote_idx - 1);
    // Sub-arreglo derecho
    quickSort(arr, pivote_idx + 1, end);
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// HEAP SORT //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Función que transforma un arreglo en heap max
 *
 * @param arr vector<int> El arreglo
 * @param n int Tamaño del arreglo
 * @param i int Índice raíz
 */
void heapify(std::vector<int> &arr, int n, int i)
{
    // Siendo i el índice de la raíz, nos interesa comparar el valor de la raíz con sus hijos izquierdo y derecho
    int mayor_idx = i;
    int left_idx = i * 2 + 1;
    int right_idx = i * 2 + 2;

    // Importante verificar que los índices de los hijos están dentro del arreglo

    // Comprobamos si hijo a la izquierda es mayor que la raíz
    if (left_idx < n && arr[left_idx] > arr[mayor_idx])
    {
        mayor_idx = left_idx;
    }

    // Comprobamos si hijo a la derecha era en realidad el mayor.
    if (right_idx < n && arr[right_idx] > arr[mayor_idx])
    {
        mayor_idx = right_idx;
    }

    // Ya tenemos identificado el mayor : verificamos que haya que hacer un intercambio
    if (i != mayor_idx)
    {
        swap(arr[i], arr[mayor_idx]);

        global_N_h++; // Contador de intercambios

        // Recursividad : heapify al sub-árbol hijo del intercambio
        heapify(arr, n, mayor_idx);
    }
}

/**
 * @brief Función heap sort para ordenar un arreglo
 *
 * @param arr vector<int> El arreglo
 * @param n int Tamaño del arreglo
 */
void heapSort(std::vector<int> &arr, int n)
{

    // Convertimos el arreglo en un heap max
    // A los nodo hoja no se le aplica heapify : empezamos desde el índice n/2 - 1
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // Ya tenemos en la raíz del árbol al mayor de todos los elementos : intercambiamos con el último elemento del sub-arreglo
    for (int i = n - 1; i > 0; i--)
    {

        swap(arr[0], arr[i]);

        global_N_h++; // Contador de intercambios

        // Recursividad : heapify desde la ráiz del árbol
        heapify(arr, i, 0);
    }
}

int main()
{

    // Tamaño del arreglo
    int N;
    std::cin >> N;

    // Llenado del arreglo (para ordernar con quick sort y con heap sort)
    std::vector<int> mi_arreglo_quicksort(N);
    std::vector<int> mi_arreglo_heapsort(N);
    for (int i = 0; i < N; i++)
    {
        int elem;
        std::cin >> elem;
        mi_arreglo_quicksort[i] = elem;
        mi_arreglo_heapsort[i] = elem;
    }

    quickSort(mi_arreglo_quicksort, 0, N - 1);
    heapSort(mi_arreglo_heapsort, N);

    std::cout << global_N_q - global_N_h;

    return 0;
}