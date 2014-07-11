#include <Servo.h>
#include <NewPing.h>
 
#define TRIGGER_PIN  8
#define ECHO_PIN     10
#define MAX_DISTANCE 200


Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(115200);
} 

void ping()
{
  int uS = sonar.ping();
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
}
 
 
void loop() 
{ 
  for(pos = 45; pos < 135; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    ping();
  } 
  for(pos = 135; pos>=45; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    ping();
  } 
}

