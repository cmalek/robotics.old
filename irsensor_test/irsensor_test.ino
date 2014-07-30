const int IR_SENSOR = 16;

int val = 0;
int old_val = 0;
int state = 0;

void setup() {
  pinMode(IR_SENSOR, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(IR_SENSOR);
  
  Serial.print(val);
  Serial.print("\n");
  delay(50);
}
