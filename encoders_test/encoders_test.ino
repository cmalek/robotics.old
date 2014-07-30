#include <Encoders.h>
#include <NewPing.h>
#include <Bounce2.h>
#include <Servo.h>
#include <Rolley.h>

#define START    0
#define FORWARD  1
#define STOP     2
#define REPORT   3
#define DONE     4

static int state = FORWARD;

Rolley robot = Rolley();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (state == FORWARD) {
    delay(1200); 
    robot.forward(250);
    delay(1200); 
    state = STOP;
  } else if (state == STOP) {
    robot.stop();
    state = REPORT;
  } else if (state == REPORT) {
    Serial.print(robot.encoders_left_distance());
    Serial.print("    ");
    Serial.print(robot.encoders_right_distance());
    Serial.print("\n");
    state = DONE;
  } else {
    delay(5000);
    state = FORWARD;
  }
}
