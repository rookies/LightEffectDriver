#include <LightEffectDriver.h>

LightEffectDriver::LightEffectDriver(byte[] pins, byte pinNumber) {
  _pinNumber = pinNumber;
  _pins = new byte[pinNumber];
  _minValues = new byte[pinNumber];
  _maxValues = new byte[pinNumber];
  for (int i; i < pinNumber; ++i) {
    _pins[i] = pins[i];
    _minValues[i] = 0;
    _maxValues[i] = 255;
  }
}

/* TODO: Init state variables */
/* TODO: Deconstruct _pins, _minValues, _maxValues, ... */

void LightEffectDriver::update() {
  /* Check the last change: */
  if (millis() - _lastChange < _changeInterval) {
    return;
  };
  /* Check the effect: */
  if (_effect == SWITCH) {
    /* TODO */
  } else if (_effect == FADE) {
    /* TODO */
  } else if (_effect == FADEOVER) {
    /* TODO */
  } else {
    /* FIXME: Invalid effect */
  };
}

void LightEffectDriver::setEffect(LightEffect effect, LightEffectOrder order, LightEffectDirection direction) {
  _effect = effect;
  _order = order;
  _direction = direction;
  /* Update: */
  _calculateChangeInterval();
}

void LightEffectDriver::setEffectSpeed(byte speed) {
  _speed = speed;
  /* Update: */
  _calculateChangeInterval();
}

void LightEffectDriver::setMinValues(byte[] minValues) {
  for (int i; i < pinNumber; ++i) {
    _minValues[i] = minValues[i];
  }
}

void LightEffectDriver::setMaxValues(byte[] maxValues) {
  for (int i; i < pinNumber; ++i) {
    _maxValues[i] = maxValues[i];
  }
}

void LightEffectDriver::_calculateChangeInterval() {
  _changeInterval = someAlgorithm(_speed, _effect); /* TODO */
}
