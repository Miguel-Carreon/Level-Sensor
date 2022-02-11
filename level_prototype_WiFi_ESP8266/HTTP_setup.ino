// Función para hacer la configuración HTTP //
void http_setup(){

  Serial.println("\nESP8266 Web Server");
  WiFi.mode(WIFI_STA);
  WiFi.begin(NETWORK_SSID, NETWORK_PASS);

  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }
  
  Serial.println("\nConnected\nWiFi ready");
  Serial.print("ESP82666 IP address: ");
  Serial.println(WiFi.localIP());

  /*server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP Server started");*/
  int power = WiFi.RSSI();
  Serial.printf("Signal dB %d\n", power);
  
}

// Función para manejar las respuestas entrantes //
/*void handleRoot(){
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/html", html_file);
  digitalWrite(LED_BUILTIN, LOW);
}*/
