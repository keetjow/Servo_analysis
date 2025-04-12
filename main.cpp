#include <iostream>
#include <pigpio.h>
#include "enc.hpp"
#include <unistd.h>
#include <chrono>
#include <cmath>
#include <thread>

/*
    BUILD
        g++ -o main_c main.cpp enc.hpp enc.cpp -lpigpio

    RUN
        sudo ./main_c
*/


void printVal(int val_)
{
    float val = 360.0f*(val_/1600.0f);
}

float f = 10.0f;
float A = 22.5f;

int main()
{
    if(gpioInitialise() < 0) return 1;
    gpioSetMode(22, PI_OUTPUT);
    Enc myEnc = Enc(17, 27, printVal);

    gpioServo(22, 1500);
    sleep(1);

    auto start = std::chrono::steady_clock::now();

    while(true)
    {        
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - start;
        double t = elapsed.count();

        double angle = A*sin(2*M_PI*f*t);
        int PWM = 1500 + (angle*(500/45));
        gpioServo(22, PWM);
        std::cout<<angle<<std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    gpioTerminate();
    return 0;
}