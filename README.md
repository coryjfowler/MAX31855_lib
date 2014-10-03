MAX31855* Library for Arduino

MAX31855* library v0.7
================================
This library is compatible any shield or breakout that uses the MAX31855 Thermocouple Amplifier.
This library utilizes hardware SPI, meaning you can share the MISO and SCLK signals with other SPI devices.
This library supports the ADG608 analog multiplexer found on Ocean Controls' shield.

Installation
==============
Copy this into your "[...]/MySketches/libraries/" folder and restart the Arduino editor.


Useage
==============
There are three functions, two will return independant temperature values and one returns the error bits.
The library prevents re-reading the IC by reading the IC at an interval defined in MAX31855.h.
The interval is set to 50 milliseconds and is to keep the data paired. 
'SCALE' only supports 0 for Celsius/Centigrade or 2 for Fahrenheit at this time.

InternalTempDoubleVariable = intTemp(SCALE);
ExternalTempDoubleVariable = extTemp(SCALE);
ErrorByteVariable = getErr(SCALE);


There is a function that will pull in all values simultaneously and reads the IC as the function is called.
'SCALE' only supports 0 for Celsius/Centigrade, 1 for Kelvin, 2 for Fahrenheit, and 3 for Rankine.

 getTemp(ExternalTempDoubleVariable, InternalTempDoubleVariable, SCALE, ErrorByteVariable);


There is a function that will set the address and enable bits of the ADG608 multiplexer found on Ocean Controls' MAX31855 shield.  First, the MUX define parameter in MAX31855.h will need to be set to 1 to enable MUX support. 0 corresponds to channel 1, and so on.
 
 setMUX(ChannelNumber-1);


Happy Coding!
