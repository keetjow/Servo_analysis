#ifndef SERVO_H
#define SERVO_H

class Servo
{
    public:
        enum Position
        {
            LEFT_MOST = 1000,
            DEFAULT = 1500,
            RIGHT_MOST = 2000
        };
        Servo(const int pin_PWM);
        Servo(const int pin_PWM, bool reset_);
        void setPWM(int pulse_width_);
        void setAngle(double angle_);
        void setPos(Position pos_);

        int pulse_width;
        double angle;
        int servo_pin;

};

#endif