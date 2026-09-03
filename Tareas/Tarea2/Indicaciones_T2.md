# Tarea 2

## Ex1

### Descripción
Vas a leer una lista de números de longitud arbitraria y te detendrás cuando dicha lista deje de ser creciente o tenga un número negativo e imprimirás la longitud de la lista.

### Entrada
Una lista de números enteros de longitud arbitraria que termina o con un número negativo o con el último número siendo menor que el penultimo.

### Salida
La cantidad de números que leíste, sin incluir el que hace que la lista ya no sea creciente o el negativo.

### Límites
Cada número de la lista tiene valor absoluto menor a $10^9$ y no habrá más de $10^5$ números en la lista.

## Ex2

### Descripción
Vas a hacer un código que lea una cantidad arbitraria de números y los sume hasta que leas un número negativo.

### Entrada
Una lista de longitud arbitraria de números enteros que terminará con un número negativo (nota que no sabes cuántos números van a ser, tienes que leer hasta encontrar el negativo).

### Salida
La suma de los números de la lista sin el negativo del final.

### Límites
No serán más de 10000 números en la lista y su suma no excederá $10^9$.

## Ex3

### Descripción
Tenemos un entero positivo $n$. Si $n$ es **par**, queremos calcular **la potencia de 2 más grande que divide a $n$**. Si $n$ es **impar**, definimos $m=n+2$ . Si $m$ es un **múltiplo de 3**, queremos calcular $8\cdot m$. Y en otro caso, queremos obtener $m^2$.

### Entrada
La primera línea de la entrada es un entero positivo $t$, que indica el número de casos a resolver. Siguen $t$ líneas, tal que la i-ésima línea tiene únicamente un entero positivo $n_i$.

### Salida
Deberás imprimir $t$ líneas, tal que la i-ésima línea tenga el valor que queremos calcular par $n_i$.

### Límites
* $1\leq t \leq 1000$.
* Para todo $i\in \{1,2,\dots, t\}$, se cumple que $1\leq n_i \leq 1000$.

## Ex4

### Descripción
Tenemos un **intervalo de números enteros consecutivos** $[l,l+1,l+2,\dots,r].$ Para cada entero $l\leq i \leq r$, queremos determinar **si $i$ divide a la suma de los números del intervalo**. En otras palabras, para todo $i \in \{l,l+1,\dots,r\}$ queremos decidir si $\sum_{j=1}^{r} j $ es un múltiplo de $i$.

### Entrada
La única línea de la entrada tiene dos números enteros positivos $l$ y $r$ **separados por un espacio**. Se garantiza que $l\leq r$.

### Salida
Se esperan $r-l+1$ líneas de salida. La i-ésima línea tiene que ser "YES" (sin comillas) si $l+i-1$ divide a la suma del intervalo de números; y tiene que ser "NO" (sin comillas) en otro caso.

### Límites 
Se garantiza que $1\leq l\leq r \leq 1000$.

## Ex5

### Descripción
Decimos que un entero positivo $n$ es **bueno** si **no es divisible entre 3**, y **su residuo al dividirlo por 5 es exactamente 3**. Dados dos enteros positivos $l\leq r$, queremos calcular la suma de los enteros $j$ **buenos** que cumplan $l\leq j\leq r$. En otras palabras, queremos calcular la suma $\sum_{j=1}^{r} j\cdot I(j)$, donde $I(J)=0$ si $j$ no es bueno; y $I(j)=1$ si $j$ es bueno.

### Entrada
La primera línea de la entrada contiene un entero positivo $t$, que indica la cantidad de casos a resolver. Las siguientes $t$ líneas contienen dos enteros $l_i$ y $r_i$ **separados por un espacio**. Se garantiza que $l_i\leq r_i$.

### Salida
Se esperan $t$ líneas de salida, donde la i-ésima línea es el valor de la suma de enteros buenos en $\{l_i,l_i+1,\dots, r_i\}$.
.

### Límites 
* $1\leq t \leq 1000$.
* Para todo $i\in \{1,\dots, t\}$ se cumple que $1\leq l_i\leq r_i\leq 1000$.

## Ex6

### Descripción
Un hotel ha tenido mucha demanda en los últimos días. A veces se encuentra en crisis, ésto sucede cuando llegan más clientes de los que puede acomodar en sus habitaciones disponibles al mismo tiempo. Ayúdalo a identificar si en algún punto de su día se encuentra en crisis. Dado un hotel con $n$ habitaciones, el día está definido con una secuencia de enteros 1 o 0 representando la llegada y la salida de algún cliente, respectivamente. El día termina cuando encuentres un 2, marcando la hora de cierre del día.

### Entrada
En la primera línea recibiras un único entero positivo $n$.

En la segunada línea recibirás caracteres 1 o 0 separados por un espacio y un 2 al final de la lista, marcando el final del día.

### Salida
Imprime "SI" si el hotel se encuentra en crisis en algún punto del día o "NO" en caso contrario (sin comillas).

