#include "communication.h"

long            _delayTX            = 2000;
unsigned long   _previousTXMillis   = 0;

const byte _txPin = 27;
const byte _rxPin = 28;

Communication _serial(_rxPin, _txPin);

void setup() {
  Serial.begin(115200);
  _serial.setup();
}

void loop() {
  if (_serial.listen()) {
    Serial.print(F("Received: [")); Serial.print(_serial.getMessage()); Serial.println(F("]"));
  }

  unsigned long currentMillis = millis();
  if (currentMillis - _previousTXMillis >= _delayTX) {
    _previousTXMillis = currentMillis;
    
    _serial.sendMessage("Hello from RP2040");
    _serial.sendMessage("See you next !");
  }
}
