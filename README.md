# Team Orienteering Problem - Forward Checking

# Compilación:

Para compilar, ir a la carpeta source del código, y escribir en consola: ``` make ```

# Ejecución

Para ejecutar, escribir en la consola ```make run < NOMBRE_INPUT.dat```

# Limpiar

Para limpiar los archivos intermedios, se es posible introducir el comando ```make clean```

# Limpiar todo

Si además se quiere borrar los archivos post compilación como el ejecutable, se puede introducir el comando ```make cleanall```

# Formato input

Las instancias tienen un formato preestablecido (igual a los ejemplos entregados por el ayudante) los cuales reciben en la primera linea la cantidad de nodos, luego la cantidad de rutas, el tiempo máximo, y posteriormente cada nodo con su posición x, su posición y, y su respectivo score:

Ejemplo:

```
n 8
m 2
tmax 12.5
4.600	7.100	0
5.700	11.400	20
4.400	12.300	20
2.800	14.300	30
3.200	10.300	15
3.500	9.800	15
4.400	8.400	10
7.800	11.000	0
```

# Formato output

El output se realiza por consola, donde se muestra una cantidad de datos, con su respectivo label para entendimiento:

Ejemplo:

```
Número Nodos: 21
Número Rutas: 2
Tiempo Máximo: 7.5
Velocidad: 1
Cantidad de soluciones posibles: 475
Cantidad de soluciones optimas: 4
Mejor solución encontrada:
Score total ruta: 90
Ruta 0:::  Score : 35 | Tiempo : 7.36313 | 0 9 10 20
Ruta 1:::  Score : 55 | Tiempo : 6.84821 | 0 6 11 12 13 20
```

* Número Nodos: Cantidad de nodos del grafo.
* Número Rutas: Cantidad de rutas requeridas.
* Tiempo Máximo: Tiempo máximo por cada ruta.
* Velocidad: Dato que no es introducido por consola, si no en el codigo fuente para calcular el tiempo. Por defecto es 1.
* Cantidad de soluciones posibles: Cantidad de soluciones factibles al problema.
* Cantidad de soluciones optimas: Cantidad de soluciones encontradas con puntaje máximo.
* Score total ruta: Puntaje asociado a todas las rutas.

Posteriormente a esto, se presentan las rutas de la siguiente manera:

```
Num de ruta::: Score: PUNTAJE_RUTA | Tiempo: TIEMPO_RUTA | NODOS_DE_RUTA
```
