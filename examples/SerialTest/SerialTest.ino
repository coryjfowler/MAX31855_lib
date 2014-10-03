/***************************************************************************
  Examle for MAX31855_lib library for MAX31855* thermocouple amplifier
  Written by Cory J. Fowler
  BSD license, all text above must be included in any redistribution.
 ***************************************************************************/

#include <SPI.h>
#include <MAX31855.h>

const byte scale = 0;   // 0 is Celsius/Centigrade, ~80µs. 1 is Kelvin, ~108µs. 2 is Fahrenheit ~100µs. 3 is Rankine, ~100µs.
byte error;
double external;
double internal;
unsigned long previousMicros = 0;
MAX31855 TC1(9);
byte cls[] = {0x1B,0x5B,0x32,0x4A,0x1B,0x5B,0x3B,0x48,0x0A,0x0D};            // Terminal control commands to erase screen and return home: <Esc>[2J<Esc>[;H

void setup(){
  Serial.begin(115200);
  TC1.begin();
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
}

void loop(){
// Go get PuTTY or some other terminal program, the Arduino IDE Serial Monitor likes to crash... and take everything with it, save often. :P
// Print terminal control codes to clear screen and position cursor at home.
  for (byte i = 0; i < 8; i++){
    Serial.write(cls[i]);                                                    
  }


  previousMicros = micros();
  TC1.getTemp(external, internal, scale, error);
  Serial.print(micros() - previousMicros);
  Serial.write(0xB5);                                                        // Print µ 'mu'           // Arduino IDE's UTF-8 encoding adds extra character infront of printed mu.
  Serial.println("s taken to read MAX31855*");
  Serial.println();
  
  Serial.println("Cold Junction Temperature:");
  Serial.print(internal);
  Serial.write(0xB0);                                                        // Print ° 'degree'
  Serial.println("C");
  
  Serial.print(TC1.intTemp(2));
  Serial.write(0xB0);
  Serial.println("F");
  Serial.println();

  Serial.println("Thermocouple Temperature:");
  Serial.print(external);
  Serial.write(0xB0);
  Serial.println("C");
  
  Serial.print(TC1.extTemp(2));
  Serial.write(0xB0);
  Serial.println("F");
  Serial.println();
  
  Serial.println(error, BIN);
  if (error & 0x01){
    Serial.print("ERROR: Thermocouple Open!!");
  }else if (error & 0x02){
    Serial.print("ERROR: Thermocouple Shorted To Ground!!");
  }else if (error & 0x04){
    Serial.print("ERROR: Thermocouple Shorted To Power!!");
//  }else{
//    Serial.println();
  }
  delay(1000);
}
