# Level-Sensor
En este repositorio se encuentra la documentación, avances y pruebas para el proyecto de sensor de nivel para tanques.
<br>
<br>

## Contenidos
**API Mockup**
- En la carpeta de [Level Sensor HTML](https://github.com/Miguel-Carreon/Level-Sensor/tree/main/Level%20Sensor%20HTML) están los archivos de HTML y CSS, estos se tienen que guardar en el mismo directorio para que el [index](https://github.com/Miguel-Carreon/Level-Sensor/blob/main/Level%20Sensor%20HTML/index.html) pueda acceder a la 
[hoja de estilos](https://github.com/Miguel-Carreon/Level-Sensor/blob/main/Level%20Sensor%20HTML/style.css).
<br>

**Arduino**
- En la carpeta de [level_prototype_WiFi](https://github.com/Miguel-Carreon/Level-Sensor/tree/main/level_prototipe_WiFi) se encuentran dos archivos, los dos tienen que estar guardados en el mismo directorio, uno de ellos es un header file llamado [arduino_secrets](https://github.com/Miguel-Carreon/Level-Sensor/blob/main/level_prototipe_WiFi/arduino_secrets.h), en esta es donde se tienen que insertar las credenciales WiFi para que el código pueda funcionar en la red en la que se encuentre conectado cada uno. <br>
Este código se utilizó en el Arduino MKR, por lo que después de los cambios en la tarjeta de desarrollo, esta carpeta contiene código obsoleto que no se seguirá utilizando, sin embargo, a partir de esa idea se comenzó a desarrollar lo que se tiene para el nuevo MCU que se decidió utilizar.
- En la carpeta [level_prototype_WiFi_ESP8266](https://github.com/Miguel-Carreon/Level-Sensor/tree/test_branch/level_prototype_WiFi_ESP8266) se encuentra el primer acercamiento que se tuvo con el ESP8266 que es el nuevo MCU que se decidió utilizar, y la conectividad de este por medio de WiFi utilizando protocolo HTTP. El contenido de esta carpeta se quedó como prototipo, ya que el método con el que se decidió atacar la necesidad de comunicación inalámbrica que se tenía, resultó no ser el más optimo, sin embargo, sirvió para cimentar los principios en los que se basó el código que se utilizo para la implementación de este proyecto.
<br>

**Level Monitor ESP8266**
<br>
*En la carpeta level_monitor_ESP8266 se encuentran los archivos relacionados con el código final que se terminó implementando.*

- Primero se tiene el archivo [index](https://github.com/Miguel-Carreon/Level-Sensor/blob/test_branch/level_monitor_ESP8266/index.html) cuyo propósito es el de tener el código HTML en un formato donde se pueda observar y organizar mejor para poder realizar modificaciones sobre él, esto es debido a que en Arduino no se puede introducir el HTML como tal, ya que primero se tiene que comprimir para que todo el código este en una línea y se tienen que usar comandos de escape para que este sea compatible en C++. Es por eso que se puede ver otro archivo llamado [compressed_html](https://github.com/Miguel-Carreon/Level-Sensor/blob/test_branch/level_monitor_ESP8266/compressed_html.txt) en donde se tiene el código HTML antes mencionado, pero se tiene comprimido en una línea y listo para ser utilizado en Arduino.
- En la carpeta [ESP3266_web_server](https://github.com/Miguel-Carreon/Level-Sensor/tree/test_branch/level_monitor_ESP8266/ESP3266_web_server) se tiene todo lo relacionado con la implementación del proyecto en Arduino, en esta carpeta se pueden encontrar varios archivos .ino que al estar en el mismo directorio actúan como uno solo que se almacena en la memoria de programa del microcontrolador. Sin embargo, el trabajarlo por pestañas resulta en un código mas ordenado en donde se pueden separar definiciones de algoritmos y de declaraciones de configuración, des esta forma convertir un código grande en algo más ordenado y que tenga mas sentido para el lector.
- En el archivo de [Credenciales](https://github.com/Miguel-Carreon/Level-Sensor/blob/test_branch/level_monitor_ESP8266/ESP3266_web_server/Credenciales.h) es donde se cambia el texto que ahí aparece, por el SSID y la contraseña de la red WiFi para que el ESP8266 pueda conectarse a la red.
- El archivo [ESP8266_web_server](https://github.com/Miguel-Carreon/Level-Sensor/blob/test_branch/level_monitor_ESP8266/ESP3266_web_server/ESP3266_web_server.ino) es el que actúa como main, en donde todas las variables locales son declaradas y se mandan a llamar funciones que se encuentran en otros archivo a los voids principales, además de esto se declaran todas las librerías que se van a usar y se definen nombres para el GPIO que se va a utilizar en el header. También se tiene el algoritmo que permite que se haga la medición cada 300ms sin necesidad de parar el procesamiento con delays, además de hacer el handle client.
- En [HTTP_setup](https://github.com/Miguel-Carreon/Level-Sensor/blob/test_branch/level_monitor_ESP8266/ESP3266_web_server/HTTP_setup.ino) se hace toda la configuración WiFi, adicionalmente también se hace toda la configuración relacionada con el protocolo HTTP para la comunicación con la API. En este mismo archivo es donde vive el código HTML adaptado para Arduino.
- En el archivo [OLED_functions](https://github.com/Miguel-Carreon/Level-Sensor/blob/test_branch/level_monitor_ESP8266/ESP3266_web_server/OLED_functions.ino) se hace una función en la que se declaran todos los parámetros para iniciar el display OLED, además de esto se hace la configuración con la que este puede mostrar los parámetros deseados.
- En [sensor_lecture](https://github.com/Miguel-Carreon/Level-Sensor/blob/test_branch/level_monitor_ESP8266/ESP3266_web_server/sensor_lecture.ino) es el archivo que contiene el algoritmo que permite hacer la medición utilizando un sensor ultrasónico HC-SR04, además de que en esta parte es donde se realizan también, los cálculos necesarios para transformar la duración de un pulso ultrasónico, en unidades de distancia y después de eso en un porcentaje nivel.
- Al final de esta carpeta está [string_replace](https://github.com/Miguel-Carreon/Level-Sensor/blob/test_branch/level_monitor_ESP8266/ESP3266_web_server/string_replace.ino) es un algoritmo que se tenía pensado para reemplazar los datos que se iban a actualizar a través de un string. Sin embargo, esto se implementó de una manera más sencilla por ende este pedazo de código no cumple ninguna función activa.
<br>

**Imágenes**
- Por último, en la carpeta llamada [Pics](https://github.com/Miguel-Carreon/Level-Sensor/tree/test_branch/Pics) se encuentran fotos y video del desarrollo conceptual del proyecto y como es que este pasó a la realidad a través de un prototipo.
