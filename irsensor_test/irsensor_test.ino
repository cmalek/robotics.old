const int LED = 13;
const int IR_SENSOR = 2;

int val = 0;
int old_val = 0;
int state = 0;

void setup() {
  pinMode(IR_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  val = digitalRead(IR_SENSOR);
  
  if (val != old_val) {
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
