#include <LightEffectDriver.h>

LightEffectDriver::LightEffectDriver() {
  /* Set scalar variables: */
  _pinNumber = 0;
  _speed = 100;
  _effect = SWITCH;
  _order = ORDERED;
  _direction = UP;
  _curve = EXP;
  _lastChange = 0;
  _indexPin1 = 0;
  /* TODO: Maybe init indexPin2? */
  _directionState = UP;
  _fadingDirection = UP;
  /* Calculate changeInterval: */
  _calculateChangeInterval();
}

bool LightEffectDriver::begin(byte* pins, byte pinNumber) {
  if (_pinNumber != 0) {
    /* begin() already called */
    return false;
  };
  if (pinNumber == 0) {
    /* invalid argument */
    return false;
  };
  /* Set scalar variables: */
  _pinNumber = pinNumber;
  /* Set array variables: */
  _pins = new byte[pinNumber];
  _minValues = new byte[pinNumber];
  _maxValues = new byte[pinNumber];
  _pinValues = new byte[pinNumber];
  for (int i=0; i < pinNumber; ++i) {
    _pins[i] = pins[i];
    _minValues[i] = 0;
    _maxValues[i] = 255;
    _pinValues[i] = 0;
  }
  /* Return success: */
  return true;
}

LightEffectDriver::~LightEffectDriver() {
  if (_pinNumber != 0) {
    /* begin() was called */
    delete[] _pins;
    delete[] _minValues;
    delete[] _maxValues;
    delete[] _pinValues;
  };
}

void LightEffectDriver::update() {
  if (_pinNumber == 0) {
    /* begin() wasn't called */
    return;
  };
  /* Check the last change: */
  if (millis() - _lastChange < _changeInterval) {
    return;
  };
  /* Check the effect: */
  if (_effect == SWITCH) {
    /* Switching */
    _changeDirection();
    _indexPin1 = _chooseNextPinIndex(_indexPin1);
    for (int i=0; i < _pinNumber; ++i) {
      if (i == _indexPin1) {
        _pinValues[i] = _maxValues[i];
      } else {
        _pinValues[i] = _minValues[i];
      };
    }
  } else if (_effect == FADE) {
    /* Fading */
    if (_fadingDirection == UP && _pinValues[_indexPin1] == _maxValues[_indexPin1]) {
      /* Maximum reached, fade down: */
      _fadingDirection = DOWN;
    } else if (_fadingDirection == DOWN && _pinValues[_indexPin1] == _minValues[_indexPin1]) {
      /* Minimum reached, change direction or go to next pin: */
      _changeDirection();
      _indexPin1 = _chooseNextPinIndex(_indexPin1);
    } else {
      /* No end reached, fade: */
      /* TODO: Use stepSize! But beware of overflows and type conversion! */
      //byte stepSize = _lastChange/_changeInterval;
      if (_fadingDirection == UP) {
        _pinValues[_indexPin1]++;
      } else {
        _pinValues[_indexPin2]--;
      };
    };
  } else if (_effect == FADEOVER) {
    /* Fading over */
    /* TODO: FadeOver effect */
  };
  /* Set pins: */
  _setPins();
  /* Set last change: */
  _lastChange = millis();
}

bool LightEffectDriver::setEffect(LightEffect effect, LightEffectOrder order, LightEffectDirection direction, LightEffectCurve curve) {
  if (_pinNumber == 0) {
    /* begin() wasn't called */
    return false;
  };
  /* Check arguments: */
  if (effect != SWITCH && effect != FADE && effect != FADEOVER) {
    /* Invalid effect value */
    return false;
  };
  if (order != ORDERED && order != RANDOM) {
    /* Invalid effect order */
    return false;
  };
  if (direction != UP && direction != DOWN && direction != UPDOWN) {
    /* Invalid effect direction */
    return false;
  };
  if (curve != LIN && curve != INV && curve != EXP && curve != EXPINV) {
    /* Invalid effect curve */
    return false;
  };
  /* Set variables: */
  _effect = effect;
  _order = order;
  _direction = direction;
  _curve = curve;
  /* Update: */
  _calculateChangeInterval();
  /* Return success: */
  return true;
}

void LightEffectDriver::setEffectSpeed(byte speed) {
  if (_pinNumber == 0) {
    /* begin() wasn't called */
    return;
  };
  _speed = speed;
  /* Update: */
  _calculateChangeInterval();
}

