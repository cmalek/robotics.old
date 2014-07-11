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
#define SERVO              9
#define SONAR_ECHO_PIN     10

// Bump Sensors
#define BUMP_LEFT          11
#define BUMP_MIDDLE        12
#define BUMP_RIGHT         13



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
