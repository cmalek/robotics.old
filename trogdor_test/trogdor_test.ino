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
  robot.stop();
}

void loop() {
  robot.bump_update();
  
  if (state == START) {
    if (robot.is_bump()) {
      Serial.println("START BUMP!");
      // warm up encoders
      robot.forward(250);
      delay(500);
      robot.stop();
      robot.encoders_reset_left_distance();
      robot.encoders_reset_right_distance();
      state = FORWARD;
    }
  } else if (state == FORWARD) {
    robot.forward(250);
    if (robot.encoders_left_distance() > 0.30) {
      state = STOP;
    }
  } else if (state == STOP) {
    robot.stop();
    robot.encoders_reset_left_distance();
    robot.encoders_reset_right_distance();
    state = DONE;
    delay(1000);
  } else {
    if (robot.is_bump()) {    
      Serial.println("DONE BUMP!");
      state = FORWARD;
    }
  }
}
