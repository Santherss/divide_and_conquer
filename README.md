# Problemas de divide y vencerás

Este repositorio reúne cinco programas independientes en C++ que aplican técnicas de divide y vencerás. Cada solución se compila y ejecuta por separado.

## Requisitos

- Compilador compatible con **C++17**, como `g++`.
- Una terminal para compilar y ejecutar los programas.

## Compilación

Compile el ejercicio que desea ejecutar. Por ejemplo:

```bash
g++ -std=c++17 -O2 -Wall -Wextra ejercicio1.cpp -o ejercicio1
```

Después, proporcione la entrada por teclado o desde un archivo:

```bash
./ejercicio1 < entrada.txt
```

Para los demás ejercicios, reemplace `ejercicio1.cpp` y `ejercicio1` por el número correspondiente. Los ejecutables generados son archivos locales y no forman parte del código fuente.

---

### Ejercicio 1 · Formas de poner paréntesis

**Enunciado**

Dada una expresión formada por enteros y los operadores `+`, `-` y `*`, calcule todos los resultados que se pueden obtener al agruparla de todas las maneras posibles. Los resultados repetidos deben conservarse.

**Entrada**

Una expresión en una sola línea, sin espacios y de hasta 20 caracteres. Cada número está entre `0` y `99`.

**Salida**

Todos los resultados posibles en orden ascendente, separados por espacios. Si varias agrupaciones producen el mismo resultado, debe aparecer tantas veces como se obtiene.

**Ejemplo**

**Entrada**

```text
2*3-4*5
```

**Salida**

```text
-34 -14 -10 -10 10
```

**Solución**

Para cada operador de la expresión, se divide el problema en una parte izquierda y otra derecha. Se calculan recursivamente todos los resultados de ambas partes y se combinan en pares aplicando el operador que las separa. Cuando un segmento ya no contiene operadores, representa un número y constituye el caso base.

Se guardan los resultados de cada segmento en una tabla de memoización para reutilizar subproblemas. Al terminar, se ordena la lista completa. El número de resultados puede crecer exponencialmente con la cantidad de operadores, porque se deben producir todas las agrupaciones.

**Fragmento clave:** cada operador divide la expresión en dos llamadas recursivas; luego se combinan todos los pares de resultados.

```cpp
vector<int> izq = FORMAS(expresion, inicio, pos);
vector<int> der = FORMAS(expresion, inicio + pos + 1,
                         largo - pos - 1);

for (int valIzq : izq) {
    for (int valDer : der) {
        int r = 0;
        if (actual == '+') r = valIzq + valDer;
        else if (actual == '-') r = valIzq - valDer;
        else r = valIzq * valDer;
        R.push_back(r);
    }
}
```

La función `FORMAS` también consulta y almacena los resultados en `memoria[inicio][largo]` para evitar resolver de nuevo el mismo segmento.

**Implementación:** [`ejercicio1.cpp`](ejercicio1.cpp)

---

### Ejercicio 2 · Multiplicación de enteros grandes

**Enunciado**

Multiplique dos enteros no negativos que pueden tener hasta 10 000 dígitos. Los operandos deben tratarse como cadenas: no se deben convertir completos a tipos numéricos ni usar bibliotecas de enteros grandes. La solución se basa en el algoritmo de Karatsuba. Como parte del análisis, se solicita comparar su tiempo de ejecución con la multiplicación escolar para entradas de `10³` y `10⁴` dígitos.

**Entrada**

Dos enteros no negativos, uno por línea, de entre 1 y 10 000 dígitos. No tienen ceros iniciales, salvo el número `0`.

**Salida**

El producto de los dos enteros, representado como una cadena sin ceros iniciales.

**Ejemplo**

**Entrada**

```text
1234
5678
```

**Salida**

```text
7006652
```

**Solución**

Karatsuba divide cada número en mitades. En vez de calcular cuatro productos parciales, calcula tres: el producto de las mitades altas, el de las mitades bajas y el producto de las sumas de las mitades. Con restas obtiene el término cruzado y combina los valores desplazándolos según la posición decimal. Las sumas, restas y desplazamientos se implementan directamente sobre cadenas de dígitos.

La complejidad del algoritmo es `O(n^log₂3)`, donde `n` es la cantidad de dígitos. El programa implementa Karatsuba; la medición comparativa con la multiplicación escolar solicitada para los tamaños indicados no está incluida.

**Fragmento clave:** se calculan los tres productos recursivos de Karatsuba y se recombinan con desplazamientos decimales.

```cpp
string P1 = multiplicacionEnterosGrandes(A, C);
string P2 = multiplicacionEnterosGrandes(B, D);
string sumaAB = sumarCadenas(A, B);
string sumaCD = sumarCadenas(C, D);
string P3 = multiplicacionEnterosGrandes(sumaAB, sumaCD);

string resta1 = restarCadenas(P3, P1);
string cruzados = restarCadenas(resta1, P2);
string term1 = aumentarCeros(P1, 2 * m);
string term2 = aumentarCeros(cruzados, m);
string sumaParcial = sumarCadenas(term1, term2);
string resultadoFinal = sumarCadenas(sumaParcial, P2);
return quitarCerosIzquierda(resultadoFinal);
```

Las operaciones auxiliares (`sumarCadenas`, `restarCadenas` y `aumentarCeros`) trabajan directamente con cadenas.

**Implementación:** [`ejercicio2.cpp`](ejercicio2.cpp)

---

### Ejercicio 3 · Conteo de intercambios

**Enunciado**

Una secuencia de enteros distintos se ordena de forma ascendente intercambiando únicamente elementos adyacentes. Calcule el mínimo número de intercambios necesarios. Ese mínimo es igual al número de inversiones: pares de posiciones `(i, j)` tales que `i < j` y `a[i] > a[j]`.

