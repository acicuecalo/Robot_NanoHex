#include <pwmWrite.h>
Pwm pwm = Pwm();

const int retardo = 100;          //50
const int retardoBalanceo = 40;  // 20
const int pinServoCentral = 1;
const int pinServoIzquierdo = 2;
const int pinServoDerecho = 4;
const int gradosAvanceRetroceso = 30; // 20
const int gradosBalanceoLateral = 15; // 10
const int gradosServoCentrado = 90;
const int subtrimServoIzquierdo = 90;
const int subtrimServoCentral = 90;
const int subtrimServoDerecho = 90;


void iniciarBaseRobot() {
  centrarServos();
}

void moverBaseRobot(int ejeX, int ejeY)  // Los valores de control de -100 a 100
{
  const int deathBand = 6;

  // Entradas
  ejeX = constrain(ejeX, -100, 100);
  ejeY = constrain(ejeY, -100, 100);
  if (abs(ejeX) < deathBand && abs(ejeY) < deathBand) {
    ejeX = 0;
    ejeY = 0;
  }

  // Salidas
  if (ejeX > 50) {
    girarDerecha();
  }

  else if (ejeX < -50) {
    girarIzquierda();
  }

  else if (ejeY > 0) {
    secuenciaAvanzar();
  }

  else if (ejeY < 0) {
    secuenciaRetroceder();
  }

  else {
    centrarServos();
  }
}

void secuenciaAvanzar() {
  servoCentralDerecha();
  delay(retardoBalanceo);
  servoIzquierdoAvanza();
  servoDerechoRetrocede();
  delay(retardo);
  servoCentralIzquierda();
  delay(retardoBalanceo);
  servoIzquierdoRetrocede();
  servoDerechoAvanza();
  delay(retardo);
}

void secuenciaRetroceder() {
  servoCentralDerecha();
  delay(retardoBalanceo);
  servoIzquierdoRetrocede();
  servoDerechoAvanza();
  delay(retardo);
  servoCentralIzquierda();
  delay(retardoBalanceo);
  servoIzquierdoAvanza();
  servoDerechoRetrocede();
  delay(retardo);
}

void girarIzquierda() {
  servoCentralDerecha();
  delay(retardoBalanceo);
  servoIzquierdoRetrocede();
  servoDerechoRetrocede();
  delay(retardo);
  servoCentralIzquierda();
  delay(retardoBalanceo);
  servoIzquierdoAvanza();
  servoDerechoAvanza();
  delay(retardo);
}

void girarDerecha() {
  servoCentralDerecha();
  delay(retardoBalanceo);
  servoIzquierdoAvanza();
  servoDerechoAvanza();
  delay(retardo);
  servoCentralIzquierda();
  delay(retardoBalanceo);
  servoIzquierdoRetrocede();
  servoDerechoRetrocede();
  delay(retardo);
}

void servoCentralDerecha() {
  pwm.writeServo(pinServoCentral, subtrimServoCentral - gradosBalanceoLateral);
}

void servoCentralIzquierda() {
  pwm.writeServo(pinServoCentral, subtrimServoCentral + gradosBalanceoLateral);
}

void servoIzquierdoAvanza() {
  pwm.writeServo(pinServoIzquierdo, subtrimServoIzquierdo - gradosAvanceRetroceso);
}

void servoIzquierdoRetrocede() {
  pwm.writeServo(pinServoIzquierdo, subtrimServoIzquierdo + gradosAvanceRetroceso);
}

void servoDerechoAvanza() {
  pwm.writeServo(pinServoDerecho, subtrimServoDerecho + gradosAvanceRetroceso);
}

void servoDerechoRetrocede() {
  pwm.writeServo(pinServoDerecho, subtrimServoDerecho - gradosAvanceRetroceso);
}

void centrarServos() {
  pwm.writeServo(pinServoCentral, 90);
  pwm.writeServo(pinServoIzquierdo, 90);
  pwm.writeServo(pinServoDerecho, 90);
}

void timerBaseRobot() {
  const int intervaloDeActualizacion = 20;  // milisegundos entre cada ciclo de temporización
  static unsigned long ultimaActualizacion;
  if ((millis() - ultimaActualizacion) > intervaloDeActualizacion) {
    ultimaActualizacion = millis();
    moverBaseRobot(RX_Channel[0], RX_Channel[1]);
  }
}
