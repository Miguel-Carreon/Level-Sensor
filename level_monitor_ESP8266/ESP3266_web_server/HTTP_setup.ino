// Función para hacer la configuración HTTP //
void http_setup(){

  // Iniciar la conexión WiFi:
  Serial.println("\nESP8266 Web Server");
  WiFi.mode(WIFI_STA); // Utilizar el µC como estación WiFi
  WiFi.begin(NETWORK_SSID, NETWORK_PASS); // Ingresar credenciales

  Serial.print("Connecting");

  // Esperar la conexión:
  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }

  // Conexión lista:
  Serial.println("\nConnected\nWiFi ready");
  Serial.print("ESP82666 IP address: ");
  Serial.println(WiFi.localIP());

  // Imprimir en el monitor serial la intensidad de la señal:
  int power = WiFi.RSSI();
  Serial.printf("Signal dB %d\n", power);

  // Configuracion del servidor:
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP Server started");
  
}

// Manejar la raíz
void handleRoot(){

  // Enviar codigo HTTP, tipo de dato y dato:
  String html_file = "<style> body { background-color: white; } h1 { text-align: center; color: rgb(69, 80, 230); font-family: \"Trebuchet MS\"; } div { background-color: rgb(69, 80, 230); width: 200px; margin: auto; text-align: center; border: rgb(69, 80, 230) 5px solid; border-radius: 5px; box-shadow: rgba(0, 0, 0, 0.19) 0px 10px 20px, rgba(0, 0, 0, 0.23) 0px 6px 6px; }</style><!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <meta http-equiv='refresh' content='3'> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Level Monitor</title></head><body> <h1>Level Sensor Web display</h1> <div> <p style = \"text-align: center; color: white; font-family: 'Trebuchet MS'; font-size: 20px;\"> Distancia </p> <p style = \"text-align: center; color: white; font-family: 'Arial Rounded MT Bold'; font-size: 50px;\">" + String(distance) + "</p> <p style = \"text-align: center; color: white; font-family: 'Trebuchet MS'; font-size: 20px;\"> cm </p> </div></body></html>";
  server.send(200, "text/html", html_file); // Protocolo HTTP
  
}
