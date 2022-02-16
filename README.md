# Librería MQTT de Redefine v2.5.0

Librería Adafruit MQTT base (v2.4.2): https://github.com/adafruit/Adafruit_MQTT_Library

Se hizo este _fork_ para arreglar un par de problemas que tenía la librería base, principalmente:

1. El chequeo de packet id no se hace, ya que el contador interno se incrementa aún cuando se enviaba un paquete incorrectamente. Esto hacía que el microcontrolador asumiera que sus paquetes estaban incorrectos aún cuando esto no fuera así.

2. Se activan los mensajes de _debug_ con el fin de saber exactamente qué se transmite y qué se recibe. 

3. Se inicializa la variable `packet_id_counter` en 1 en vez de 0. Esto ya que los _broker_ MQTT parten por defecto en 1, por lo que si se inicializa en 0, todos los paquetes iniciales en una conexión serán rechazados por el _broker_, forzando que el mensaje se repita cada vez que haya una conexión nueva.


