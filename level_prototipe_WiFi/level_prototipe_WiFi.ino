#include <Arduino.h>
#include <WiFiNINA.h>
#include <SPI.h>
#include "arduino_secrets.h"

#define trig  0
#define echo  1

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
int distance;
int duration;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  
  //Initialize serial
  Serial.begin(9600);
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 500 ms for connection:
    delay(500);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();

  //Pinout configuration
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);

}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void ultrasonic_lecture(){

  digitalWrite(trig , HIGH);
  delay(1);
  digitalWrite(trig , LOW);
  delay(1);
  duration = pulseIn(echo , HIGH);
  distance = duration / 58.2;
  
}

void loop() {
  
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an HTTP request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html lang = \"en\">");
          client.println("<head>");
          client.println("<title>Level Sensor Web App</title>");
          client.println("<meta charset='UTF-8'>");
          client.println("<meta http-equiv='X-UA-Compatible' content='IE=edge'>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
          client.println("</head>");
          ultrasonic_lecture();
          client.println("<body style = \"background-color: white;\">");
          client.println("<h1 style = \"text-align: center; color: rgb(69, 80, 230); font-family: 'Trebuchet MS'\">Level Sensor Web display</h1>");
          client.println("<div style = \"background-color: rgb(69, 80, 230); width: 200px; margin: auto; text-align: center; border: rgb(69, 80, 230) 5px solid; border-radius: 5px; box-shadow: rgba(0, 0, 0, 0.19) 0px 10px 20px, rgba(0, 0, 0, 0.23) 0px 6px 6px;'\">");
          client.println("<p style = \"text-align: center; color: white; font-family: 'Trebuchet MS'; font-size: 20px;\">Distancia</p>");
          client.print("<p style = \"text-align: center; color: white; font-family: 'Arial Rounded MT Bold'; font-size: 50px\">");
          client.print(distance);
          client.println("</p>");
          client.println("<p style = \"text-align: center; color: white; font-family: 'Trebuchet MS'; font-size: 20px;\">cm</p>");
          client.println("</div>");
          client.println("<br />");
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }

}
