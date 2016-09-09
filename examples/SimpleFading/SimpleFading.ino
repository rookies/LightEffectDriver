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
