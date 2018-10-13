#ifndef PinObserver_h
#define PinObserver_h

#include "Arduino.h"
#include <inttypes.h>

class PinObserver {
private:
    int lastState;
    unsigned long lastDebounceTime;
    
protected:
    int _pin;

public:
    PinObserver(int);
    int state;
    bool hasBeenChangedState;
    void begin(void);
    void update(void);
};
#endif
