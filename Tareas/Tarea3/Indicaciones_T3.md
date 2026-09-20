# Tarea 3

## ex1 
### Descripción
**Métodos de cadenas**
Dadas dos cadenas $S_1$ y $S_2$, formadas únicamente por letras minúsculas (sin espacios), determina cuál de las dos **es menor en orden alfabético** (orden lexicográfico), cópiala a una nueva variable, e imprime esa copia junto con su longitud.

Si ambas cadenas son exactamente iguales, cualquiera de las dos puede considerarse la "menor".

Este problema está pensado para practicar:

* *malloc* para reservar memoria dinámicamente para $S_1$, $S_2$, y tu copia (ya que sus tamaños solo se conocen en tiempo de ejecución).
* *strcmp* para comparar las cadenas.
* *strcpy* para copiar la cadena elegida a otra variable.
* *strlen* para obtener la longitud de esa copia.

**Importante sobre la memoria:** debes reservar suficiente espacio para cada cadena, incluyendo el carácter nulo ('\0') que la termina. Si $S_1$ tiene $L_1$ caracteres, necesitas al menos $L_1+1$ bytes para almacenarla correctamente.

### Entrada
* La primera línea contiene dos enteros $L_1$ y $L_2$ ($1\leq L_1,L_2\leq 1000$): las longitudes de $S_1$ y $S_2.
* La segunda línea contiene la cadena $S_1$, de exactamente $L_1$ caracteres.
* La tercera línea contiene la cadena $S_2$, de exactamente  $L_2$ caracteres.

Ambas cadenas contienen únicamente letras minúsculas de la *a* a la *z*.

### Salida
Imprime **dos líneas**:

1. La cadena menor en orden alfabético (tu copia, hecha con *strcpy*).
2. La longitud de esa copia (obtenida con *strlen*).

## ex2
### Descripción
**Descifrar la clave de bits**

