#include <iostream>
#include <pigpio.h>
#include "enc.hpp"

/*
    BUILD
        g++ -o main_c main.cpp enc.hpp enc.cpp -lpigpio

    RUN
        sudo ./main_c
*/


void printVal(int val_)
{
    float val = 360.0f*(val_/1600.0f);
    std::cout<<val<<std::endl;
}

int main()
{
    if(gpioInitialise() < 0) return 1;
    Enc myEnc = Enc(17, 27, printVal);

    while(true)
    {

    }

    gpioTerminate();
    return 0;
}