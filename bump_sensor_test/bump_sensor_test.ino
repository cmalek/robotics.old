#include <Bounce2.h>

#define RIGHT_BUTTON 13
#define MIDDLE_BUTTON 12
#define LEFT_BUTTON 11

Bounce right = Bounce(); 
Bounce middle = Bounce(); 
Bounce left = Bounce(); 

void setup() {
  
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(RIGHT_BUTTON, INPUT);
  digitalWrite(RIGHT_BUTTON, HIGH);
  pinMode(MIDDLE_BUTTON, INPUT);
  digitalWrite(MIDDLE_BUTTON, HIGH);
  pinMode(LEFT_BUTTON, INPUT);
  digitalWrite(LEFT_BUTTON, HIGH);
  
  right.attach(RIGHT_BUTTON);
  right.interval(5);

  middle.attach(MIDDLE_BUTTON);
  middle.interval(5);

  left.attach(LEFT_BUTTON);
  left.interval(5);
  
}

void loop() {
  right.update();
  middle.update();
  left.update();
  
  int right_value = right.read();
  int middle_value = middle.read();
  int left_value = left.read();
  Serial.print(left_value);
  Serial.print(middle_value);
  Serial.print(right_value);
  Serial.print("\n");
  delay(50);

}
