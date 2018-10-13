#include "PinObserver.h"
#include <SoftwareSerial.h>
#include <KeyboardPinObserver.h>

SoftwareSerial serial(10, 11);
KeyboardPinObserver keyW = KeyboardPinObserver(5, 2);
KeyboardPinObserver keyR = KeyboardPinObserver(9, 2);
KeyboardPinObserver keyS = KeyboardPinObserver(5, 3);
KeyboardPinObserver keyA = KeyboardPinObserver(6, 3);
KeyboardPinObserver keyD = KeyboardPinObserver(7, 3);
KeyboardPinObserver keySpace = KeyboardPinObserver(8, 4);

void setup() {
  keyW.begin();
  keyR.begin();
  keyS.begin();
  keyA.begin();
  keyD.begin();
  keySpace.begin();
  serial.begin(9600);
}

void loop() {
  keyW.update();
  keyR.update();
  keyS.update();
  keyA.update();
  keyD.update();
  keySpace.update();
  
  if (keyW.hasBeenChangedState || keyR.hasBeenChangedState || keyS.hasBeenChangedState || keyA.hasBeenChangedState || keyD.hasBeenChangedState || keySpace.hasBeenChangedState) {
    int8_t buttonsState = 0;

    if (keyW.state == HIGH) { buttonsState |= 1 << 0; }
    if (keyR.state == HIGH) { buttonsState |= 1 << 1; }
    if (keyS.state == HIGH) { buttonsState |= 1 << 2; }
    if (keyA.state == HIGH) { buttonsState |= 1 << 3; }
    if (keyD.state == HIGH) { buttonsState |= 1 << 4; }
    if (keySpace.state == HIGH) { buttonsState |= 1 << 5; }
    
    serial.write(buttonsState);
  }
}

