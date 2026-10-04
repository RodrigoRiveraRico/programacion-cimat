#include <stdio.h>
#include <stdlib.h>

/// @brief Función para evaluar numéricamente una expresión prefija (notación polaca).
///
/// Función recursiva. En cada llamada recursiva se actualiza el apuntador a la cadena.
///
/// La función procesa una cadena que corresponde con una expresión válida en notaciónn polaca.
/// Las operaciones son entre números enteros.
/// Se supone que la expresión no tiene divisiones entre cero.
/// Se opera con división entera.
///
/// Ejemplo: "+ * 10 2 / 15 5" -> (10 * 2) + (15 / 5) = 23
///
/// Ejemplo: "+ - * 12 2 6 + 20 22" -> ((12 * 2) - 6) + (20 + 22) = 60
/// @param ptr **char Dirección de un apuntador a la cadena.
/// @return long int Resultado numérico.
/// @note Debe ingresarse una expresión válida.
long evaluarNotacionPrefija(char **ptr);

int main(void)
{

    // Longitud de la cadenda de texto.
    unsigned N;
    scanf("%u", &N);

    // Puntero a expresión.
    // La idea es que este apuntador se quede apuntando a la expresión.
    char *expresion = malloc((N + 1) * sizeof *expresion); // N caracteres + '\0'
    if (!expresion)
    {
        return 1;
    }
    getchar();                                       // Consumimos salto de línea
    fgets(expresion, (N + 1) * sizeof(char), stdin); // N caracteres + '\n'

    // puntero_lectura será el cursor sobre la cadena.
    // La idea es que este apuntador se desplace sobre la cadena.
    char *puntero_lectura = expresion;

    // Evaluación de la expresión.
    long resultado = evaluarNotacionPrefija(&puntero_lectura);

    printf("%ld", resultado);

    free(expresion);
    return 0;
}

// ptr manipulará a puntero_lectura
long evaluarNotacionPrefija(char **ptr)
{
    // La cadena tiene espacios en blanco. Hay que consumirlos.
    while (**ptr == ' ')
    {
        (*ptr)++;
    }

    // Llegamos al final de la cadena.
    if (**ptr == '\0')
    {
        return 0;
    }

    // Suponemos que la expresión prefija es válida.
    // El primer carácter en la expresión es un operador.
    char operador = **ptr;

    // CASO RECURSIVO
    // Evaluamos expresion1 operador expresion2
    if (operador == '+' ||
        operador == '-' ||
        operador == '*' ||
        operador == '/')
    {
        // Consumir el operador actual
        (*ptr)++;

        // Hacemos la evaluacion expresion1 operador expresion2
        long expresion1 = evaluarNotacionPrefija(ptr); // En esta llamada se actualiza el apuntador puntero_lectura. Recordar que la inteción de dicho apuntador es ser un cursor sobre la cadena.
        long expresion2 = evaluarNotacionPrefija(ptr); // En esta llamada trabajamos con el curso después de haber recorrido la expresion1.

        if (operador == '+')
            return expresion1 + expresion2;
        if (operador == '-')
            return expresion1 - expresion2;
        if (operador == '*')
            return expresion1 * expresion2;
        if (operador == '/')
            return expresion1 / expresion2; // División entera. Suponemos que no hay división entre cero.
    }

    // CASO BASE
    // El carácter leído no es un operador. Entonces es un número.
    else
    {
        long numero;
        unsigned caracteres_leidos; // Recordar que nos movemos sobre una cadena, por lo que hay que contar la cantidad de caracteres del número.

        // Con sscanf leemos el número de la cadena. Usamos el especificador %ld para long int.
        // El especificador %n cuenta la cantidad de caracteres leidos (corresponden al número).
        sscanf(*ptr, "%ld%n", &numero, &caracteres_leidos);
        (*ptr) += caracteres_leidos; // OJO sscanf no modifica al apuntador.
        return numero;
    }
}