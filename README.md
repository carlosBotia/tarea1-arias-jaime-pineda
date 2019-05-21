# PRACTICA 5- SINCRONIZACIÓN  
En el presente laboratorio se realizó un programa  en c++ y  la interfaz grafica de qt cretor, dicho programa consta de un banco un número determinado de clientes que acceden a él por medio de una memoria compartida.  El banco posee  un número  un  determinado  de cajeros  que son ingresados por consola (estos de crean de forma dinámica ),  las cajas se deben mostrar en la interfaz gráfica  con un dibujo que represente el estado de la caja (vacía en primera instancia y cuando llega un cliente debe cambiar al estado lleno ) a su vez se debe mostrar  el nombre e identificación del cliente que esta “consultado” en la caja, la consulta del cliente en cada caja dura alrededor de 5 y 20 segundos,  después de este tiempo la caja retorna a su estado vacío. Cuando todas las cajas del banco están llenas el cliente debe hacer cola hasta que alguna caja quede libre.

# Justificación.

El presente laboratorio se hace con el fin poder sincronizar dos procesos (cliente y banco) mediante la utilización de semáforos, evitando así que mas de un proceso acceda a un mismo recurso 
' svsjvjshvsjhvs bbbbbbbbb'

# procedimeinto y desarrollo 

Cuando se ejecuta el proceso banco este crea  una memoria compartida llamada  “ nombre “, la cual sirve para poder comunicarse con los distintos clientes que quieren acceder a ella. A su vez crea de forma dinámica la cantidad de cajeros que este posee tal como se presenta a continuación.

<pre><code>$ ./banco_gui 4</code></pre>

![cajeros](https://user-images.githubusercontent.com/48129411/58126219-16f7c600-7bd8-11e9-8c98-3c156373044a.jpg)

después de crear la memoria compartida al ejecutar el  proceso banco,  se  ejecutar el cliente, en donde el primer argumento corresponde a la identificación y el segundo al nombre.

<pre><code>$./cliente 10752321635 carlos</code></pre>

  ![cajerosm](https://user-images.githubusercontent.com/48129411/58127906-106b4d80-7bdc-11e9-9dd5-50ddcbdd1bbe.jpg)
  
 a medida que los clientes van llegando se van acomodando a los cajeros que están libres.

Se creo una estructura la cual es compartida por los dos procesos.

```php

 
 typedef struct
    {
    char cajas_[100];
    char nombreCliente[20];
    char identidicacionCliente[20];
    {


```
 en donde `char cajas_[100]` lleva el conteo de la cantidad de cajas se crearon y su correspondiente  estado, y ` char nombreCliente[20],identidicacionCliente[20]` información del cliente 
