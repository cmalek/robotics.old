#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Rolley.h>

Rolley::Rolley() : 
    _sonar_obstacle_distance(SONAR_OBSTACLE_DISTANCE),
    _servo_range_start(0),
    _servo_range_end(180)
{
    setup();
}

Rolley::Rolley(uint8_t _obstacle_distance) : 
    _sonar_obstacle_distance(_obstacle_distance),
    _servo_range_start(0),
    _servo_range_end(180)
{
    setup();
}

void Rolley::setup() 
{
    // Setup motors
    pinMode(LEFT_MOTOR_DIRECTION_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_DIRECTION_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_SPEED_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_SPEED_PIN, OUTPUT);
    digitalWrite(LEFT_MOTOR_SPEED_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_SPEED_PIN, LOW);
 
    // Setup sonar
    this->_sonar = &NewPing(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_MAX_DISTANCE);

    // Setup servo
    //this->_servo.attach(SERVO_PIN);
    //this->_servo.write(90); // point straight ahead to begin with

    // Setup bump sensors
    pinMode(BUMP_LEFT_PIN, INPUT);
    digitalWrite(BUMP_LEFT_PIN, HIGH); // Turn on pullup resistor
    pinMode(BUMP_MIDDLE_PIN, INPUT);
    digitalWrite(BUMP_MIDDLE_PIN, HIGH); // Turn on pullup resistor
    pinMode(BUMP_RIGHT_PIN, INPUT);
    digitalWrite(BUMP_RIGHT_PIN, HIGH); // Turn on pullup resistor

    this->_left_bump.attach(BUMP_LEFT_PIN); 
    this->_left_bump.interval(5);
    this->_middle_bump.attach(BUMP_MIDDLE_PIN); 
    this->_middle_bump.interval(5);
    this->_right_bump.attach(BUMP_RIGHT_PIN); 
    this->_right_bump.interval(5);

    // Setup wheel encoders
    this->_encoders = Encoders();
    this->_encoders.setup();

    // Setup cliff sensors
    pinMode(CLIFF_LEFT_PIN, INPUT);
    pinMode(CLIFF_RIGHT_PIN, INPUT);
}

void Rolley::forward(uint8_t speed)
{
    /* 
     * Go forward.
     *
     * param speed: 0-250
     */
    analogWrite (LEFT_MOTOR_SPEED_PIN, speed);
    digitalWrite(LEFT_MOTOR_DIRECTION_PIN, MOTOR_FORWARD);    
    analogWrite (RIGHT_MOTOR_SPEED_PIN, speed);    
    digitalWrite(RIGHT_MOTOR_DIRECTION_PIN, MOTOR_FORWARD);
}

void Rolley::backward(uint8_t speed)
{
    /* 
     * Go backward
     *
     * param speed: 0-250
     */
    analogWrite (LEFT_MOTOR_SPEED_PIN, speed);
    digitalWrite(LEFT_MOTOR_DIRECTION_PIN, MOTOR_REVERSE);    
    analogWrite (RIGHT_MOTOR_SPEED_PIN, speed);    
    digitalWrite(RIGHT_MOTOR_DIRECTION_PIN, MOTOR_REVERSE);
}

void Rolley::spin(uint8_t direction, uint8_t speed)
{
    /* 
     * Spin in place. 
     *
     * param direction: LEFT or RIGHT
     * param speed: 0-250
     */
    analogWrite (LEFT_MOTOR_SPEED_PIN, speed);
    analogWrite (RIGHT_MOTOR_SPEED_PIN, speed);    
    if (direction == LEFT) {
        digitalWrite(LEFT_MOTOR_DIRECTION_PIN, MOTOR_REVERSE);    
        digitalWrite(RIGHT_MOTOR_DIRECTION_PIN, MOTOR_FORWARD);
    } else {
        digitalWrite(LEFT_MOTOR_DIRECTION_PIN, MOTOR_FORWARD);    
        digitalWrite(RIGHT_MOTOR_DIRECTION_PIN, MOTOR_REVERSE);
    }
}

