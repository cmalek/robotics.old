#include <Encoders.h>
#include <NewPing.h>
#include <Bounce2.h>
#include <Servo.h>
#include <Rolley.h>

Rolley robot = Rolley();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (robot.is_bump()) {
    Serial.println("BUMP!");
  } 
  if (robot.is_left_bump()) {
    Serial.println("LEFT BUMP!");
  } 
  if (robot.is_front_bump()) {
    Serial.println("MIDDLE BUMP!");
  } 
  if (robot.is_right_bump()) {
    Serial.println("RIGHT BUMP!");
  } 
}
