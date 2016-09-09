#ifndef LightEffectDriver_h
#define LightEffectDriver_h
#include <Arduino.h>
#include <avr/pgmspace.h>

/**
 * Available light effects.
*/
enum LightEffect {
  /**
   * Switches through the lights.
  */
  SWITCH,
  /**
   * Fades the light on, then off,
   * then switches to the next.
  */
  FADE,
  /**
   * Fades the next light on while
   * the current one is still fading off.
  */
  FADEOVER
};

/**
 * Available orders in which
 * the next light is selected.
*/
enum LightEffectOrder {
  /**
   * Ordered, needs an effect direction.
   * (UP, DOWN or UPDOWN)
  */
  ORDERED,
  /**
   * Randomly, ignores effect direction.
  */
  RANDOM
};

/**
 * Available directions for ordered selection.
*/
enum LightEffectDirection {
  /**
   * No direction, only allowed for
   * random selection.
  */
  NONE,
  /**
   * Counting pin index up.
  */
  UP,
  /**
   * Counting pin index down.
  */
  DOWN,
  /**
   * Counting alternating up and down.
  */
  UPDOWN
};

/**
 * Available pin value modifier curves.
*/
enum LightEffectCurve {
  /**
   * No modification, fading from dark to
   * bright with a linear function.
  */
  LIN,
  /**
   * Fading from bright to dark with a
   * linear function.
  */
  INV,
  /**
   * Fading from dark to bright with an
   * exponential function, this is mostly
   * the best choice because it looks linear
   * to the human eye.
  */
  EXP,
  /**
   * Fading from bright to dark with an
   * exponential function.
  */
  EXPINV
};

class LightEffectDriver {
  public:
    /**
     * Default constructor.
     * 
     * @param pins Array of pins.
     * @param pinNumber Number of entries in pins-array.
    */
    LightEffectDriver(byte* pins, byte pinNumber);
    /**
     * Default deconstructor.
    */
    ~LightEffectDriver();
    /**
     * Does the work, should be called as often as
     * possible in main loop.
    */
    void update();
    /**
     * Sets the light effect and effect params.
     * 
     * @param effect The effect.
     * @param order The order of the effect.
     * @param direction The direction of the effect.
     * @param curve The value-conversion-curve for the effect.
    */
    void setEffect(LightEffect effect, LightEffectOrder order, LightEffectDirection direction, LightEffectCurve curve);
    /**
     * Sets the effect speed.
     * 
     * @param speed The effect speed.
    */
    void setEffectSpeed(byte speed);
    /**
     * Sets the minimum value for each pin, default is 0.
     * 
     * @param minValues Array of minimum values.
    */
    void setMinValues(byte* minValues);
    /**
     * Sets the maximum value for each pin, default is 255.
     * 
     * @param maxValues Array of maximum values.
    */
    void setMaxValues(byte* maxValues);
  private:
    /**
     * Calculates _changeInterval from effect and speed.
    */
    void _calculateChangeInterval();
    /**
     * Calculates the next pin index, modifies nothing.
     * 
     * @param currentIndex The current pin index.
     * @return The new pin index.
    */
    byte _chooseNextPinIndex(byte currentIndex);
    /**
     * Applies the curve type and sets physical pins.
    */
    void _setPins();
    /**
     * Calculates the real effect direction (important for UPDOWN).
     * 
     * @return The direction, UP or DOWN.
    */
    LightEffectDirection _getEffectDirection();
    /**
     * Checks if the direction needs to be changed and changes it.
    */
    void _changeDirection();
    /* Constants: */
    /**
     * The table with values of the exponential function.
    */
    static const uint8_t _expTable[] PROGMEM;
    /* Variables: */
    /**
     * The array with pin numbers.
    */
    byte* _pins;
    /**
     * The number of pins.
    */
    byte _pinNumber;
    /**
     * The effect speed.
    */
    byte _speed;
    /**
     * The light effect.
    */
    LightEffect _effect;
    /**
     * The effect order.
    */
    LightEffectOrder _order;
    /**
     * The effect direction.
    */
    LightEffectDirection _direction;
    /**
     * The effect curve.
    */
    LightEffectCurve _curve;
    /**
     * The array with minValues for each pin.
    */
    byte* _minValues;
    /**
     * The array with maxValues for each pin.
    */
    byte* _maxValues;
    /* State Variables: */
    /**
     * The value for each pin, without curve applied.
    */
    byte* _pinValues;
    /**
     * The millis()-value of the last update()-run.
    */
    unsigned long _lastChange;
    /**
     * The time between update()-runs in ms,
     * calculated by _calculateChangeInterval().
    */
    unsigned long _changeInterval; /* TODO: maybe smaller datatype? */
    /**
     * The _pins-array index of the active pin.
    */
    byte _indexPin1;
    /**
     * The _pins-array index of the second active pin.
     * (only for FADEOVER-effect)
    */
    byte _indexPin2;
    /**
     * The real effect direction for UPDOWN direction.
    */
    LightEffectDirection _directionState;
    /**
     * The fading direction.
    */
    LightEffectDirection _fadingDirection;
};

#endif
