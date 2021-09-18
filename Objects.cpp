#include "Objects.h"
#define APAGADO 0
#define PRENDIDO 1

#define ESPERA 0
#define CONFIRMACION 1
#define LIBERACION 2

#define TICKS_BTN 25

int ticks,lecturaBtn;
#include <TimerOne.h>


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

void tick() {
  ticks++;
}

Button::Button(int aPin){
    this->pin = aPin;
    this->estado = 0;
    this->flag = 0;
    setup();
}

void Button::setup(){
    Timer1.initialize(1000);
    Timer1.attachInterrupt(tick);
    pinMode(pin,INPUT_PULLUP);
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

