#include <Encoders.h>
#include <Arduino.h>

static volatile int left_count = 0;
static volatile int right_count = 0;

static volatile int last_left = 0;
static volatile int last_right = 0;

// Interrupt based on wheel encoder
//
ISR(PCINT1_vect)
{

  // Get the value at the pins
  //
  const int left = PINC & (1 << 4);
  const int right = PINC & (1 << 5);

  // Determine which pin to update
  // CPM: I admit that I don't understand why we're XORing
  //      current sample with the last sample
  if (left ^ last_left)
  {
    left_count += 1;
  }
  if (right ^ last_right)
  {
    right_count += 1;
  }

  // reset
  //
  last_left = left;
  last_right = right;
}

namespace rolley
{

    inline void ResetLeft()
    {
        noInterrupts();
        left_count = 0;
        interrupts();
    }

    inline void ResetRight()
    {
        noInterrupts();
        right_count = 0;
        interrupts();
    }

    inline int getRightCounts()
    {
        noInterrupts();
        const int tmp = left_count;
        interrupts();
        return tmp;
    }

    inline int getLeftCounts()
    {
        noInterrupts();
        const int tmp = right_count;
        interrupts();
        return tmp;
    }

    Encoders::Encoders() {}

    void Encoders::setup()
    {
        // Make sure the pin is set for input
        //
        pinMode(LeftWheelEncoder, INPUT);
        pinMode(RightWheelEncoder, INPUT);

        // Enable the pull-up resistor
        //
        digitalWrite(LeftWheelEncoder, HIGH);
        digitalWrite(RightWheelEncoder, HIGH);

        // Prevent interrupts while initializing
        //
        noInterrupts();

        // Pin 14 for left wheel, Pin 15 for the right wheel
        //
        PCICR = 1 << PCIE1;
        PCMSK1 |= (1 << PCINT12) | (1 << PCINT13);
        MCUCR = (1 << ISC00);

        // Clear the interrupt flags in case they were set before for any reason.
        // On the AVR, interrupt flags are cleared by writing a logical 1
        // to them.
        //
        PCIFR |= (1 << PCIF0) | (1 << PCIF1) | (1 << PCIF2);

        // re-enable interrupts
        //
        interrupts();
    }

    float Encoders::convert(int count)
    {
        static const float ppr = 20.0f;
        static const float pi = 3.1416f;
        static const float diameter = 0.0635f;
        static const float circumference = pi * diameter;
        return circumference * count / ppr;
    }

    void Encoders::reset_left()
    {
        ResetLeft();
    }
    void Encoders::reset_right()
    {
        ResetRight();
    }

    float Encoders::left()
    {
        return this->convert(getLeftCounts());
    }

    float Encoders::right()
    {
        return this->convert(getRightCounts());
    }

    String Encoders::test()
    {
        String response = String("");
        response += "EL";
        response += this->left();
        response += ";";
        response += "ER";
        response += this->right();
        return(response);
    }
}
