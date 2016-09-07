#include <LightEffectDriver.h>

LightEffectDriver::LightEffectDriver(byte* pins, byte pinNumber) {
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
    _indexPin1 = _chooseNextPinIndex(_indexPin1);
  } else if (_effect == FADE) {
    /* TODO */
  } else if (_effect == FADEOVER) {
    /* TODO */
  };
  /* Set pins: */
  _setPins();
  /* Set last change: */
  _lastChange = millis();
}

void LightEffectDriver::setEffect(LightEffect effect, LightEffectOrder order, LightEffectDirection direction) {
  /* TODO: Check arguments */
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

void LightEffectDriver::setMinValues(byte* minValues) {
  for (int i; i < _pinNumber; ++i) {
    _minValues[i] = minValues[i];
  }
}

void LightEffectDriver::setMaxValues(byte* maxValues) {
  for (int i; i < _pinNumber; ++i) {
    _maxValues[i] = maxValues[i];
  }
}

void LightEffectDriver::_calculateChangeInterval() {
  // TODO: _changeInterval = someAlgorithm(_speed, _effect);
}

byte LightEffectDriver::_chooseNextPinIndex(byte currentIndex) {
  if (_order == RANDOM) {
    /* Random order, choose a random pin to be the next: */
    return random(0, _pinNumber);
  } else {
    /* Ordered, check for UPDOWN direction: */
    LightEffectDirection dir = _direction;
    if (_direction == UPDOWN) {
      dir = _directionState;
    };
    /* Check for effect or state direction (if effect direction is UPDOWN): */
    if (dir == UP) {
      /* Counting up, check if we are at the last pin: */
      if (currentIndex == _pinNumber-1) {
        return 0;
      } else {
        return currentIndex+1;
      };
    } else {
      /* Counting down, check if we are at the first pin: */
      if (currentIndex == 0) {
        return _pinNumber;
      } else {
        return currentIndex-1;
      };
    };
  };
}

void LightEffectDriver::_setPins() {
  if (_effect == SWITCH) {
    /* TODO */
  } else if (_effect == FADE) {
    /* TODO */
  } else if (_effect == FADEOVER) {
    /* TODO */
  };
}
