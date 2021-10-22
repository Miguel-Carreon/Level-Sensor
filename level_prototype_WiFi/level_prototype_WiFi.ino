#include <Arduino.h>
#include <WiFiNINA.h>
#include <SPI.h>
#include <utility/wifi_drv.h>
#include "arduino_secrets.h"

// Se definen las entradas con nombres:
#define trig  0
#define echo  1

// Declaración de variables:
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
int distance; // Esta variable almacena la distancia que se imprime
int duration;

int status = WL_IDLE_STATUS;

WiFiServer server(80); // Servidor local 80


void setup() {

  // Configuración de pinout //
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  WiFiDrv::pinMode(25, OUTPUT);
  WiFiDrv::pinMode(26, OUTPUT);
  WiFiDrv::pinMode(27, OUTPUT);
  
  // Iniciar la comunicacion serial a 9600 baudios //
  Serial.begin(9600);

  // Verificar estatus del módulo WiFi:
  if (WiFi.status() == WL_NO_MODULE) {
    rgbFunc(220, 20, 60); // Encender luz roja
    Serial.println("Communication with WiFi module failed!"); // Imprimir en caso de que no se pueda conectar
    // don't continue
    while (true);
  }

  // Intentar conectarse a red WiFi:
  
  while (status != WL_CONNECTED) {
    rgbFunc(255, 199, 44);
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // Esperar 500ms a la conexión:
    delay(500);
  }
  server.begin();
  // Conexión exitosa:
  rgbFunc(0, 255, 154);
  printWifiStatus(); //Llamar a la funcion que imprime estatus WiFi

}


// Funcion para imprimir el estatus WiFi //
void printWifiStatus() {
  
  // Imprimir el SSID de la red a la que se conectó:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Imprimir la dirección IP de la tarjeta:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Imprimir la intensidad de la señal:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
}


// Funcion para realizar la medición //
void ultrasonic_lecture(){

  //Envía una señal ultrasónica luego evalua el tiepo que tarda en regresar:
  digitalWrite(trig , HIGH);
  delay(1);
  digitalWrite(trig , LOW);
  delay(1);
  duration = pulseIn(echo , HIGH);
  distance = duration / 58.2; // Conversión a distancia en cm
  
}

// Función para encender un LED RGB //
void rgbFunc(int r, int g, int b) {
  
  WiFiDrv::analogWrite(26, r);   //RED
    
  WiFiDrv::analogWrite(25, g); //GREEN

  WiFiDrv::analogWrite(27, b);   //BLUE
  
}

void loop() {
  
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // Una petición HTTP termina con una linea en blanco
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
        // Envíar una respuesta si se recibe un caracter de nueva linea y la linea esta vacía:
        if (c == '\n' && currentLineIsBlank) {
          // Envíar un header HTTO de respuesta estandar
          client.println("HTTP/1.1 200 OK"); // 200 es el código que indica que esta todo OK
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // Actualizar la página cada 5 segundos
          client.println();
          
          // Sección de HTML //
          client.println("<!DOCTYPE HTML>");
          client.println("<html lang = \"en\">");
          client.println("<head>");
          client.println("<title>Level Sensor Web App</title>");
          client.println("<meta charset='UTF-8'>");
          client.println("<meta http-equiv='X-UA-Compatible' content='IE=edge'>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>"); // Hacer compatible para móviles
          client.println("</head>");
          ultrasonic_lecture(); // Llamar la funcin para hacer la lectura de la distancia
          client.println("<body style = \"background-color: white;\">");
          client.println("<h1 style = \"text-align: center; color: rgb(69, 80, 230); font-family: 'Trebuchet MS'\">Level Sensor Web display</h1>");
          client.println("<div style = \"background-color: rgb(69, 80, 230); width: 200px; margin: auto; text-align: center; border: rgb(69, 80, 230) 5px solid; border-radius: 5px; box-shadow: rgba(0, 0, 0, 0.19) 0px 10px 20px, rgba(0, 0, 0, 0.23) 0px 6px 6px;'\">");
          client.println("<p style = \"text-align: center; color: white; font-family: 'Trebuchet MS'; font-size: 20px;\">Distancia</p>");
          client.print("<p style = \"text-align: center; color: white; font-family: 'Arial Rounded MT Bold'; font-size: 50px\">");
          client.print(distance); // Imprimir la lectura de la distancia
          client.println("</p>");
          client.println("<p style = \"text-align: center; color: white; font-family: 'Trebuchet MS'; font-size: 20px;\">cm</p>");
          client.println("</div>");
          client.println("<br />");
          client.println("</body>");
          client.println("</html>");
          // termina la sección de HTML editable //
          break;
        }
        
        if (c == '\n') {
          // Empezando una nueva línea
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // Hay algo escrito en la nueva línea
          currentLineIsBlank = false;
        }
        
      }
      
    }
    
    // Darle tiempo al navegador para que reciba los datos:
    delay(1);

    // Cerrar la conexión:
    client.stop();
    Serial.println("client disconnected");
    
  }

}
