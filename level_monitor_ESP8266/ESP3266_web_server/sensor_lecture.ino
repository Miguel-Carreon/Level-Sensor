// Función para realizar la medición //
void ultrasonic_lecture(){

  //Envía una señal ultrasónica luego evalua el tiepo que tarda en regresar:
  digitalWrite(trig , HIGH);
  delay(1);
  digitalWrite(trig , LOW);
  delay(1);
  duration = pulseIn(echo , HIGH);
  distance = duration / 58.2; // Conversión a distancia en cm
  
}
