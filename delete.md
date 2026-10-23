
/* El destructor se ejecuta automaticamente?

¡Sí\! En C++, el destructor se ejecuta automáticamente cuando un objeto llega al final de su tiempo de vida. No necesitas llamarlo manualmente.

En tu implementación, tienes este destructor:

cpp
```
~my_list() {
    clear();
}
```

Esto significa que, cuando un objeto de tipo `my_list` deja de existir, se ejecuta `clear()` para liberar todos los nodos que la lista haya reservado con `new`.

## 1. ¿Cuándo se ejecuta?

### Caso A: Al salir de una función

Considera tu `main()`:

cpp
```
int main() {
    my_list mi_lista;

    mi_lista.push_back(10);
    mi_lista.push_back(20);

    std::cout << mi_lista.size() << '\n';

    return 0;
}
```

Ocurre lo siguiente:

1. Se crea `mi_lista`.

Se ejecuta el constructor `my_list()`. Inicialmente, `head` y `tail` son `nullptr` y `sz` es `0`.

2. Se insertan dos nodos.

`push_back()` reserva memoria para los nodos con `new`.

3. Termina `main()`.

`mi_lista` sale de su tiempo de vida y C++ llama automáticamente a `~my_list()`.

4. Se ejecuta `clear()`.

Se liberan los nodos y se evita dejar esa memoria reservada sin necesidad.

## 2. ¿Y si creo un objeto dentro de un bloque?

cpp
```
int main() {
    std::cout << "Antes\n";

    {
        my_list lista;
        lista.push_back(10);

        std::cout << "Dentro del bloque\n";
    } // Aquí se ejecuta el destructor.

    std::cout << "Despues\n";
}
```

La salida será:

text
```
Antes
Dentro del bloque
Despues
```

Aunque no veas una llamada explícita al destructor, este se ejecuta al cerrar el bloque `}` en el que se declaró `lista`.

## 3. ¿Debo llamar al destructor manualmente?

No. No hagas esto:

cpp
```
lista.~my_list(); // No recomendado
```

Si llamas manualmente al destructor de un objeto que sigue dentro de su tiempo de vida, puedes provocar que se liberen sus recursos y que después se vuelva a ejecutar el destructor automáticamente. Eso puede ocasionar errores graves, como liberar la misma memoria dos veces.

En cambio, si quieres vaciar la lista sin destruir el objeto, utiliza:

cpp
```
lista.clear();
```

La lista seguirá existiendo y podrás insertar nuevos nodos.

## 4. ¿Qué pasa con los objetos creados con `new`?

Hay una diferencia importante:

cpp
```
my_list a;                 // Destructor automático al salir del ámbito.
my_list* b = new my_list;  // El destructor no se ejecuta al salir del ámbito.
```

En el segundo caso, `b` es un puntero a un objeto creado dinámicamente. Debes gestionar su tiempo de vida; si usas `delete b`, se ejecutará el destructor de `my_list`.

En C++ moderno, generalmente es preferible usar `std::unique_ptr` para administrar este tipo de objetos automáticamente.

En resumen: en tu programa, `~my_list()` se ejecuta automáticamente cuando `mi_lista` sale de su ámbito. El destructor llama a `clear()`, y este libera los nodos que la lista creó. Esa es precisamente una de las funciones más importantes de un destructor en una clase que administra memoria.
*/