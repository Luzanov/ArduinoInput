#ifndef ADNS5030_h
#define ADNS5030_h

#include "Arduino.h"
#include <inttypes.h>

class ADNS5030 {
private:
    void sendData(uint8_t);
    
protected:
    uint8_t _sclkPin;
    uint8_t _misoPin;
    uint8_t _mosiPin;
    uint8_t _ncsPin;
    uint8_t readRegister(uint8_t);
    void writeRegister(uint8_t, uint8_t);

public:
    ADNS5030(uint8_t, uint8_t, uint8_t, uint8_t);
    void begin(void);
    signed char dx(void);
    signed char dy(void);
    signed char getMouseControl(void);
    bool motion();
    void setMouseControl(uint8_t);
};
#endif
