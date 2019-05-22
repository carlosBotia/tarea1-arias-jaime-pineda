# PRACTICA 5- SINCRONIZACIÓN  
En el presente laboratorio se realizó un programa  en c++ y  la interfaz grafica de qt creator, dicho programa consta de un banco, y número determinado de clientes que acceden a él por medio de una memoria compartida.  El banco posee  un número    determinado  de cajeros  que son ingresados por consola (estos de crean de forma dinámica ),  las cajas se deben mostrar en la interfaz gráfica  con un dibujo que represente el estado de la caja (vacía en primera instancia y cuando llega un cliente debe cambiar al estado lleno ) a su vez se debe mostrar  el nombre e identificación del cliente que esta “consultado” en la caja, la consulta del cliente en cada caja dura alrededor de 5 y 20 segundos,  después de este tiempo la caja retorna a su estado vacío. Cuando todas las cajas del banco están llenas el cliente debe hacer cola hasta que alguna caja quede libre.

# Justificación.

El presente laboratorio se hace con el fin poder sincronizar dos procesos (cliente y banco) mediante la utilización de semáforos, evitando así que mas de un proceso acceda a un mismo recurso 


# procedimeinto y desarrollo 

en el siguiente esquemático se evidencia el funcionamiento del programa. 

![diagramas](https://user-images.githubusercontent.com/48129411/58141060-8afd9280-7c07-11e9-9b9b-0f7ae7063eb6.png)

Cuando se ejecuta el proceso banco este crea  una memoria compartida llamada `Banco`, la cual sirve para poder comunicarse con los distintos clientes que quieren acceder a ella. A su vez crea de forma dinámica la cantidad de cajeros que este posee tal como se presenta a continuación.

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
 en donde `char cajas_[100]` lleva el conteo de la cantidad de cajas que se crearon y su correspondiente  estado, y ` char nombreCliente[20],identidicacionCliente[20]`  tiene la información del cliente.
 
cuando el proceso cliente  inicia este revisa el arreglo  que contiene el número de cajas que el banco creo, si  `cajas_[0]=0` , quiere decir que la caja 1 está vacía y el cliente puede acceder a ella , inmediatamente se   cambia de estado  `cajas_[0]=1` , espera un determinado tiempo( de 5 a 20 segundos)  y vuelve a cambiar el estado a  vacío.
 ```php
  if(cajas_[0]==0)
  {
  cajas_[0]=1;
  sleep(tiempoAleatorio);
  cajas[0]=1;
  exit(1);
  } 
  ```
 
 para poder leer contantemente la memoria compartida que contiene la información de los clientes se utilizó un timer, este es un tipo de reloj interno que permite ejecutar una acción o función mediante una interrupción en QT, así el proceso banco esta leyendo contantemente la memoria compartida en busca de un nuevo cliente que se quiera suscribir.
 ```php
 cajas_banco::cajas_banco(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cajas_banco)
{
    ui->setupUi(this);
    QTimer *cronometro=new QTimer(this);
    connect(cronometro, SIGNAL(timeout()), this, SLOT(funcion()));
    cronometro->start(1000);
}

```
la funcion `funcion();`  es la encargada de revisar la memoria compartida periódicamente ,  esta función envían los datos recolectados a la función `iniciar(int cajas )` que se encarga de cambiar  el estado de las imágenes y la información de los clientes.

para controlar el flujo de clientes que acceden a los recursos (cantidad de cajas ) es necesario  la implementación de semáforos, la cantidad de semáforos es proporcional  al número de cajas que se tiene.

# conclusiones 
- A veces es necesario que dos o más procesos accedan a un recurso común (escribir en un mismo fichero, leer la misma zona de memoria, escribir en la misma pantalla, etc). El problema es que si lo hacen simultáneamente y de forma incontrolada, pueden "dañar" el uno la operación del otro (y dejar el fichero o la memoria con un contenido inservible o la pantalla ilegible).Para evitar este problema, están los semáforos. Un semáforo da acceso al recurso a uno de los procesos y se lo niega a los demás mientras el primero no termine


 
