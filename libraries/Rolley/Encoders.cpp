// Copyright (C) 2012 Mark R. Stevens
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <Encoders.h>
#include <Arduino.h>

static volatile int counts1 = 0;
static volatile int counts2 = 0;

static volatile int last1 = 0;
static volatile int last2 = 0;

// Interrupt based on wheel encoder
//
ISR(PCINT1_vect)
{

  // Get the value at the pins
  //
  const int m1 = PINC & (1 << 4);
  const int m2 = PINC & (1 << 5);

  // Determine which pin to update
  // CPM: I admit that I don't understand why we're XORing
  //      current sample with the last sample
  if (m1 ^ last1)
  {
    counts1 += 1;
  }
  if (m2 ^ last2)
  {
    counts2 += 1;
  }

  // reset
  //
  last1 = m1;
  last2 = m2;
}

namespace rolley
{

    inline void ResetLeft()
    {
        noInterrupts();
        counts1 = 0;
        interrupts();
    }

    inline void ResetRight()
    {
        noInterrupts();
        counts2 = 0;
        interrupts();
    }

    inline int getRightCounts()
    {
        noInterrupts();
        const int tmp = counts1;
        interrupts();
        return tmp;
    }

    inline int getLeftCounts()
    {
        noInterrupts();
        const int tmp = counts2;
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
        return convert(getLeftCounts());
    }

    float Encoders::right()
    {
        return convert(getRightCounts());
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
