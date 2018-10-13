#ifndef KeyboardPinObserver_h
#define KeyboardPinObserver_h

#include "Arduino.h"
#include <inttypes.h>

class KeyboardPinObserver {
private:
    int lastState;
    unsigned long lastDebounceTime;
    
protected:
    int _readPin;
    int _writePin;

public:
    KeyboardPinObserver(int, int);
    int state;
    bool hasBeenChangedState;
    void begin(void);
    void update(void);
};
#endif
