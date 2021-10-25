#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Credenciales.h"
#include "HTML.h"

// Variables Globales //


// Crear el objeto de la clase ESP8266WebServer //
ESP8266WebServer server(80); //El puerto 80 es el estandar para HTTP

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  Serial.println("\nESP8266 Web Server");
  WiFi.mode(WIFI_STA);
  WiFi.begin(NETWORK_SSID, NETWORK_PASS);

  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi ready");
  Serial.print("ESP82666 IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP Server started");
  
}

// Función para manejar las respuestas entrantes //
void handleRoot(){
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/html", html_file);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  server.handleClient(); // Administrar las peticiones
  
  int power = WiFi.RSSI();
  Serial.printf("Signal dB %d\n", power);
  delay(1000);
    
}
