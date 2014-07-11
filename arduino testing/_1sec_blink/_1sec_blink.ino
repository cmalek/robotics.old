const int LED = 13;
const int SENSOR = 2;

int val = 0;
int old_val = 0;
int state = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);

}

void loop() {
  val = digitalRead(SENSOR);
  
  if ((val == HIGH) && (old_val == LOW)) {
    state = 1 - state;
    delay(10);
  }

  old_val = val;
  
  if (state == 1) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
