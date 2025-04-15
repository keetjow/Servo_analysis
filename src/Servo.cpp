#include "Servo.hpp"
#include <pigpio.h>
#include <iostream>

void Servo::setPWM(int pulse_width_)
{
    pulse_width =pulse_width_;
    angle = ((pulse_width - 1500.0f)/500.0f)*45.0f;
    gpioServo(servo_pin, pulse_width);
}

void Servo::setAngle(double angle_)
{
    angle = angle_;
    pulse_width = 1500 + (angle*(500/45));
    gpioServo(servo_pin, pulse_width);
}

void Servo::setPos(Position pos_)
{
    switch(pos_)
    {
        case Position::LEFT_MOST:
            pulse_width = Position::LEFT_MOST;
            break;
        case Position::DEFAULT:
            pulse_width = Position::DEFAULT;
            break;
        case Position::RIGHT_MOST:
            pulse_width = Position::RIGHT_MOST;
            break;
    }
    gpioServo(servo_pin, pulse_width);
}

Servo::Servo(const int pin_PWM, bool reset_)
{
    servo_pin = pin_PWM;
    gpioSetMode(servo_pin, PI_OUTPUT);

    pulse_width = Position::DEFAULT;
    angle = 0;
    gpioServo(servo_pin, pulse_width);
}

Servo::Servo(const int pin_PWM)
{   
    servo_pin = pin_PWM;
    gpioSetMode(servo_pin, PI_OUTPUT);

    pulse_width = 0;
    angle = 0;
    gpioServo(servo_pin, pulse_width);
    std::cout<<"Default position not reached, angle feedback set to 0"<<std::endl;
}