**Entrada**

La entrada contiene varios casos. Cada caso comienza con `n` (`n ≤ 500 000`), seguido de `n` enteros, uno por línea, entre `0` y `999 999 999`. La entrada termina con un caso cuyo valor de `n` es `0`.

**Salida**

Un número por caso: el mínimo de intercambios adyacentes necesarios para ordenar la secuencia.

**Ejemplo**

**Entrada**

```text
5
9
1
0
5
4
0
```

**Salida**

```text
6
```

**Solución**

Se utiliza merge sort. Al combinar dos mitades ordenadas, si el siguiente elemento de la mitad derecha es menor que el siguiente de la izquierda, ese elemento forma una inversión con todos los elementos restantes de la mitad izquierda. Se suma esa cantidad de una sola vez y se continúa la mezcla.

El algoritmo cuenta las inversiones en `O(n log n)` tiempo y utiliza `O(n)` espacio auxiliar.

**Fragmento clave:** durante la mezcla, cuando el elemento derecho es menor, forma una inversión con cada elemento restante de la mitad izquierda.

```cpp
if (arr[i] <= arr[j]) {
    temp[k++] = arr[i++];
} else {
    temp[k++] = arr[j++];
    inversions += (mid - i + 1);
}
```

La suma `mid - i + 1` cuenta todas esas inversiones sin compararlas individualmente.

**Implementación:** [`ejercicio3.cpp`](ejercicio3.cpp)

---

### Ejercicio 4 · Par de puntos más cercano

**Enunciado**

Dado un conjunto de puntos en el plano, encuentre la distancia euclidiana entre los dos puntos más cercanos. La solución esperada debe tener complejidad `Θ(n log n)`.

**Entrada**

La entrada contiene varios casos. Cada caso comienza con `n` (`0 ≤ n ≤ 10 000`), seguido de `n` líneas con las coordenadas `x` e `y` de cada punto. Las coordenadas están entre `0` y `40 000`. La entrada termina con `n = 0`.

**Salida**

Para cada caso, imprima la distancia mínima con cuatro cifras decimales. Imprima `INFINITY` si hay un solo punto o si la distancia mínima es mayor o igual que `10 000`.

**Ejemplo**

**Entrada**

```text
5
0 0
10 10
3 4
20 20
4 5
1
7 7
0
```

**Salida**

```text
1.4142
INFINITY
```

**Solución**

Se ordenan los puntos por coordenada `x` y se divide el conjunto en dos mitades. Se calcula recursivamente la distancia mínima de cada mitad. Después se construye una franja alrededor de la línea divisoria y se comparan los puntos de esa franja que podrían mejorar la distancia encontrada.

La implementación ordena la franja por coordenada `y` en cada llamada recursiva. Por ello, su complejidad es `O(n log² n)`, aunque el enunciado solicita `Θ(n log n)`. Para alcanzar la complejidad solicitada, se puede conservar el orden por `y` al combinar las mitades y limitar las comparaciones de la franja.

**Fragmento clave:** se seleccionan los puntos cercanos a la línea divisoria, se ordenan por `y` y se comparan mientras la diferencia vertical pueda mejorar la distancia actual.

```cpp
if (abs(puntos[i].x - midPoint.x) < d)
    franja.push_back(puntos[i]);

sort(franja.begin(), franja.end(),
     [](const Punto& a, const Punto& b) {
         return a.y < b.y;
     });

for (size_t i = 0; i < franja.size(); i++) {
    for (size_t j = i + 1; j < franja.size() &&
         (franja[j].y - franja[i].y) < d; j++) {
        double dist = distanciaEuclidiana(franja[i], franja[j]);
        if (dist < d) {
            d = dist;
        }
    }
}
```

**Implementación:** [`ejercicio4.cpp`](ejercicio4.cpp)

---

### Ejercicio 5 · k-ésimo elemento más grande

**Enunciado**

Dado un arreglo de enteros y un entero `k`, encuentre el k-ésimo elemento más grande. Los valores repetidos cuentan por separado y no se permite ordenar el arreglo. Se espera una solución con complejidad `Θ(n)` en promedio.

**Entrada**

La primera línea contiene `n` y `k` (`1 ≤ k ≤ n ≤ 10⁵`). La segunda línea contiene `n` enteros entre `−10⁴` y `10⁴`.

**Salida**

El valor que ocupa la posición `k` al ordenar conceptualmente el arreglo de mayor a menor.

**Ejemplo**

**Entrada**

```text
6 2
3 2 1 5 6 4
```

**Salida**

```text
5
```

**Solución**

Quickselect particiona el arreglo alrededor de un pivote aleatorio. Tras la partición, los elementos menores o iguales al pivote quedan a un lado y los mayores al otro. Se compara la posición final del pivote con el índice que corresponde al k-ésimo mayor y se continúa únicamente en la parte que contiene la respuesta.

El tiempo esperado es `O(n)` y el peor caso es `O(n²)`. La selección se realiza sobre el arreglo recibido, sin ordenarlo por completo.

**Fragmento clave:** quickselect solo continúa por el lado que contiene el índice buscado. Para el k-ésimo mayor, ese índice es `n - k` en orden ascendente.

```cpp
if (pivotIndex == objetivo) return arr[pivotIndex];
if (pivotIndex > objetivo)
    return quickSelect(arr, bajo, pivotIndex - 1, objetivo);
return quickSelect(arr, pivotIndex + 1, alto, objetivo);
```

El pivote se elige aleatoriamente en `particion`, que lo coloca en su posición definitiva antes de devolver el índice.

**Implementación:** [`ejercicio5.cpp`](ejercicio5.cpp)
