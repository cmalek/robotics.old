#ifndef Rolley_h
#define Rolley_h

#include <Servo.h>
#include <NewPing.h>
#include <Bounce2.h>
#include <Encoders.h>

// Motors 
#define LEFT_MOTOR_DIRECTION_PIN    4
#define LEFT_MOTOR_SPEED_PIN        5
#define RIGHT_MOTOR_SPEED_PIN       6
#define RIGHT_MOTOR_DIRECTION_PIN   7

// Servo
#define SERVO_PIN                   9

// Sonar
#define SONAR_TRIGGER_PIN           8
#define SONAR_ECHO_PIN              10

// Bump Sensors
#define BUMP_LEFT_PIN               11
#define BUMP_RIGHT_PIN              12
#define BUMP_MIDDLE_PIN             13

// Wheel encoders
#define ENCODER_LEFT_PIN            14
#define ENCODER_RIGHT_PIN           15

// Cliff sensors
#define CLIFF_LEFT_PIN              16
#define CLIFF_RIGHT_PIN             17

/* =======================
 * Other definitions
 * ======================= */

#define LEFT                        1
#define RIGHT                       2

#define SONAR_MAX_DISTANCE          200
#define SONAR_OBSTACLE_DISTANCE     15

#define MOTOR_FORWARD               HIGH
#define MOTOR_REVERSE               LOW

class Rolley
{
    public:
        Rolley();
        void setup();

        void forward(uint8_t speed);
        void backward(uint8_t speed);
        void spin(uint8_t direction, uint8_t speed);
        void stop();

        NewPing *sonar;
        float sonar_get_distance();
        boolean is_sonar_wall();

        Servo *servo;
        int servo_get_position();
        void servo_set_position(int);
        void servo_set_scan_range(int, int);
        void servo_scan();
        int servo_pos;
        int servo_increment;

        boolean bump_update();
        boolean is_bump();
        boolean is_front_bump();
        boolean is_left_bump();
        boolean is_right_bump();

        boolean is_cliff();
        boolean is_front_cliff();
        boolean is_left_cliff();
        boolean is_right_cliff();

        float encoders_left_distance();
        float encoders_reset_left_distance();
        float encoders_right_distance();
        float encoders_reset_right_distance();

        void motor_test();
        void sensor_test();
    private:
        uint8_t _sonar_obstacle_distance;

        int _servo_range_start;
        int _servo_range_end;

        Bounce _left_bump;
        Bounce _middle_bump;
        Bounce _right_bump;

        Encoders _encoders;
};
#endif
