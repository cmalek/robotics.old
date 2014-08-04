#include <NewPing.h>
#include <Servo.h>
#include <Bounce2.h>
#include <Encoders.h>
#include <RolleyMin.h>

Servo servo;
NewPing sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_MAX_DISTANCE); 
RolleyMin robot = RolleyMin();


void setup() {
  robot.servo = &servo;
  robot.sonar = &sonar;
  robot.setup();
  Serial.begin(9600);
}

void loop() {  
  robot.sensor_test();
}
  
