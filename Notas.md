
# Notas

## Lógica en C
* `printf(0 ? "V" : "F");` devuelve `F` ya que el cero es el falso lógico.
* `printf(20 ? "V" : "F");` devuelve `V` ya que cualquier número diferente de cero es el verdadero lógico.

## Apuntadores

* Un apuntador `*p` guarda direcciones:
    - `p = &a;` Guarda la dirección de `a` en `p`.
    - `p = malloc(...);` Guarda la dirección que devuelve `malloc` en `p`.
    - `scanf("%...", p);` Es lo correcto si se quiere guardar algo en la dirección donde apunta `p`.
    - Si definimos `int *p;`, entonces `&p` es del tipo `int **`.
    - Declarar un puntero no crea el objeto al que apunta.
        - `_mi_struct_ *p` solo crea el puntero.
        - `_mi_struct_ p` crea realmente un objeto `_mi_struct_`.
        - `_mi_struct_ *p = malloc(sizeof *p)` crea el puntero y reserva memoria para `_mi_struct_`.


## Formato

* `scanf("%c", ...)` leerá los saltos de línea (_Enter_) que estén atrapados en el búfer. **Solución:** `scanf(" %c", ...)` poner un espacio antes de `%c`.

### Especificadores


| Tipo de dato | Especificador | Uso en `printf` (Imprimir) | Uso en `scanf` (Leer) | ¿Lleva `&` en `scanf`? |
| :--- | :---: | :--- | :--- | :---: |
| **Entero** (`int`) | `%d` o `%i` | Pasa el **valor** directamente.<br>Ej: `printf("%d", num);` | Pasa la **dirección** de la variable.<br>Ej: `scanf("%d", &num);` | **Sí** |
| **Carácter** (`char`) | `%c` | Pasa el **valor** del carácter.<br>Ej: `printf("%c", letra);` | Pasa la **dirección** del carácter.<br>Ej: `scanf("%c", &letra);` | **Sí** |
| **Flotante** (`float`) | `%f` | Pasa el **valor** decimal.<br>Ej: `printf("%f", nota);` | Pasa la **dirección** del flotante.<br>Ej: `scanf("%f", &nota);` | **Sí** |
| **Double** (`double`) | `%f` / `%lf` | En `printf` se puede usar `%f` o `%lf` indistintamente. | En `scanf` **obligatoriamente** usa **`%lf`**.<br>Ej: `scanf("%lf", &double_num);` | **Sí** |
| **Cadena** (`char *`) | `%s` | Pasa la **dirección** (el apuntador).<br>Ej: `printf("%s", cadena);` | Pasa la **dirección** (el arreglo ya es una dirección).<br>Ej: `scanf("%s", cadena);` | **NO** |
| **Dirección** (`void *`) | `%p` | Pasa el apuntador para ver la dirección en hexadecimal.<br>Ej: `printf("%p", p);` | Raramente usado en `scanf`, pero lee una dirección hexadecimal. | **No** (ya es una dirección) |

#### Notas sobre `%d` y `%i`
 1. En `printf`
Tanto `%d` como `%i` esperan un entero con signo y lo imprimen en **base 10 (decimal)**. Si la variable vale `10`, ambos imprimirán `10`.

2. En `scanf` ¡OJO!
* **`%d` (Decimal):** Obliga a `scanf` a interpretar la entrada **estrictamente como un número base 10**. Si el usuario escribe `012`, `scanf` ignora el cero y guarda el número doce (`12`).
* **`%i` (Entero con detección automática de base):** Permite a `scanf` adivinar la base numérica según los **prefijos** que escriba el usuario en la consola:

| Si el usuario escribe... | Prefijo detectado | Cómo lo interpreta `%i` | Valor guardado en memoria (en base 10) |
| :--- | :--- | :--- | :--- |
| `12` | Ninguno | Decimal (Base 10) | **12** |
| `012` | Un `0` al inicio | Octal (Base 8) | **10** (porque \(1 \times 8^1 + 2 \times 8^0 = 10\)) |
| `0x12` o `0X12` | `0x` o `0X` al inicio | Hexadecimal (Base 16) | **18** (porque \(1 \times 16^1 + 2 \times 16^0 = 18\)) |



## scanf()

### Strings

* Las cadenas de formato deben ir estrictamente entre comillas dobles `("%c")`.

* `scanf("%s", ...)` coloca automáticamente `'\0'`. Solo hay que asignar la memoria suficiente para incluir `'\0'`.

#### <string.h>

* `strcpy(destino, origen)`.

* `strcmp(s1,s2)` Devuelve un `int`. Si es cero: `s1==s2`. Si es positivo: `s1>s2`. Si es negativo: `s1<s2`.

## printf()

* Al usar `%s`, le estás diciendo a `printf`: "Aquí tienes la dirección de memoria donde empieza el texto. Ve a esa dirección e imprime carácter por carácter hasta que encuentres el terminador nulo `'\0'`".