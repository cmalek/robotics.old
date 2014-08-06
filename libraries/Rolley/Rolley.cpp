#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Rolley.h>

Rolley::Rolley() : 
    _servo_range_start(0),
    _servo_range_end(180),
    servo_pos(90),
    servo_increment(1),
    _sonar_obstacle_distance(SONAR_OBSTACLE_DISTANCE)
{}

void Rolley::setup() 
{
    // Setup motors
    this->_motors.setup(LEFT_MOTOR_DIRECTION_PIN,
                        LEFT_MOTOR_SPEED_PIN,
                        RIGHT_MOTOR_DIRECTION_PIN,
                        RIGHT_MOTOR_SPEED_PIN);

    // Setup servo
    this->servo->attach(SERVO_PIN);
    this->servo_set_position(this->servo_pos);
    delay(100);

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
    //
    // Setup wheel encoders
    this->_encoders = Encoders();
    this->_encoders.setup();
 
    // Setup cliff sensors
    pinMode(CLIFF_LEFT_PIN, INPUT);
    pinMode(CLIFF_RIGHT_PIN, INPUT);
}

//
// MOTORS
//

void Rolley::forward(uint8_t speed)
{
    /* 
     * Go forward.
     *
     * param speed: 0-250
     */
    this->_motors.forward(speed);
}

void Rolley::backward(uint8_t speed)
{
    /* 
     * Go backward
     *
     * param speed: 0-250
     */
    this->_motors.backward(speed);
}

void Rolley::spin(uint8_t direction, uint8_t speed)
{
    /* 
     * Spin in place. 
     *
     * param direction: LEFT or RIGHT
     * param speed: 0-250
     */
    this->_motors.spin(direction, speed);
}

void Rolley::stop()
{
    this->_motors.stop();
}

//
// SONAR
//

float Rolley::sonar_get_distance()
{
  return(this->sonar->ping_median() / US_ROUNDTRIP_CM);
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

int Rolley::servo_get_position()
{
    return (this->servo_pos);
}

void Rolley::servo_set_position(int pos)
{
    this->servo->write(pos);
}

void Rolley::servo_set_scan_range(int start = 0, int end = 180)
{
    this->_servo_range_start = start;
    this->_servo_range_end = end;
}

void Rolley::servo_scan()
{
    if (this->servo_pos <= this->_servo_range_start) {
        this->servo_set_position(this->_servo_range_start);
        this->servo_pos = this->_servo_range_start;
        delay(50);
    }

    if (this->servo_pos >= this->_servo_range_end) {
        this->servo_set_position(this->_servo_range_end);
        this->servo_pos = this->_servo_range_end;
        delay(50);
    }

    if (this->servo_pos + this->servo_increment > this->_servo_range_end) {
        this->servo_increment = -1;
    }
    if (this->servo_pos + this->servo_increment < this->_servo_range_start) {
        this->servo_increment = 1;
    }
    this->servo_pos += this->servo_increment;
    this->servo_set_position(this->servo_pos);
    delay(10);
}

//
// CLIFF
//

boolean Rolley::is_cliff()
{
    return(this->is_left_cliff() || this->is_front_cliff() || this->is_right_cliff());
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
    return(digitalRead(CLIFF_RIGHT_PIN) && !digitalRead(CLIFF_LEFT_PIN));
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
// ENCODERS
// 

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

// 
// TEST
//

void Rolley::motor_test()
{
    this->_motors.test();
}

void Rolley::sensor_test()
{
    this->bump_update();
    this->servo_scan();
    Serial.print("POS:");
    Serial.print(this->servo_pos);
    Serial.print("\tI:");
    Serial.print(this->servo_increment);
    Serial.print("\tD:");
    Serial.print(this->sonar_get_distance());
    Serial.print("\t\t||\t");
    Serial.print(this->is_left_bump() ? "BL" : "0");
    Serial.print("\t");
    Serial.print(this->is_front_bump() ? "BF" : "0");
    Serial.print("\t");
    Serial.print(this->is_right_bump() ? "BR" : "0");
    Serial.print("\t||\t");
    Serial.print(this->is_left_cliff() ? "CL" : "0");
    Serial.print("\t");
    Serial.print(this->is_front_cliff() ? "CF" : "0");
    Serial.print("\t");
    Serial.print(this->is_right_cliff() ? "CR" : "0");
    Serial.print("\t||\tEL:");
    Serial.print(this->encoders_left_distance());
    Serial.print("\t||\tER:");
    Serial.println(this->encoders_right_distance());
}
