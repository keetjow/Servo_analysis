#ifndef ENC_H
#define ENC_H

#include <iostream>

class Enc
{
    public:
        Enc(const int pin_A, const int pin_B, void (*callback)(int));
        int n;

    private:
        int myPin_A;
        int myPin_B;
        int level_A;
        int level_B;
        int lastgpio;
        void (*myCallback)(int);
        static void pulseEx(int gpio, int level, uint32_t tick, void *userdata);
        void pulse(int gpio, int level, uint32_t tick);

};

#endif