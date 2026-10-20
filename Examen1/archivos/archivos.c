/*
| Modo   | Significado                          |
| ------ | ------------------------------------ |
| `"r"`  | Leer                                 |
| `"w"`  | Escribir; crea o sobrescribe         |
| `"a"`  | Escribir al final; crea si no existe |
| `"r+"` | Leer y escribir                      |
| `"w+"` | Leer y escribir; sobrescribe         |
| `"a+"` | Leer y escribir al final             |
| `"rb"` | Leer binario                         |
| `"wb"` | Escribir binario                     |
| `"ab"` | Agregar binario                      |
*/

#include <stdio.h>


/*
 * Abre un archivo.
 *
 * nombre : nombre o ruta del archivo.
 * modo   : modo de apertura, por ejemplo:
 *          "r"  -> lectura de texto
 *          "w"  -> escritura de texto
 *          "rb" -> lectura binaria
 *          "wb" -> escritura binaria
 *
 * Retorna:
 *      Un puntero FILE si el archivo se abrió correctamente.
 *      NULL si ocurrió un error.
 */
FILE *abrir_archivo(const char *nombre, const char *modo)
{
    return fopen(nombre, modo);
}


/*
 * Cierra un archivo previamente abierto.
 *
 * Retorna:
 *      0  -> si el archivo se cerró correctamente.
 *      EOF -> si ocurrió un error.
 */
int cerrar_archivo(FILE *archivo)
{
    return fclose(archivo);
}


/*
 * Lee una línea de un archivo de texto.
 *
 * archivo : archivo del que se quiere leer.
 * buffer  : arreglo donde se almacenará la línea.
 * tam     : tamaño máximo del buffer.
 *
 * fgets() lee como máximo tam - 1 caracteres y agrega
 * '\0' al final de la cadena.
 *
 * Retorna:
 *      1 -> si se leyó una línea correctamente.
 *      0 -> si no se pudo leer (por ejemplo, EOF).
 */
int leer_linea(FILE *archivo, char *buffer, size_t tam)
{
    return fgets(buffer, tam, archivo) != NULL;
}


/*
 * Escribe una cadena en un archivo de texto.
 *
 * archivo : archivo donde se escribirá.
 * texto   : cadena que se quiere escribir.
 *
 * fputs() escribe la cadena sin agregar automáticamente
 * un salto de línea.
 *
 * Retorna:
 *      1 -> si la escritura fue exitosa.
 *      0 -> si ocurrió un error.
 */
int escribir_linea(FILE *archivo, const char *texto)
{
    return fputs(texto, archivo) != EOF;
}


/*
 * Lee datos binarios desde un archivo.
 *
 * archivo      : archivo del que se leerán los datos.
 * datos        : dirección de memoria donde se almacenarán.
 * tam_elemento : tamaño, en bytes, de cada elemento.
 * cantidad     : número de elementos que se quieren leer.
 *
 * void * permite que la función pueda trabajar con
 * diferentes tipos de datos: int, double, estructuras, etc.
 *
 * Retorna:
 *      El número de elementos que fueron leídos correctamente.
 */
size_t leer_binario(FILE *archivo,
                    void *datos,
                    size_t tam_elemento,
                    size_t cantidad)
{
    return fread(datos, tam_elemento, cantidad, archivo);
}


/*
 * Escribe datos binarios en un archivo.
 *
 * archivo      : archivo donde se escribirán los datos.
 * datos        : dirección de memoria de los datos.
 * tam_elemento : tamaño, en bytes, de cada elemento.
 * cantidad     : número de elementos que se quieren escribir.
 *
 * El parámetro const indica que esta función no modifica
 * los datos originales.
 *
 * Retorna:
 *      El número de elementos que fueron escritos correctamente.
 */
size_t escribir_binario(FILE *archivo,
                        const void *datos,
                        size_t tam_elemento,
                        size_t cantidad)
{
    return fwrite(datos, tam_elemento, cantidad, archivo);
}

// int main(void){

//     FILE *ptr=abrir_archivo("datos.txt", "r");
//     if(!ptr){
//         return 1;
//     }

//     char sexo[4];
//     int edad=-1;
//     float dato;
//     fscanf(ptr, "%s %d %f",sexo,&edad,&dato);   // Es análogo a si leyera desde la consola
//     printf("%s %d %.2f", sexo, edad, dato);

//     cerrar_archivo(ptr);

//     return 0;
// }

int main(void){

    FILE *f = abrir_archivo("datos.bin", "wb");

    if (f == NULL) {
        return 1;
    }

    int v[5] = {1, 2, 3, 4, 5};

    escribir_binario(f, v, sizeof(v[0]), 5);

    cerrar_archivo(f);

    return 0;
}