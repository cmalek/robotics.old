#include <Servo.h>
#include <NewPing.h>

/* ======================
 * PINS
 * ====================== */

// Motors 
#define M1_DIRECTION_PIN   4
#define M1_SPEED_PIN       5
#define M2_SPEED_PIN       6
#define M2_DIRECTION_PIN   7

// Sonar
#define SONAR_TRIGGER_PIN  8
#define SERVO_PIN          9
#define SONAR_ECHO_PIN     10

// Bump Sensors
#define BUMP_LEFT_PIN      11
#define BUMP_MIDDLE_PIN    12
#define BUMP_RIGHT_PIN     13

// Wheel encoders
#define ENCODER_LEFT_PIN   A0
#define ENCODER_RIGHT_PIN  A1

// Cliff sensors
#define CLIFF_LEFT_PIN     A3
#define CLIFF_RIGHT_PIN    A4

/* =======================
 * Other definitions
 * ======================= */

#define SONAR_MAX_DISTANCE      200
#define SONAR_OBSTACLE_DISTANCE 15

#define MOTOR_FORWARD           HIGH
#define MOTOR_REVERSE           LOW

/* =======================
 * Object creation
 * ======================= */

NewPing sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_MAX_DISTANCE);


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
