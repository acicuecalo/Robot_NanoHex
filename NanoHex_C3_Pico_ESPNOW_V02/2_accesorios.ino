const int pinBateria = 3;
int16_t adcBateria;
int16_t mvBateria;
int16_t porcentajeBateria;

void iniciarAccesorios() {
  Serial.begin(115200);
}

/*
void leerVoltajeBateria() {
  adcBateria = analogRead(pinBateria);
  mvBateria = map(adcBateria, 0, 3030, 0, 4200);  // 4.20 v son 3030 en el ADC
  mvBateria = constrain(mvBateria, 0, 4200);
  porcentajeBateria = map(mvBateria, 3000, 4200, 0, 100);
  porcentajeBateria = constrain(porcentajeBateria, 0, 100);
}
*/

void timerAccesorios() {
  const int intervaloDeActualizacion = 1000;  // milisegundos entre cada ciclo de temporización
  static unsigned long ultimaActualizacion;
  if ((millis() - ultimaActualizacion) > intervaloDeActualizacion) {
    ultimaActualizacion = millis();
    //leerVoltajeBateria();
  }
}