void Rolley::stop()
{
    analogWrite (LEFT_MOTOR_SPEED_PIN, 0);
    digitalWrite(LEFT_MOTOR_DIRECTION_PIN, MOTOR_REVERSE);    
    analogWrite (RIGHT_MOTOR_SPEED_PIN, 0);    
    digitalWrite(RIGHT_MOTOR_DIRECTION_PIN, MOTOR_REVERSE);
}

//
// CLIFF
//

boolean Rolley::is_cliff()
{
    return(digitalRead(CLIFF_LEFT_PIN) || digitalRead(CLIFF_RIGHT_PIN));
}

boolean Rolley::is_front_cliff()
{
    return(digitalRead(CLIFF_LEFT_PIN) && digitalRead(CLIFF_RIGHT_PIN));
}

boolean Rolley::is_left_cliff()
{
    return(digitalRead(CLIFF_LEFT_PIN) && !digitalRead(CLIFF_RIGHT_PIN));
}

boolean Rolley::is_right_cliff()
{
    return(digitalRead(CLIFF_LEFT_PIN) && !digitalRead(CLIFF_RIGHT_PIN));
}

//
// BUMP
//

boolean Rolley::bump_update()
{
    this->_left_bump.update();
    this->_right_bump.update();
    this->_middle_bump.update();
}

boolean Rolley::is_bump()
{
    this->bump_update();
    int left = this->_left_bump.read();
    int right = this->_right_bump.read();
    int middle = this->_middle_bump.read();
    return((left == LOW) || (middle == LOW) || (right == LOW));
}

boolean Rolley::is_front_bump()
{
    this->bump_update();
    int middle = this->_middle_bump.read();
    return(middle == LOW);
}

boolean Rolley::is_left_bump()
{
    this->bump_update();
    int left = this->_left_bump.read();
    int right = this->_right_bump.read();
    int middle = this->_middle_bump.read();
    return((left == LOW) && (middle != LOW) && (right != LOW));
}

boolean Rolley::is_right_bump()
{
    this->bump_update();
    int left = this->_left_bump.read();
    int right = this->_right_bump.read();
    int middle = this->_middle_bump.read();
    return((right == LOW) && (middle != LOW) && (left != LOW));
}

//
// SONAR
//

float Rolley::sonar_get_distance()
{
  return(this->_sonar->ping_median() / US_ROUNDTRIP_CM);
}

boolean Rolley::is_sonar_wall()
{
  float cm = this->sonar_get_distance();
  if ((cm > 0) && (cm < this->_sonar_obstacle_distance)) {
    return true;
  }
  return false;
}

//
// SERVO
//

uint8_t Rolley::servo_get_position()
{
    return (this->_servo.read());
}

void Rolley::servo_set_position(uint8_t pos)
{
    this->_servo.write(pos);
}

void Rolley::servo_set_scan_range(uint8_t start = 0, uint8_t end = 180)
{
    this->_servo_range_start = start;
    this->_servo_range_end = end;
}

void Rolley::servo_scan()
{
    static uint8_t current_pos = this->servo_get_position();
    static uint8_t increment = 1;

    if (current_pos < this->_servo_range_start) {
        this->servo_set_position(this->_servo_range_start);
        current_pos = this->_servo_range_start;
        delay(15);
    }

    if (current_pos > this->_servo_range_end) {
        this->servo_set_position(this->_servo_range_end);
        current_pos = this->_servo_range_end;
        delay(15);
    }

    if (current_pos + increment > this->_servo_range_start) {
        increment = -1;
    }
    if (current_pos + increment < this->_servo_range_end) {
        increment = 1;
    }
    current_pos += increment;
    this->servo_set_position(current_pos);
    delay(15);
}

float Rolley::encoders_left_distance()
{
    return this->_encoders.left();
}

float Rolley::encoders_reset_left_distance()
{
    this->_encoders.reset_left();
}

float Rolley::encoders_right_distance()
{
    return this->_encoders.right();
}

float Rolley::encoders_reset_right_distance()
{
    this->_encoders.reset_right();
}

