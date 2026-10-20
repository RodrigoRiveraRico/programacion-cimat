
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 10000;

void genera_par_aleatorio(int *a, int *b);

// Estructura para guardar par de números aleatorios
struct Par
{
    int a;
    int b;
};

// ============================================================
// QUICK-FIND
// ============================================================

struct QuickFind
{
    int id[N];

    QuickFind()
    {
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
        }
    }

    int find(int a)
    {
        return id[a];
    }

    void join(int a, int b)
    {
        int id_a = find(a);
        int id_b = find(b);

        if (id_a == id_b)
        {
            return;
        }

        for (int i = 0; i < N; i++)
        {
            if (id[i] == id_a)
            {
                id[i] = id_b;
            }
        }
    }
};

// ============================================================
// QUICK-UNION
// ============================================================

struct QuickUnion
{
    int id[N];

    QuickUnion()
    {
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
        }
    }

    int find(int a)
    {
        while (a != id[a])
        {
            a = id[a];
        }

        return a;
    }

    void join(int a, int b)
    {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b)
        {
            return;
        }

        id[root_a] = root_b;
    }
};

// ============================================================
// WEIGHTED QUICK-UNION
// ============================================================

struct WeightedUnion
{
    int id[N];
    int sz[N];

    WeightedUnion()
    {
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
            sz[i] = 1;
        }
    }

    int find(int a)
    {
        while (a != id[a])
        {
            a = id[a];
        }

        return a;
    }

    void join(int a, int b)
    {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b)
        {
            return;
        }

        if (sz[root_a] < sz[root_b])
        {
            id[root_a] = root_b;
            sz[root_b] += sz[root_a];
        }
        else
        {
            id[root_b] = root_a;
            sz[root_a] += sz[root_b];
        }
    }
};

// ============================================================
// MAIN
// ============================================================

// Se prueba quick-find, quick-union y weighted-union con números aleatorios
int main()
{
    // semilla números aleatorios
    srand(static_cast<unsigned int>(time(nullptr)));

    QuickFind arreglo_find;
    QuickUnion arreglo_union;
    WeightedUnion arreglo_weighted;

    // Generar pares aleatorios
    Par *pares_random = new Par[N];

    for (int i = 0; i < N; i++)
    {
        genera_par_aleatorio(
            &pares_random[i].a,
            &pares_random[i].b);
    }

    clock_t inicio, fin;

    // QUICK-FIND
    inicio = clock();

    for (int i = 0; i < N; i++)
    {
        arreglo_find.join(
            pares_random[i].a,
            pares_random[i].b);
    }

    fin = clock();

    double t1 = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC;

    // QUICK-UNION
    inicio = clock();

    for (int i = 0; i < N; i++)
    {
        arreglo_union.join(
            pares_random[i].a,
            pares_random[i].b);
    }

    fin = clock();

    double t2 = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC;

    // WEIGHTED QUICK-UNION
    inicio = clock();

    for (int i = 0; i < N; i++)
    {
        arreglo_weighted.join(
            pares_random[i].a,
            pares_random[i].b);
    }

    fin = clock();

    double t3 = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC;

    // Resultados en milisegundos
    cout << t1 * 1000 << " " << t2 * 1000 << " " << t3 * 1000;

    delete[] pares_random;
    return 0;
}

void genera_par_aleatorio(int *a, int *b)
{
    *a = rand() % N;
    *b = rand() % N;
}