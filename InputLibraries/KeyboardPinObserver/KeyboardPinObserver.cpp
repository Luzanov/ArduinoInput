/******************************************************************************
 * Includes
 ******************************************************************************/

#include "KeyboardPinObserver.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

#define DEBOUNCE_DELAY 50

/******************************************************************************
 * Constructors
 ******************************************************************************/

KeyboardPinObserver::KeyboardPinObserver(int readPin, int writePin) {
    _readPin = readPin;
    _writePin = writePin;
    state = 0;
    lastDebounceTime = 0;
    hasBeenChangedState = false;
}

/******************************************************************************
 * Protected
 ******************************************************************************/

void KeyboardPinObserver::begin(void) {
    pinMode(_readPin, INPUT);
    pinMode(_writePin, OUTPUT);
}

void KeyboardPinObserver::update(void) {
    hasBeenChangedState = false;
    digitalWrite(_writePin, HIGH);
    int currentState = digitalRead(_readPin);
    
    if (currentState != lastState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        if (state != currentState) {
            state = currentState;
            hasBeenChangedState = true;
        }
    }
    lastState = currentState;
    digitalWrite(_writePin, LOW);
}
