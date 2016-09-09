#ifndef LightEffectDriver_h
#define LightEffectDriver_h
#include <Arduino.h>
#include <avr/pgmspace.h>

enum LightEffect { SWITCH, FADE, FADEOVER };
enum LightEffectOrder { ORDERED, RANDOM };
enum LightEffectDirection { NONE, UP, DOWN, UPDOWN };
enum LightEffectCurve { LIN, INV, EXP, EXPINV };

class LightEffectDriver {
  public:
    LightEffectDriver(byte* pins, byte pinNumber);
    void update();
    void setEffect(LightEffect effect, LightEffectOrder order, LightEffectDirection direction, LightEffectCurve curve);
    void setEffectSpeed(byte speed);
    void setMinValues(byte* minValues);
    void setMaxValues(byte* maxValues);
  private:
    void _calculateChangeInterval();
    byte _chooseNextPinIndex(byte currentIndex);
    void _setPins();
    /* Constants: */
    static const uint8_t _expTable[] PROGMEM;
    /* Variables: */
    byte* _pins;
    byte _pinNumber;
    byte _speed;
    LightEffect _effect;
    LightEffectOrder _order;
    LightEffectDirection _direction;
    LightEffectCurve _curve;
    byte* _minValues;
    byte* _maxValues;
    /* State Variables: */
    byte* _pinValues;
    unsigned long _lastChange;
    unsigned long _changeInterval; /* TODO: maybe smaller datatype? */
    byte _indexPin1;
    byte _indexPin2; /* Only for FADEOVER effect */
    LightEffectDirection _directionState; /* Only for UPDOWN direction */
};

#endif
