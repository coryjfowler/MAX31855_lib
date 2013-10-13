MAX31855* Library for Arduino

MAX31855* library v0.5 Initial Release
================================
This library is compatible any shield or breakout that uses the MAX31855 Thermocouple Amplifier.
This library utilizes hardware SPI, meaning you can share the MISO and SCLK signals with other SPI devices.

Installation
==============
Copy this into your "[...]/MySketches/libraries/" folder and restart the Arduino editor.


Useage
==============
There are three functions that will return independant temperature values.
The library prevents re-reading the IC by reading the IC at an interval defined in MAX31855.h.
The interval is set to 50 milliseconds and is to keep the data paired. 
'SCALE' only supports 0 for Celsius/Centigrade or 2 for Fahrenheit at this time.

doubleVariable = intTemp(SCALE);
doubleVariable = extTemp(SCALE);
byteVariable = getErr(SCALE);

There is a function that will pull in all values simultaneously and reads the IC as the function is called.
'SCALE' only supports 0 for Celsius/Centigrade, 1 for Kelvin, 2 for Fahrenheit, and 3 for Rankine.

 getTemp(ExternalTempDoubleVariable, InternalTempDoubleVariable, SCALE, ErrorByteVariable);

Happy Coding!
