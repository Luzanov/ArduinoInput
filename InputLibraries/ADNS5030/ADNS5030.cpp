
/******************************************************************************
 * Doc
 * http://datasheet.octopart.com/ADNS-5030-Avago-datasheet-10314086.pdf
 * ADNS 5030
******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "ADNS5030.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

#define ADNS_MOTION_STATUS  0x02
#define ADNS_DELTA_X        0x03
#define ADNS_DELTA_Y        0x04
#define ADNS_MOUSE_CONTROL  0x0d

#define ADNS_DELAY_TSWW     31      // SPI Time between Write Commands
#define ADNS_DELAY_TSRAD    4       // SPI Read Address-Data Delay
#define ADNS_DELAY_TSRWSRR  2       // tSRW & tSRR = 1μs.

/******************************************************************************
 * Constructors
 ******************************************************************************/

ADNS5030::ADNS5030(uint8_t sclkPin, uint8_t misoPin, uint8_t mosiPin, uint8_t ncsPin) {
    _sclkPin = sclkPin;
    _misoPin = misoPin;
    _mosiPin = mosiPin;
    _ncsPin = ncsPin;
}

/******************************************************************************
 * Private
 ******************************************************************************/

void ADNS5030::sendData(uint8_t data) {
    for (byte i = 0x80; i; i >>= 1) {
        digitalWrite(_sclkPin, LOW);
        digitalWrite(_mosiPin, data & i ? HIGH : LOW);
//        asm volatile ("nop");
        digitalWrite(_sclkPin, HIGH);
    }
}

/******************************************************************************
 * Protected
 ******************************************************************************/

void ADNS5030::begin(void) {
    pinMode(_misoPin, INPUT);
    pinMode(_ncsPin, OUTPUT);
    pinMode(_sclkPin, OUTPUT);
    pinMode(_mosiPin, OUTPUT);
    digitalWrite(_misoPin, LOW);
    digitalWrite(_ncsPin, HIGH);
    digitalWrite(_sclkPin, HIGH);
    digitalWrite(_mosiPin, HIGH);
}

signed char ADNS5030::dx(void) {
	return (signed char) readRegister(ADNS_DELTA_X);
}

signed char ADNS5030::dy(void) {
	return (signed char) readRegister(ADNS_DELTA_Y);
}

signed char ADNS5030::getMouseControl(void) {
    return (signed char) readRegister(ADNS_MOUSE_CONTROL);
}

bool ADNS5030::motion() {
    return readRegister(ADNS_MOTION_STATUS);
}

void ADNS5030::setMouseControl(uint8_t value) {
    // Reset chip
    writeRegister(0x3a, 0x5a);
    // Set CPI
    writeRegister(ADNS_MOUSE_CONTROL, value);
}

uint8_t ADNS5030::readRegister(uint8_t address) {
    digitalWrite(_ncsPin, LOW);
    sendData(address & ~0x80);
    delayMicroseconds(ADNS_DELAY_TSRAD);
    
    uint8_t data = 0;
    for (byte i = 8; i; i--) {
        digitalWrite(_sclkPin, LOW);
        //        asm volatile ("nop");
        digitalWrite(_sclkPin, HIGH);
        data <<= 1;
        if (digitalRead(_misoPin)) {
            data |= 0x01;
        }
    }
    digitalWrite(_ncsPin, HIGH);
    delayMicroseconds(ADNS_DELAY_TSRWSRR);
    return data;
}

void ADNS5030::writeRegister(uint8_t address, uint8_t data) {
    digitalWrite(_ncsPin, LOW);
    sendData(address | 0x80);
    delayMicroseconds(1);
    sendData(data);
    delayMicroseconds(ADNS_DELAY_TSWW);
    digitalWrite(_ncsPin, HIGH);
}
