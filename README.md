# PRACTICA 5- SINCRONIZACIÓN  
En el presente laboratorio se realizó un programa  en c++ y  la interfaz grafica de qt cretor, dicho programa consta de un banco un número determinado de clientes que acceden a él por medio de una memoria compartida.  El banco posee  un número  un  determinado número de cajeros  que son ingresados por consola (estos de crean de forma dinámica ),  las cajas se deben mostrar en la interfaz gráfica  con un dibujo que represente el estado de la caja (vacía en primera instancia y cuando llega un cliente debe cambiar al estado lleno ) a su vez se debe mostrar  el nombre e identificación del cliente que esta “consultado” en la caja, la consulta del cliente en cada caja dura alrededor de 5 y 20 segundos,  después de este tiempo la caja retorna a su estado vacío. Cuando todas las cajas del banco están llenas el cliente debe hacer cola hasta que alguna caja quede libre.

## Justificación.

El presente laboratorio se hace con el fin poder sincronizar dos procesos (cliente y banco) mediante la utilización de semáforos, evitando así que mas de un proceso acceda a un mismo recurso 

.}:}l.