### Límites
* $1\leq n\leq 100$.
* No habrá 0 si no hay huéspedes dentro del hotel en ese momento.

## Ex7

### Descripción
**Paridad de Filas y Columnas**

Dada una matriz de enteros $A$ de tamaño $N\times M$, usa **memoria dinámica** para guardarlas y determina si se cumplen **ambas** condiciones al mismo tiempo:

1) La suma de los elementos de **cada fila** es **par**.
2) La suma de los elementos de **cada columna** es **impar**.

Si ambas condiciones se cumplen para todas las filas y todas las columnas, imprime _SI_. En caso contrario, imprime _NO_.

### Entrada
* La primera línea contiene dos enteros $N$ y $M$ ($1\leq N,M\leq 100$), el número de filas y columnas.
* Las siguientes $N$ líneas contienen $M$ enteros cada una: los elementos de $A$.

Cada elemento cumple  $-1000\leq A_{i,j}\leq 1000$. Se asegura que la suma de cada fila y columna cabe en un _int_.

### Salida
Imprime _SI_ si todas las filas tienen suma par y todas las columnas tienen suma impar. Imprime _NO_ en caso contrario.

## Ex8

### Descripción

**¿Es la transpuesta?**

Dadas dos matrices $A$ (de tamaño $N \times M$) y $B$ (de tamaño $P\times Q$), usa **memoria dinámica** para guardarlas y determina si $B$ es la transpuesta de $A$, es decir, si se cumple:
$$B_{j,i}=A_{i,j} \;\;\;\;\; \text{para todo } i,j$$

Recuerda que si $B=A^{T}$, entonces las dimensiones deben cumplir $P=M$ y $Q=N$ (las filas de $A$ son las columnas de $B$, y viceversa). Si las dimensiones no encajan de esta forma, $B$ no puede ser la transpuesta de $A$.

### Entrada
* La primera línea contiene dos enteros $N$ y $M$ ($1\leq N,M \leq 100$): dimensiones de $A$.
* Las siguientes $N$ líneas contienen $M$ enteros cada una: los elementos de $A$.
* La siguiente línea contiene dos enteros $P$ y $Q$ ($1\leq P,Q\leq 100$): dimensiones de $B$.
* Las siguientes $P$ líneas contienen $Q$ enteros cada una: los elementos de $B$.

Cada elemento de ambas matrices cumple $-1000\leq A_{i,j},B_{i,j}\leq 1000$.

### Salida
Imprime _SI_ si $B$ es la transpuesta de $A$, o _NO_ en caso contrario.

## Ex9

### Descripción
Daniel es gran fan de los polinomios y en su tiempo libre se dedica a escribir ejemplares sin importar su grado. Hace poco aprendió a derivar ¡lo que significa que puede obtener aún más polinomios a partir de los que ya ha escrito! Pero hay un pequeño problema: Daniel se lastimó todas sus extremidades por escribir demasiados polinomios.


Tu deber es ayudar a Daniel a generar las derivadas de sus polinomios. Dado un polinomio de grado $n$.

$$a_nx^n + a_{n-1}x^{n-1} + \dots + a_2x^2 + a_1x^1 + a_0x^0$$

es relativamente sencillo obtener su derivada

$$na_nx^{n-1} + (n-1)a_{n-1}x^{n-2} + \dots + 2a_2x^1 + a_1x^0$$

Realiza un programa con memoria dinámica que reciba los parámetros y coeficientes que describen un polinomio y devuelva la evaluación del polinomio original, la evaluación del polinomio derivado y sus nuevos coeficientes.

### Entrada
* La primera línea contendrá el punto $x$ en el que se evaluará el polinomio.
* La segunda linea contendrá el valor $n$ que indicará el grado del polinomio.
* Finalmente las siguientes $n+1$ lineas representarán los coeficientes del polinomio.

### Salida
* Evaluación del polinomio original en el punto $x$ (con 4 decimales de precisión).
* Evaluación del polinomio derivado en el punto $x$ (con 4 decimales de precisión).
* $n$ líneas con los coeficientes del polinomio derivado (cada uno con 4 decimales de precisión).

### Límites
* $1\leq n$

## Ex10

### Descripción
**Suma de matrices**

Dadas dos matrices $A$ y $B$ de números enteros de tamaño $M\times N$, usa **memoria dinámica** para guardarlas y calcula la matriz $C$ que resulta de sumar elemento por elemento ambas matrices, es decir:

$$C_{i,j}=A_{i,j}+B_{i,j}$$

### Entrada
* La primera línea contiene dos enteros $M$ y $N$ ($1\leq M,N \leq 100$), el número de filas y columnas.
* Las siguientes $M$ líneas contienen $N$ enteros cada una: los elementos de la matriz $A$.
* Las siguientes $M$ líneas contienen $N$ enteros cada una: los elementos de la matriz $B$.

Cada elemento de las matrices cumple $-1000\leq A_{i,j},B_{i,j}\leq 1000$.

### Salida
Imprime $M$ líneas con $N$ enteros cada una, separados por un espacio, representando la matriz $C$.

## Ex11
