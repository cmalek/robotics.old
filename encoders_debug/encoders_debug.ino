static volatile int counts1 = 0;
static volatile int counts2 = 0;
static volatile int last1 = 0;
static volatile int last2 = 0;
static volatile int pinc = 0;
static int tmp = 0;

inline int getCountsAndResetM1()
{
  noInterrupts();
  const int tmp = counts1;
  counts1 = 0;
  interrupts();
  return tmp;
}

inline int getCountsAndResetM2()
{
  noInterrupts();
  const int tmp = counts2;
  counts2 = 0;
  interrupts();
  return tmp;
}

inline float convert(int count)
{
  static const float ppr = 20.0f;
  static const float pi = 3.1416f;
  static const float diameter = 0.0635f;
  static const float circumference = pi * diameter;
  return circumference * count / ppr;
}

void setup() {
  // put your setup code here, to run once:
  // Make sure the pin is set for input
  //
  
  Serial.begin(9600);

  pinMode(14, INPUT);
  pinMode(15, INPUT);

  // Enable the pull-up resistor
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);

  // Prevent interrupts while initializing
  noInterrupts();

  // Pin 14 for left wheel, Pin 15 for the right wheel
  PCICR |= 1 << PCIE1;
  PCMSK1 |= (1 << PCINT12) | (1 << PCINT13);
  
  // Clear the interrupt flags in case they were set before for any reason.
  // On the AVR, interrupt flags are cleared by writing a logical 1
  // to them.
 
  // PCIFR |= (1 << PCIF0) | (1 << PCIF1) | (1 << PCIF2);

  // re-enable interrupts
  //
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(pinc);
  Serial.print("   ");
  Serial.print(counts1);
  Serial.print("   ");
  Serial.print(counts2);
  Serial.print('\n');
  delay(1000);
}

// Interrupt based on wheel encoder
//
ISR(PCINT1_vect)
{

  // Get the value at the pins
  //
  pinc = PINC;
  const int m1 = PINC & (1 << 4);
  const int m2 = PINC & (1 << 5);

  // Determine which pin to update
  //
  if (m1 ^ last1)
  {
    counts1 += 1;
  }
  if (m2 ^ last2)
  {
    counts2 += 1;
  }
  
  last1 = m1;
  last2 = m2;
}

