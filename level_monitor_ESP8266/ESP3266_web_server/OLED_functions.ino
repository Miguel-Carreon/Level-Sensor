Adafruit_SSD1306 oled(width, height, &Wire, OLED_RESET);

// Función para iniciar el OLED //
void oled_setup(){

  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
}

// Funcion para la configuración de impresión en el OLED //
void oled_display(String message, int value, String unit){

  int power = WiFi.RSSI();
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.setCursor(0, 0);
  oled.print(message);
  oled.print(value);
  oled.print(unit);
  oled.print("\n\nRSSI: ");
  oled.print(power);
  oled.print(" dB");
  oled.print("\nIP: ");
  oled.print(WiFi.localIP());
  oled.display();
  
}
