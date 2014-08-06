#include <NewPing.h>
#include <Servo.h>
#include <Bounce2.h>
#include <Encoders.h>
#include <Rolley.h>
#include <Sonar.h>

Servo servo;
NewPing sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_MAX_DISTANCE); 
Rolley robot = Rolley();


void setup() {
  robot.setup(&servo, &sonar);
  Serial.begin(115200);
}

void loop() {  
  robot.sensor_test();
}
  
