/******************************************************************************
 * Includes
 ******************************************************************************/

#include "PinObserver.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

#define DEBOUNCE_DELAY 50

/******************************************************************************
 * Constructors
 ******************************************************************************/

PinObserver::PinObserver(int pin) {
    _pin = pin;
    lastDebounceTime = 0;
    hasBeenChangedState = false;
}

/******************************************************************************
 * Protected
 ******************************************************************************/

void PinObserver::begin(void) {
    pinMode(_pin, INPUT);
}

void PinObserver::update(void) {
    hasBeenChangedState = false;
    int currentState = digitalRead(_pin);
    
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
}