void LightEffectDriver::setMinValues(byte* minValues) {
  if (_pinNumber == 0) {
    /* begin() wasn't called */
    return;
  };
  for (int i=0; i < _pinNumber; ++i) {
    _minValues[i] = minValues[i];
  }
}

void LightEffectDriver::setMaxValues(byte* maxValues) {
  if (_pinNumber == 0) {
    /* begin() wasn't called */
    return;
  };
  for (int i=0; i < _pinNumber; ++i) {
    _maxValues[i] = maxValues[i];
  }
}

void LightEffectDriver::_calculateChangeInterval() {
  /* 1ms ... 1021ms */
  /* TODO: 1ms won't work, Arduino's PWM cycle duration is 2ms. */
  _changeInterval = -4*_speed + 1021;
  if (_effect == SWITCH) {
    /* 10ms ... ~10s */
    _changeInterval *= 10;
  };
}

byte LightEffectDriver::_chooseNextPinIndex(byte currentIndex) {
  if (_order == RANDOM) {
    /* Random order, choose a random pin to be the next: */
    return random(0, _pinNumber);
  } else {
    /* Check for direction: */
    if (_getEffectDirection() == UP) {
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
  int i;
  switch (_curve) {
    case INV:
      /* inverted */
      for (i=0; i < _pinNumber; ++i) {
        analogWrite(_pins[i], 255-_pinValues[i]);
      }
      break;
    case EXP:
      /* exponential */
      for (i=0; i < _pinNumber; ++i) {
        analogWrite(_pins[i], pgm_read_byte(&_expTable[_pinValues[i]]));
      }
      break;
    case EXPINV:
      /* exponential & inverted */
      for (i=0; i < _pinNumber; ++i) {
        analogWrite(_pins[i], pgm_read_byte(&_expTable[255-_pinValues[i]]));
      }
      break;
    default:
      /* linear */
      for (i=0; i < _pinNumber; ++i) {
        analogWrite(_pins[i], _pinValues[i]);
      }
  }
}

LightEffectDirection LightEffectDriver::_getEffectDirection() {
  if (_direction == UPDOWN) {
    return _directionState;
  } else {
    return _direction;
  };
}

/* not for FADEOVER */
void LightEffectDriver::_changeDirection() {
  if (_order == RANDOM || _direction != UPDOWN) {
    return;
  };
  if (_direction == UP && _indexPin1 == _pinNumber-1) {
    _direction = DOWN;
  } else if (_direction == DOWN && _indexPin1 == 0) {
    _direction = UP;
  };
}

/*
 * f(x) = a * e^(x/b) with a = f(0) and b = 255/ln(255/a)
 * 
 * Generated with python:
 * import math
 * for i in range(256):
 *   print("%3d" % int(0.99*math.exp(i/255*math.log(255/0.99))), end=", ")
*/
const uint8_t LightEffectDriver::_expTable[256] PROGMEM = {
    0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
    1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
    1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
    2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
    3,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   5,   5,   5,   5,   5,
    5,   5,   5,   6,   6,   6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,
    8,   8,   8,   8,   8,   8,   9,   9,   9,   9,   9,  10,  10,  10,  10,  11,
   11,  11,  11,  12,  12,  12,  12,  13,  13,  13,  14,  14,  14,  15,  15,  15,
   16,  16,  16,  17,  17,  17,  18,  18,  19,  19,  19,  20,  20,  21,  21,  22,
   22,  23,  23,  24,  24,  25,  25,  26,  27,  27,  28,  28,  29,  30,  30,  31,
   32,  32,  33,  34,  35,  35,  36,  37,  38,  39,  40,  40,  41,  42,  43,  44,
   45,  46,  47,  48,  49,  50,  52,  53,  54,  55,  56,  58,  59,  60,  61,  63,
   64,  66,  67,  69,  70,  72,  73,  75,  77,  78,  80,  82,  84,  85,  87,  89,
   91,  93,  95,  97,  99, 102, 104, 106, 109, 111, 113, 116, 119, 121, 124, 127,
  129, 132, 135, 138, 141, 144, 147, 151, 154, 157, 161, 164, 168, 172, 176, 179,
  183, 188, 192, 196, 200, 205, 209, 214, 218, 223, 228, 233, 238, 244, 249, 255
};
