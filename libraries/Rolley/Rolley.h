#ifndef Rolley_h
#define Rolley_h

#include <RolleyCommon.h>
#include <Encoders.h>
#include <Drive.h>
#include <Bump.h>
#include <RolleyServo.h>
#include <Sonar.h>
#include <Cliff.h>


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

#define SONAR_MAX_DISTANCE          200
#define WHEEL_BASE                  15 

namespace rolley
{
    class Rolley
    {
        public:
            Rolley();
            void setup(Servo *, NewPing *);

            void forward(uint8_t speed);
            void forward_meters(uint8_t speed, float meters);
            void backward(uint8_t speed);
            void backward_meters(uint8_t speed, float meters);
            void spin(rolley::motor_directions_t direction, uint8_t speed);
            void stop();

            float sonar_get_distance();
            boolean is_sonar_wall();

            int servo_get_position();
            void servo_set_position(int);
            void servo_set_scan_range(int, int);
            void servo_scan();

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
            void encoders_reset_left_distance();
            float encoders_right_distance();
            void encoders_reset_right_distance();
            float encoders_distance();
            void encoders_reset();

            void motor_test();
            void sensor_test();
        private:
            void move_meters(uint8_t speed, float meters, int direction);
            rolley::Drive _motors;
            rolley::Bump _bump;
            rolley::RolleyServo _servo;
            rolley::Sonar _sonar;
            rolley::Encoders _encoders;
            rolley::Cliff _cliff;
    };
}
#endif
