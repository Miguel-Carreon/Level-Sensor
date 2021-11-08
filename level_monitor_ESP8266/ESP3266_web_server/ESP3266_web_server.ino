#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>
#include "Credenciales.h"

#define trig  D5
#define echo  D6
#define width 128
#define height 32
#define OLED_RESET LED_BUILTIN

// Variables Globales:
int distance;
int duration;
int nivel;
unsigned long lecture_interval;

// Crear el objeto server de la clase ESP8266WebServer:
ESP8266WebServer server(80); //Puerto 80 es el estándar

void setup() {

  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200); // Baudaje a 115200 baudios

  //Llamar la configuracion del display OLED:
  oled_setup();

  //Llamar la configuracion del protocolo HTTP:
  http_setup();

}

void loop() {

  // Realizar la lectura y actualizacion de datos en el display cada 300ms:
  if ((millis() - lecture_interval) > 300){
    ultrasonic_lecture();
    Serial.print("Distancia: ");
    Serial.println(distance);
    oled_display("Distancia: ", distance, " cm");
    lecture_interval = millis();
  }
  
  server.handleClient(); // Administrar peticiones
    
}
