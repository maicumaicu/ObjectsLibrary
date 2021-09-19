#include "Objects.h"
#define APAGADO 0
#define PRENDIDO 1

#define ESPERA 0
#define CONFIRMACION 1
#define LIBERACION 2


Led::Led(int aPin){
    this->pin = aPin;
    this->estado = 0;
    setup();
}
void Led::setup(){
    pinMode(pin,OUTPUT);
    digitalWrite(pin,LOW);
}

int Led::getPin(){
    return pin;
}

int Led::getEstado(){
    return estado;
}

void Led::prenderLed(){ 
    digitalWrite(pin,HIGH);
    estado = 1;
}

void Led::apagarLed(){
    digitalWrite(pin,LOW);
    estado = 0;
}

void Led::pwmLed(int pwm){ 
    analogWrite(pin, pwm);
}


//------------------------------------------------------------------------------------------

Button::Button(int aPin){
    this->pin = aPin;
    this->estado = 0;
    this->flag = 0;
}

int Button::getPin(){
    return pin;
}

int Button::getEstado(){
    return estado;
}

int Button::getFlag(){
    return flag;
}

void Button::btnMachine(){
    switch (estado) {
    case ESPERA:
      flag = 0;
      lecturaBtn = digitalRead(pin);
      if (lecturaBtn == 0) {
        ticks = 0;
        estado = CONFIRMACION;
      }
      break;

    case CONFIRMACION:
      lecturaBtn = digitalRead(pin);
      if ( lecturaBtn == 0 && ticks >= TICKS_BTN) {
        estado = LIBERACION;
      }

      if ( lecturaBtn == 1 && ticks < TICKS_BTN) {
        estado = ESPERA;
      }
      break;

    case LIBERACION:
      lecturaBtn = digitalRead(pin);
      if ( lecturaBtn == 1) {
        flag = 1;
        estado = ESPERA;
        Serial.println(flag);
      }
      break;
  }
}

//--------------------------------------------------------------------------------

Ultrasonic::Ultrasonic(int aTrig,int aEcho){
    echo = aEcho;
    trig = aTrig;
    distancia = 0;
}

int Ultrasonic::getEcho(){
  return echo;
}

int Ultrasonic::getTrig(){
  return trig;
}

int Ultrasonic::getDistancia(){
  return distancia;
}

void Ultrasonic::medicion(){
  int t;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);
  t = pulseIn(echo, HIGH); //obtenemos el ancho del pulso
  distancia = (t/2)/29;   
  
  Serial.print("Distancia 1: ");
  Serial.print(distancia);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println(); 
}