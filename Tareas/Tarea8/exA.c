#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("data.txt", "r");
    if (!fp) return 1;

    char line[256];

    /* Leer hasta el delimitador */
    while (fgets(line, sizeof line, fp)) {
        if (strncmp(line, "END_HEADER", 10) == 0)
            break;
        /* opcional: parsear el header aquí */
    }

    /* Ahora leer los datos */
    while (fgets(line, sizeof line, fp)) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}   