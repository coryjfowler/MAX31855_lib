/***************************************************************************
  Library for the MAX31855* thermocouple amplifier from Maxim Semiconductor
  Written by Cory J. Fowler
  BSD license, all text above must be included in any redistribution.
 ***************************************************************************/
#ifndef _MAX31855_H_
#define _MAX31855_H_

#include "Arduino.h"

#define DEBUG 0

// Set to 1 if input is multiplexed (Ocean Controls Shield)
#define MUX   0
// Pins for multiplexer control (Ignore if not needed.)
#define AD0   4
#define AD1   5
#define AD2   6
#define MX_EN 7

// Timeout before intTemp(), extTemp(), or tempErr() read from the MAX31855 again this is to keep data paired.
#define TIME  50

class MAX31855 {
  public:
    MAX31855(int _CS);
    void begin(void);
  
/* Reads chip at interval derrived from TIME constant above in this file.
    Use these functons where you want a value returned, the timing aids in
    keeping the values matched verses reading the chip again for each value.  */
// Supports 0 for Celcius and 2 for Fahrenheit
    double intTemp(int _SCALE); 
    double extTemp(int _SCALE);
    byte tempErr();
  
// Used for the Ocean Controls Shield that features the ADG608 analog multiplexer.
    void setMUX(byte _MUX);
  
// Reads chip as the function is called.  My testing on an ATmega328p @ 16MHz shows it executes in about 80 microseconds.
// Supports 0 for Celcius, 1 For Kelvin, 2 for Fahrenheit, and 2 for Rankine
    void getTemp(double &_external, double &_internal, byte _SCALE, byte &_error);

 private:
    byte CS;
    boolean initRead;
    long data;
    unsigned long previous;
    void ReadSPI(void);
};
#endif
/***************************************************************************
  END FILE
 ***************************************************************************/
