#include <NewPing.h>

/*
 # Editor : Phoebe
 # Date   : 2012.11.6
 # Ver    : 0.1
 # Product: Cherokey 4WD Mobile Platform
 # SKU    : RBO0102
   
 # Description:     
 # Drive 2 motors with this Cherokey 4WD Mobile Platform  
 # Connect the D4,D5,D6,D7 to UNO digital 4,5,6,7
 
*/
  
#define E1 5     //M1 Speed Control
#define E2 6     //M2 Speed Control
#define M1 4     //M1 Direction Control
#define M2 7     //M1 Direction Control
 
#define TRIGGER_PIN  8
#define ECHO_PIN     9
#define MAX_DISTANCE 500

#define FORWARD 1
#define BACKUP_TURN 2
#define TURN 3

#define WALL 15

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int state = FORWARD;

void stop(void)                    //Stop
{
  digitalWrite(E1,0); 
  digitalWrite(M1,LOW);    
  digitalWrite(E2,0);   
  digitalWrite(M2,LOW);    
}   
void advance(char a,char b)          //Move forward
{
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}
void back_off (char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);   
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}
void turn_L (char a,char b)             //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}
void turn_R (char a,char b)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}

void bank_L (char a)             //Turn Right
{
  analogWrite (E1,a/24);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,a);    
  digitalWrite(M2,HIGH);
}

void bank_R (char a)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,a/24);    
  digitalWrite(M2,HIGH);
}

boolean is_wall(void) {
  int uS = sonar.ping_median();
  float cm = uS / US_ROUNDTRIP_CM;
  if ((cm > 0) && (cm < WALL)) {
    return true;
  }
  return false;
}
 
void setup(void) 
{ 
  int i;
  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT);  
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW); 
 
} 
  
void loop(void) 
{
  advance(150, 150);
  if (is_wall()) {
      back_off(150, 150);
      delay(1000);
      turn_L(255, 255);
      delay(500);
  }
}
