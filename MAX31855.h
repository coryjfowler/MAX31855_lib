/***************************************************************************
  Library for the MAX31855* thermocouple amplifier from Maxim Semiconductor
  Written by Cory J. Fowler
  BSD license, all text above must be included in any redistribution.
 ***************************************************************************/

#include "Arduino.h"
#define TIME 50
#define DEBUG 0

class MAX31855 {
  public:
    MAX31855(int _CS);
 
/* Reads chip at interval derrived from TIME constant above in this file.
    Use these functons where you want a value returned, the timing aids in
    keeping the values matched verses reading the chip again for each value.  */
  // Supports 0 for Celcius and 2 for Fahrenheit
    double intTemp(int _SCALE); 
    double extTemp(int _SCALE);
    int tempErr();
  
// Reads chip as the function is called.  My testing on an ATmega328p @ 16MHz shows it executes in about 80 microseconds.
// Supports 0 for Celcius, 1 For Kelvin, 2 for Fahrenheit, and 2 for Rankine
    void getTemp(double &_external, double &_internal, byte _SCALE, byte &_error);

 private:
    byte CS;
    byte initRead;
    long data;
    unsigned long previous;
    void ReadSPI(void);
};
