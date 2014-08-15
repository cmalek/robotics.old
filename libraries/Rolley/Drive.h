#ifndef Rolley_Drive_h
#define Rolley_Drive_h

/* =======================
 * Other definitions
 * ======================= */

#define MOTOR_FORWARD               HIGH
#define MOTOR_REVERSE               LOW

namespace rolley
{
    enum motor_directions_t { LEFT_TURN, RIGHT_TURN };

    class Drive
    {
        public:
            Drive();
            void setup(uint8_t, uint8_t, uint8_t, uint8_t);

            void forward(uint8_t speed);
            void backward(uint8_t speed);
            void spin(rolley::motor_directions_t direction, uint8_t speed);
            void stop();

            void test();
        private:
            uint8_t convert_speed(uint8_t);
            uint8_t _left_direction_pin;
            uint8_t _left_speed_pin;
            uint8_t _right_direction_pin;
            uint8_t _right_speed_pin;
    };
}
#endif
