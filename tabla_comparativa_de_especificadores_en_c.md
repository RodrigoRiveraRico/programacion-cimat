# Tabla Comparativa de Especificadores de Formato en C

_De Gemini_

Esta tabla detalla los especificadores de formato más utilizados en C, sus tipos de datos correspondientes, el rango de valores típico y las diferencias más importantes en el comportamiento entre `printf` y `scanf`.

| Especificador | Tipo de Dato | Rango de Valores Típico | Diferencia clave entre `printf` y `scanf` |
| :--- | :--- | :--- | :--- |
| **`%c`** | `char` | `-128` a `127` o `0` a `255` (1 byte) | En `scanf` **no** ignora espacios en blanco ni saltos de línea anteriores. |
| **`%d`** | `int` | `-2,147,483,648` a `2,147,483,647` (4 bytes) | Lee/imprime enteros con signo en base 10. |
| **`%i`** | `int` | `-2,147,483,648` a `2,147,483,647` (4 bytes) | En `printf` es idéntico a `%d`. En `scanf` interpreta el prefijo ingresado (`0x` para hexadecimal, `0` para octal, sin prefijo para decimal). |
| **`%u`** | `unsigned int` | `0` a `4,294,967,295` (4 bytes) | Lee/imprime enteros sin signo en base 10. |
| **`%hd`** | `short int` | `-32,768` a `32,767` (2 bytes) | Requiere el modificador de longitud `h` en ambos. |
| **`%hu`** | `unsigned short` | `0` a `65,535` (2 bytes) | Usa el modificador `h` para enteros cortos sin signo. |
| **`%ld`** | `long int` | `-2,147,483,648` a `2,147,483,647` (32 bits) / hasta $\approx \pm 9.22 \times 10^{18}$ (64 bits) | Requiere el modificador `l`. |
| **`%lu`** | `unsigned long` | `0` a `4,294,967,295` (32 bits) / hasta $\approx 1.84 \times 10^{19}$ (64 bits) | Usa el modificador `l` para enteros largos sin signo. |
| **`%lld`** | `long long int` | `-9,223,372,036,854,775,808` a `9,223,372,036,854,775,807` (8 bytes) | Requiere el modificador doble `ll`. |
| **`%llu`** | `unsigned long long` | `0` a `18,446,744,073,709,551,615` (8 bytes) | Requiere el modificador doble `ll` para enteros de 64 bits sin signo. |
| **`%f`** | `float` | $\pm 1.17 \times 10^{-38}$ a $\pm 3.40 \times 10^{38}$ (4 bytes) | En `printf`, `%f` sirve tanto para `float` como para `double`. En `scanf`, **`%f` es estrictamente para `float`**. |
| **`%lf`** | `double` | $\pm 2.22 \times 10^{-308}$ a $\pm 1.79 \times 10^{308}$ (8 bytes) | En `printf`, `%lf` y `%f` son equivalentes. En `scanf`, **`%lf` es obligatorio para leer un `double`**. |
| **`%Lf`** | `long double` | $\pm 3.36 \times 10^{-4932}$ a $\pm 1.18 \times 10^{4932}$ (8 a 16 bytes) | Requiere la `L` mayúscula en ambos casos. |
| **`%e` / `%E`** | `float` / `double` | Mismo rango que `float`/`double` | En `printf` imprime en notación científica. En `scanf` procesa valores de coma flotante igual que `%f`. |
| **`%s`** | `char[]` / `char*` | Depende del tamaño del buffer | En `printf` imprime la cadena hasta el carácter nulo `\0`. En `scanf` lee caracteres **hasta el primer espacio en blanco** y no requiere el operador `&`. |
| **`%p`** | Puntero (`void*`) | Depende de la arquitectura (32 bits o 64 bits) | Imprime o lee direcciones de memoria (generalmente en notación hexadecimal con prefijo `0x`). |
| **`%x` / `%X`** | `unsigned int` | `0` a `4,294,967,295` (representación Hexadecimal) | Imprime/lee en hexadecimal (letras minúsculas con `%x`, mayúsculas con `%X`). |
| **`%o`** | `unsigned int` | `0` a `4,294,967,295` (representación Octal) | Imprime/lee en formato octal (base 8). |

---

## Observaciones Técnicas Clave

1. **Uso de direcciones de memoria (`&`)**:
   * En `printf` se pasa el valor de la variable directamente: `printf("%d", numero);`.
   * En `scanf` se requiere la dirección de memoria usando el operador `&`: `scanf("%d", &numero);` (excepto con arreglos de caracteres/cadenas procesados con `%s`).

2. **Diferencia Crítica en Números Flotantes**:
   * **`printf`**: `%f` acepta tanto `float` como `double` debido a la promoción automática de tipos en C para argumentos variádicos.
   * **`scanf`**: Es estricto. Se **debe** usar `%f` para `float` y `%lf` para `double`. Usar el incorrecto causará sobreescritura errónea de memoria.

3. **Comportamiento del especificador `%i` frente a `%d`**:
   * En `printf`: Ambas opciones imprimen en base 10 de forma idéntica.
   * En `scanf`: `%i` interpreta la entrada del usuario según el formato:
     * Prefijo `0x` o `0X` $\rightarrow$ Hexadecimal.
     * Prefijo `0` $\rightarrow$ Octal.
     * Sin prefijo $\rightarrow$ Decimal.

4. **Lectura de cadenas (`%s`)**:
   * `scanf("%s", buffer);` se detiene al encontrar cualquier espacio, tabulador o salto de línea. Para limitar la longitud y evitar desbordamientos de buffer se recomienda un ancho máximo, por ejemplo: `scanf("%19s", buffer);`.