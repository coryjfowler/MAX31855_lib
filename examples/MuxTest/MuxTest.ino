/***************************************************************************
  Examle for MAX31855_lib library for MAX31855* thermocouple amplifier
  Written by Cory J. Fowler
  BSD license, all text above must be included in any redistribution.
 ***************************************************************************/

#include <SPI.h>
#include <MAX31855.h>

const byte scale = 0;   // 0 is Celsius/Centigrade, ~80µs. 1 is Kelvin, ~108µs. 2 is Fahrenheit ~100µs. 3 is Rankine, ~100µs.

byte error;
byte channel = 0;

double external;
double internal;

byte cls[] = {0x1B,0x5B,0x32,0x4A,0x1B,0x5B,0x3B,0x48,0x0A,0x0D};            // Terminal control commands to erase screen and return home: <Esc>[2J<Esc>[;H

MAX31855 TCM(9);


void setup(){
  TCM.begin();
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
}

void loop(){
// Go get PuTTY or some other terminal program, the Arduino IDE Serial Monitor likes to crash... and take everything with it, save often. :P
// Print terminal control codes to clear screen and position cursor at home.
  if(channel == 0){
    for (byte i = 0; i < 8; i++){
      Serial.write(cls[i]);                                                    
    }
  }
  

  TCM.setMUX(channel);                                                        // Set MUX channel, enable MUX, and start MAX31855 conversion process.
  TCM.getTemp(external, internal, scale, error);                              // Read MAX31855
  
  if(channel == 0){                                                           // Just print the channel 1's cold junction
    Serial.println("Cold Junction Temperature:");
    Serial.print(internal);
    Serial.write(0xB0);                                                       // Print ° 'degree'   // Arduino IDE's UTF-8 encoding adds extra character infront of printed degree symbol.
    Serial.println("C");
    Serial.println();
  }

  Serial.println("Thermocouple Temperature:");
  Serial.print(external);
  Serial.write(0xB0);
  Serial.println("C");

  Serial.print(error, BIN);
  if (error & 0x01){
    Serial.println("  ERROR: Thermocouple Open!!");
  } else if (error & 0x02){
    Serial.println("  ERROR: Thermocouple Shorted To Ground!!");
  } else if (error & 0x04){
    Serial.println("  ERROR: Thermocouple Shorted To Power!!");
  } else {
    Serial.println();
  }
  
  if(channel == 7){
    channel = 0;
    delay(5000);
  } else {
    channel++;
  }
  Serial.println();
}
