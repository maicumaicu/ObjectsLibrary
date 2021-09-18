#ifndef OBJECTS_H
#define OBJECTS_H
#include <Arduino.h>
class Led {
    private:
        int pin;
        int estado;
        void setup();
    public:
        Led (int aPin);
        int getPin();
        int getEstado();
        void prenderLed();
        void apagarLed();
        void pwmLed(int pwm);
};

class Button{
    private:
        int pin;
        int estado;
        int flag;
        void setup();
    public:
        Button(int aPin);
        int getPin();
        int getEstado();
        int getFlag();
        void btnMachine();
};
#endif