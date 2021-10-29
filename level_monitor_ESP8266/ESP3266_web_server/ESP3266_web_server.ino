#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <string.h>
#include "Credenciales.h"

// Variables Globales:
int nivel = 0;

// Crear el objeto server de la clase ESP8266WebServer:
ESP8266WebServer server(80); //Puerto 80 es el estándar

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200); // Baudaje a 115200 baudios

  //Llamar la configuracion del protocolo HTTP:
  http_setup();

}

void loop() {

  // Prueba
  nivel++;
  delay(3000);
  
  server.handleClient(); // Administrar peticiones
    
}
