# LightEffectDriver
**Warning:** This library is at a very early stage of development and currently untested, don't expect it to work.


This is an **Arduino library** for doing cool stuff with **multiple lights** using PWM. Everything is done **non-blocking**,
to use it you just need to specify the effect and call the *update()*-function in your program loop. In theory, the library
supports an unlimited amount of lights and any type of light the Arduino can drive directly or indirectly, e.g.
* small **LEDs** directly
* bigger LEDs, **LED-lamps**, **LED-strips** or other Low-Voltage **light bulbs** using transistors

The available **effects** are:
* **Switching** through the lights
* **Fading** the lights on and off, one after another
* Fading through the lights; while one light fades off the next one fades on

This can happen in a random order, in one direction (up or down) or in both directions (up,down,up,...). There are
modifiing curves which can be applied on the values:
* fading inverted (from maximum to minimum value)
* fading with an exponential function (to compensate the logarithmic characteristic curve of the human eye)
* fading with an inverted exponential function (from max to min)

Minimum and maximum values are 0 resp. 255 by default but can be adjusted. Speed can be adjusted between 10ms and 10s for
switching to the next light and 1ms and 1s for fading to the next value.

## Example
```arduino
/* Include the library: */
#include <LightEffectDriver.h>

/* Specify the number of pins to use: */
const int pinNumber = 3;
/* Specify the pin numbers (They need to suppport PWM!): */
byte pins[pinNumber] = {9,10,11};

/* Create the driver instance: */
LightEffectDriver driver;

void setup() {
  /* Initialize driver: */
  if (!driver.begin(pins, pinNumber)) {
    /* Initialization failed, should be handled here. */
  };
  /* Fade up & down with an exponential function: */
  driver.setEffect(FADE, ORDERED, UPDOWN, EXP);
  /* Set speed to maximum: */
  driver.setEffectSpeed(255);
}

void loop() {
  /* Let the library do its work: */
  driver.update();
}
```
This example program fades through 3 lights up & down at maximum speed until it is stopped. For a full example with all possibilities, see `examples/FullDemo/FullDemo.ino`.

## API Documentation
TODO

## Wishlist
TODO
