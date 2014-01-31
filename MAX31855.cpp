/*************************************************************************** 
  Library for the MAX31855* thermocouple amplifier from Maxim Semiconductor
  Written by Cory J. Fowler
  BSD license, all text above must be included in any redistribution.
 ***************************************************************************/

#include "MAX31855.h"
#include <SPI.h>

MAX31855::MAX31855(int _CS) {
  CS = _CS;
  initRead = 1;
  SPI.begin();
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
}

double MAX31855::intTemp(int _SCALE) {
  if (initRead | ((millis() - previous) >= TIME)){
    previous = millis();
    initRead = 0;
    ReadSPI();
  }
  
  int inTemp;
  double _internal;
  
  // Dispose of un-needed bits and preserve sign.
  if(data & 0x00008000){
    inTemp = ((data >> 4) & 0x00000FFF) | 0xF000;
  }
  else{
    inTemp = (data >> 4) & 0x00000FFF;
  }
  
  // Compute real world value...
  if(_SCALE){
    _internal = (inTemp * 0.1125) + 32;
  }
  else{
    _internal = inTemp * 0.0625;
  }
  
  return _internal;
}


double MAX31855::extTemp(int _SCALE) {	
  if (initRead | ((millis() - previous) >= TIME)){
    previous = millis();
    initRead = 0;
    ReadSPI();
  }
  
  int exTemp;
  double _external;
  
// Dispose of un-needed bits and preserve sign.
 if(data & 0x80000000){
    exTemp = ((data >> 18) & 0x000003FFF) | 0xC000;
  }
  else{
    exTemp = (data >> 18) & 0x000003FFF;
  }

// Compute real world value...
  if(_SCALE){
    _external = (exTemp * 0.45) + 32;
  }
  else{
    _external = exTemp* 0.25;
  }
  
  return _external;
}


int MAX31855::tempErr() {
  if (initRead | ((millis() - previous) >= TIME)){
    previous = millis();
    initRead = 0;
    ReadSPI();
  }
  
  return (data & 0x00000007);
}


void MAX31855::getTemp(double &_external, double &_internal, byte _SCALE, byte &_error) {	
    previous = millis();
    initRead = 0;
    ReadSPI();

  int inTemp;
  int exTemp;

// Dispose of un-needed bits and preserve sign.
    if(data & 0x00008000){
      inTemp = ((data >> 4) & 0x00000FFF) | 0xF000;
    }
    else{
      inTemp = (data >> 4) & 0x00000FFF;
    }

// Dispose of un-needed bits and perserve sign.
    if(data & 0x80000000){
      exTemp = ((data >> 18) & 0x000003FFF) | 0xC000;
    }
    else{
      exTemp = (data >> 18) & 0x000003FFF;
    }

#if DEBUG    
  Serial.println(inTemp);
  Serial.println(exTemp);
#endif
    
// Calculate real world value for farenheit or celsius scales. 
switch(_SCALE){
	case(3):
	_internal = (inTemp * 0.1125) + 273.15;
	_external = (exTemp * 0.45) + 273.15;
	break;

        case(2):
	_internal = (inTemp * 0.1125) + 32;
	_external = (exTemp * 0.45) + 32;
	break;

        case(1):
	_internal = (inTemp * 0.0625) + 273.15;
	_external = (exTemp * 0.25) + 273.15;
	break;

        default:
	_internal = inTemp * 0.0625;                                  
	_external = exTemp * 0.25;
	break;
}

#if DEBUG
  Serial.println(_internal);    
  Serial.println(_external);
#endif

  _error = data & 0x00000007;
}


void MAX31855::ReadSPI(void) {
#if DEBUG
  Serial.print("millis() = ");
  Serial.println(millis());
  Serial.print("TIME = ");
  Serial.println(TIME);
  Serial.println("Reading from MAX31855");
  Serial.println("=================");
#endif
  unsigned long _data = 0x00000000;
  digitalWrite(CS, LOW);
  delayMicroseconds(1);

  for (int i = 0; i < 4; i++) {
    _data = (_data << 8) + SPI.transfer(0x00);
  }

  digitalWrite(CS, HIGH);

#if DEBUG
  Serial.print("Raw Data = ");
  Serial.println(_data,HEX);
#endif
  data = _data;
}
