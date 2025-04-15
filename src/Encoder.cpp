#include "Encoder.hpp"
#include <pigpio.h>
#include <cmath>
#include "Servo.hpp"


void Encoder::pulseEx(int gpio, int level, uint32_t tick, void *userdata)
{
    Encoder *self = (Encoder*) userdata;
    self->pulse(gpio, level, tick);
}

void Encoder::pulse(int gpio, int level, uint32_t tick)
{
    if (gpio == myPin_A) level_A = level; else level_B = level;
    if(gpio != lastgpio)
    {
        lastgpio = gpio;
        static int last_encoded = 0;
        int encoded = (level_A << 1) | level_B;
        int sum = (last_encoded << 2) | encoded;
    
        if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
            n++;
        else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
            n--;
    
        last_encoded = encoded;
        myCallback(n);
    }


}

Encoder::Encoder(const int pin_A, const int pin_B, void (*callback)(int))
{
    myPin_A = pin_A;
    myPin_B = pin_B;

    myCallback = callback;

    n = 0;

    gpioSetMode(myPin_A, PI_INPUT);
    gpioSetMode(myPin_B, PI_INPUT);

    level_A = 0;
    level_B = 0;

    gpioSetAlertFuncEx(pin_A, pulseEx, this);
    gpioSetAlertFuncEx(pin_B, pulseEx, this);
}