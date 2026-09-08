
# Notas

## Apuntadores

* Un apuntador `*p` guarda direcciones:
    - `p = &a;` Guarda la dirección de `a` en `p`.
    - `p = malloc(...);` Guarda la dirección que devuelve `malloc` en `p`.
    - `scanf("%...", p);` Es lo correcto si se quiere guardar algo en la dirección donde apunta `p`.
    - Si definimos `int *p;`, entonces `&p` es del tipo `int **`.


## Formato

* `scanf("%c", ...)` leerá los saltos de línea (_Enter_) que estén atrapados en el búfer. **Solución:** `scanf(" %c", ...)` poner un espacio antes de `%c`.

## scanf()

### Strings

* Las cadenas de formato deben ir estrictamente entre comillas dobles `("%c")`.

* `scanf("%s", ...)` coloca automáticamente `'\0'`. Solo hay que asignar la memoria suficiente para incluir `'\0'`.

#### <string.h>

* `strcpy(destino, origen)`.

* `strcmp(s1,s2)` Devuelve un `int`. Si es cero: `s1==s2`. Si es positivo: `s1>s2`. Si es negativo: `s1<s2`.