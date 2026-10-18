#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct  {
    float x, y, z;
} Vertice;

int main(void){

    int vertices;
    int faces;
    int contador_vertices_z_no_negativo;
    int contador_caras_tres_vertices;

    // Para guardar los caracteres leídos línea por línea
    char line[256];

    // Se lee la cabecera. De aquí obtenemos número de vértices y caras.
    while(fgets(line, sizeof(line) ,stdin)){
        if (strncmp(line, "end_header", 10) == 0){
            break;
        }
        // %*s le indica a sscanf que debe leer el dato pero no guardarlo en ninguna variable (lo descarta).
        else if(strncmp(line, "element vertex", 14) == 0){
            sscanf(line, "%*s %*s %d", &vertices);
        }
        else if(strncmp(line, "element face", 12) == 0){
            sscanf(line, "%*s %*s %d", &faces);
        }
    }

    // Reservamos memoria para guardas los vértices
    Vertice *array = malloc(vertices * sizeof *array);
    if(!array){
        return 1;
    }
    // Al final del while, line apunta al string "end_header".
    // Queremos empezar a leer los vértices
    contador_vertices_z_no_negativo = 0;
    for(int v=0;v<vertices;v++){
        fgets(line, sizeof(line) ,stdin);
        sscanf(line, "%f %f %f", &array[v].x, &array[v].y, &array[v].z);
        if(array[v].z > 0){
            contador_vertices_z_no_negativo++;
        }
    }
    // Al final del for, line apunta al string del último vértice.
    // Queremos empezar a leer las caras.
    contador_caras_tres_vertices = 0;
    for(int c=0;c<faces;c++){
        int numero_vertices;
        fgets(line, sizeof(line) ,stdin);
        sscanf(line, "%d %*s", &numero_vertices);
        if(numero_vertices == 3){
            contador_caras_tres_vertices++;
        }
    }

    printf("%d\n", vertices);
    printf("%d\n", faces);
    printf("%d\n", contador_caras_tres_vertices);
    printf("%d\n", contador_vertices_z_no_negativo);
    free(array);
    return 0;
}