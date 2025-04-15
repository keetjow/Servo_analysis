#include <iostream>
#include <pigpio.h>
#include "src/Encoder.hpp"
#include "src/Servo.hpp"
#include <unistd.h>
#include <chrono>
#include <cmath>
#include <thread>

/*
    SERVO (+/- 45deg)
        :MIN 1000 (-45deg)
        :MIDDLE 1500 (0deg)
        :MAX 2000 (+45deg)

    BUILD
        g++ -o main_c main.cpp src/*.cpp -lpigpio

    RUN
        sudo ./main_c
*/

void printVal(int val_)
{
    //float val = 360.0f*(val_/1600.0f);
}

float f = 1.0f;
float A = 22.5f;

int main()
{
    if(gpioInitialise() < 0) return 1;
    Encoder myEncoder = Encoder(17, 27, printVal);
    Servo myServo = Servo(22, true);

    sleep(1);

    auto start = std::chrono::steady_clock::now();

    while(true)
    {   
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - start;
        double t = elapsed.count();

        double angle = A*sin(2*M_PI*f*t);
        myServo.setAngle(angle);

        std::cout<<myServo.angle<<" "<<angle<<std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    gpioTerminate();
    return 0;
}