#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "Credenciales.h"
#include "HTML.h"

// Variables Globales //
const char *host = "http://httpbin.org/post";

// Crear el objeto de la clase ESP8266WebServer //
//ESP8266WebServer server(80); //El puerto 80 es el estandar para HTTP

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  http_setup();
  
}

void loop() {

  //server.handleClient(); // Administrar las peticiones

  WiFiClient client;
  HTTPClient http;

  String dato1 = "69%";
  String dato2 = "13cm";
  
  String post_data;
  post_data = "Nivel = " + dato1 + "&Distancia = " + dato2;

  Serial.printf("Host link: ");
  Serial.println(host);
  Serial.printf("Post data: ");
  Serial.println(post_data);

  http.begin(client, host);
  http.addHeader("Content-Type", "text/plain");

  int httpCode = http.POST(post_data);

  String payload = http.getString();

  Serial.print("Response Code: ");
  Serial.println(httpCode);
  Serial.print("Returned data form server: ");
  Serial.println(payload);

  http.end();
  delay(5000);

}
