#include "ADNS5030.h"
#include "PinObserver.h"
#include <SoftwareSerial.h>

ADNS5030 sensor = ADNS5030(6, 7, 8, 9); // sclk, miso, mosi, ncs
PinObserver leftButton = PinObserver(3);
PinObserver rightButton = PinObserver(2);
SoftwareSerial serial(5, 4);  // Rx, Tx

void setup() {
  rightButton.begin();
  leftButton.begin();
  serial.begin(9600);
  sensor.begin();
}

void loop() {
  leftButton.update();
  rightButton.update();
  
  if (sensor.motion() || leftButton.hasBeenChangedState || rightButton.hasBeenChangedState) {
    int8_t deltaX = -sensor.dx();
    int8_t deltaY = -sensor.dy();
    int8_t firstByte = 127; // Begin of message
    int8_t buttonsState = 0;

    if (leftButton.state == HIGH) {
      buttonsState |= 1 << 0;
    }
    if (rightButton.state == HIGH) {
      buttonsState |= 1 << 1;
    }
    serial.write(firstByte);
    serial.write(deltaX);
    serial.write(deltaY);
    serial.write(buttonsState);
  }
}

