const int pinBateria = 3;
int16_t adcBateria;
int16_t mvBateria;
int16_t porcentajeBateria;

void iniciarAccesorios() {
  Serial.begin(115200);
}