Dadas 4 partes de 8 bits (valores entre 0 y 255) y una clave objetivo $K$ de 32 bits, debes guardarlas secuencialmente en un arreglo de tipo unsigned char de tamaño 4. Usando casting de punteros, interpreta la memoria de estos 4 bytes consecutivos como un solo entero sin signo de 32 bits, al que llamaremos $X$. Asume que el sistema utiliza arquitectura [Little-Endian](https://www.geeksforgeeks.org/dsa/little-and-big-endian-mystery/).

Una vez obtenido $X$, debes aplicar una transformación intercambiando sus 16 bits más significativos con sus 16 bits menos significativos para generar una nueva clave $Y$. Para lograrlo, **debes usar** operadores de bits (AND, OR, corrimiento a la izquierda y corrimiento a la derecha) siguiendo esta fórmula:

$$Y = ((X \ \& \ 0xFFFF0000) \gg 16) \ | \ ((X \ \& \ 0x0000FFFF) \ll 16)$$

### Entrada
* La primera línea contiene 4 enteros (la entrada es de int's, pero debes castear a unsigned char al guardarlo en el arreglo) separados por espacio $B_0,B_1,B_2,B_3$ ($0\leq B_i\leq 255$), correspondientes a los 4 bytes de información.
* La segunda línea contiene un **entero sin signo** de 32 bits $K$ ($0\leq K\leq 4294967295$), que representa la clave esperada.

### Salida
Imprime SI si el valor transformado $Y$ es exactamente igual a $K$, o NO en caso contrario.

## ex3
### Descripción
Descripción
En Valenciana, hay algunas ranas de colores en puestos cerca del centro. Estas ranas tienen colores llamativos distintos a los de las ranas usuales. Constanza quiere saber si esta especie de ranas está relacionada con las ranas normales.

Para esto, Constanza extrajo una **cadena de caracteres** $s$, de longitud $m$, que representa el ADN de una de estas curiosas ranas. Y Constanza tiene otra cadena de caracteres $t$, de longitud $n$. Ayuda a Constanza a determinar cuantas veces aparece la cadena $t$ en la $s$.

Formalmente, si $s_1 s_2\cdots s_m$ son los caracteres de $s$, decimos que $t$ ocurre en la posición $i$ (con $i\in \{1,2,\dots m-n\}$) si $s_i s_{i+1}\cdots s_{i+n}$ es igual (caracter por caracter) a $t$.

### Entrada
La primera línea de la entrada tiene un entero **positivo** $n$, la longitud de la cadena $t$. La siguiente línea tiene la cadena de caracteres $t$. Luego, la tercera línea de la entrada tiene un entero positivo $m$, la longitud de la cadena $s$. Por último, la cuarta línea de la entrada tiene la cadena $s$.

### Salida
Se espera que la salida sea un único **entero no negativo**, el número de veces que $t$ aparece como subcadena en $s$.

### Límites
* $s$ y $t$ únicamente contienen a los caracteres A, C, G y T.
* Se cumple que $1\leq n \leq 10$ y $1\leq m \leq 100$.

Nota: No se garantiza que $n<m$.

## ex4
### Descripción
Las ranas de Valenciana están aprendiendo a jugar ajedrez. Acaban de aprender a mover la reina. La rana Ajedrecista (quien les está enseñando), les comentó sobre el problema de las 8 reinas. Las ranas de Valenciana pensaron que era interesante, pero les llamó más la atención el siguiente problema: Dado un tablero de ajedrez de tamaño $N\times M$, con algunas casillas ocupadas por reinas, ¿Cuántas parejas de reinas se atacan entre sí?

Decimos que una pareja de reinas se atacan entre sí si están en la misma diagonal, fila o columna, y **no hay otra reina entre ellas**.

Ayuda a las ranas de Valenciana haciendo un programa en C que resuelva este problema.

### Entrada
La primera línea de la entrada tiene dos enteros positivos $N$ y $M$, que indican las dimensiones del tablero. Siguen $N$ líneas de $M$ caracteres cada una. Si el caracter $j$ de la fila $i$ es ., significa que la casilla $(i,j)$ está vacía; y si el caracter es Q, significa que hay una reina en ella.

### Salida
Se espera una única línea de salida, con un entero no negativo que indique la cantidad de parejas de reinas que se atacan entre sí. **Nota**: Si la reina en la casilla $(a,b)$ y la reina en la casilla $(c,d)$ se atacan entre sí, eso cuenta como una pareja de reinas que se ataca entre sí.

### Límites
Se garantiza que $1\leq N,M\leq 50$. El número de reinas en el tablero es un entero no negativo entre $0$ y $NM$.

## ex5
### Descripción
El profesor Alonso estaba enseñando a sus alumnos a generar números aleatorios en C. En particular, le comentó a la clase que para obtener un número real en **uniformemente distribuido** en el intervalo $[0,1]$, pueden usar (float)rand() / RAND_MAX. El estudiante Roy le preguntó si podían sumar $n$ números obtenidos de esta manera para obtener un número aleatorio **uniformemente distribuido** en el intervalo $[0,n]$.

Para responder esto, Alonso les propuso a sus estudiantes realizar el siguiente experimento:

1. Inicializa el generador de números aleatorios con time(NULL).
2. Sea $n=3000000$. Suma $n$ números reales uniformemente distribuidos en $[0,1]$, y guarda el resultado en $S$.
3. Calcula e imprime $s=\frac{|S-0.5n|}{n}$ **con 2 decimales de precisión**.

Alonso les explica a sus estudiantes que si $S$ es un número que se distribuye uniformemente en $[0,n]$, entonces $s$ se distribuye uniformemente en $[0.0,0.5]$. Por ende, sería muy probable que $s\geq 0.005$. Sin embargo, Alonso está bastante seguro de que esto no va a suceder para ningún estudiante. Tu trabajo es implementar el experimento de Alonso.

**Nota:** Alonso sabe que un programa que implemente correctamente su experimento tiene una probabilidad diminuta de fallar. Incluso si **todos los estudiantes de CIMAT y DEMAT** hicieran **miles de ejecuciones por segundo durante horas**, Alonso se sentiría confiado en apostar a que ninguna ejecución falla.

### Entrada
Este problema no tiene entrada.

### Salida
Imprime $s$ **con 2 dígitos de presición.** Esto es importante, porque si no lo haces, aunque tu programa sea correcto, OmegaUP te marcará un veredicto negativo.

### Bonus (opcional)
Esto no tiene valor alguno para tu calificación. Imagina que tú eres el ayudante de la clase que está diseñando este problema, y quieres saber qué tan grande tiene que ser el $n$ del experimento. Te gustaría que, con una probabilidad menor a $0.001$, un programa correcto calcule un $s>0.001$.

## ex6
### Descripción
Recientemente Daniel ingresó a su servicio social, donde su tarea principal es resolver sistemas de ecuaciones lineales. Por ser el nuevo, sus compañeros le asignaron únicamente los casos con matrices triangulares inferiores de la forma: $$Lx=b$$


Lejos de molestarse, Daniel sabe que estos sistemas son muy sencillos de resolver mediante el algoritmo de **sustitución hacia adelante** (forward substitution). Además, para ahorrar ancho de banda, en el laboratorio le entregan las matrices de forma comprimida: solo le pasan la diagonal principal y los elementos por debajo de ella, omitiendo todos los ceros de la parte superior.

Decidido a simplificar aún más sus responsabilidades, Daniel quiere escribir un programa que resuelva automáticamente los sistemas y calcule el error absoluto de comprobación $E$ para verificar la precisión numérica del vector solución obtenido $x$:

$$E = \sum_{i=1}^{n} ||(Lx)_i - b_i||$$

¿Puedes escribir el código que realice esta tarea por Daniel y (potencialmente) quedarte con sus horas de servicio social?

### Entrada
* En la primera línea, un entero $n$ que representa la dimensión de la matriz cuadrada $L$ (y la longitud de los vectores).
* Las siguientes $n$ líneas contienen la estructura comprimida de la matriz $L$:
    * La línea $1$ contiene $1$ valor: $L_{1,1}$.
    * La línea $2$ contiene $2$ valores: $L_{2,1},L_{2,2}$.
    * ...
    * La línea $i$ contiene $i$ valores separados por espacio: $L_{i,1},L_{i,2},\dots,L_{i,i}$.
* La última línea del input contiene $n$ números flotantes separados por espacio, que representan los elementos del vector $b$.

### Salida
* En $n$ lineas se tienen que imprimir los elementos del vector solución $x$, se usa el formato por defecto de float (printf("%f")).
* La última línea imprime el error del sistema usando el vector solución $x$, es decir el valor $E=\sum_{i=1}^{n}||(Lx)_i - b_i||$ en formato de float en notación científica (printf("%e")).

### Límites
* Usar memoria dinámica exacta para matrices triangulares.
* Dar una función que reciba dos vectores y su dimensión y devuelva su error absoluto.