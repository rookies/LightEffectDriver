#include <LightEffectDriver.h>

const int pinNumber = 3;
byte pins[pinNumber] = {9,10,11};
LightEffectDriver driver;
byte effect = 0;
unsigned long lastChange = 0;

void setup() {
  Serial.begin(19200);
  Serial.println("Switch ordered up");
  if (!driver.begin(pins, pinNumber)) {
    Serial.println("Error on LightEffectDriver::begin().");
    while (true) { }
  };
  driver.setEffect(SWITCH, ORDERED, UP, LIN);
}

void loop() {
  /* TODO: Change speed, min- & max-values */
  if (millis()-lastChange > 10000) {
    switch (effect) {
      case 0:
        Serial.println("Switch ordered up");
        driver.setEffect(SWITCH, ORDERED, UP, LIN);
        break;
      case 1:
        Serial.println(".. down");
        driver.setEffect(SWITCH, ORDERED, DOWN, LIN);
        break;
      case 2:
        Serial.println(".. up & down");
        driver.setEffect(SWITCH, ORDERED, UPDOWN, LIN);
        break;
      case 3:
        Serial.println(".. random");
        driver.setEffect(SWITCH, RANDOM, NONE, LIN);
        break;
      case 4:
        Serial.println(".. ordered up inverted");
        driver.setEffect(SWITCH, ORDERED, UP, INV);
        break;
      case 5:
        Serial.println(".. down inverted");
        driver.setEffect(SWITCH, ORDERED, DOWN, INV);
        break;
      case 6:
        Serial.println(".. up & down inverted");
        driver.setEffect(SWITCH, ORDERED, UPDOWN, INV);
        break;
      case 7:
        Serial.println(".. random inverted");
        driver.setEffect(SWITCH, RANDOM, NONE, INV);
        break;
      case 8:
        Serial.println("Fade ordered up linear");
        driver.setEffect(FADE, ORDERED, UP, LIN);
        break;
      case 9:
        Serial.println(".. exponential");
        driver.setEffect(FADE, ORDERED, UP, EXP);
        break;
      case 10:
        Serial.println(".. down linear");
        driver.setEffect(FADE, ORDERED, DOWN, LIN);
        break;
      case 11:
        Serial.println(".. exponential");
        driver.setEffect(FADE, ORDERED, DOWN, EXP);
        break;
      case 12:
        Serial.println(".. up & down linear");
        driver.setEffect(FADE, ORDERED, UPDOWN, LIN);
        break;
      case 13:
        Serial.println(".. exponential");
        driver.setEffect(FADE, ORDERED, UPDOWN, EXP);
        break;
      case 14:
        Serial.println(".. random linear");
        driver.setEffect(FADE, RANDOM, NONE, LIN);
        break;
      case 15:
        Serial.println(".. exponential");
        driver.setEffect(FADE, RANDOM, NONE, EXP);
        break;
      case 16:
        Serial.println("FadeOver ordered up linear");
        driver.setEffect(FADEOVER, ORDERED, UP, LIN);
        break;
      case 17:
        Serial.println(".. exponential");
        driver.setEffect(FADEOVER, ORDERED, UP, EXP);
        break;
      case 18:
        Serial.println(".. down linear");
        driver.setEffect(FADEOVER, ORDERED, DOWN, LIN);
        break;
      case 19:
        Serial.println(".. exponential");
        driver.setEffect(FADEOVER, ORDERED, DOWN, EXP);
        break;
      case 20:
        Serial.println(".. up & down linear");
        driver.setEffect(FADEOVER, ORDERED, UPDOWN, LIN);
        break;
      case 21:
        Serial.println(".. exponential");
        driver.setEffect(FADEOVER, ORDERED, UPDOWN, EXP);
        break;
      case 22:
        Serial.println(".. random linear");
        driver.setEffect(FADEOVER, RANDOM, NONE, LIN);
        break;
      case 23:
        Serial.println(".. exponential");
        driver.setEffect(FADEOVER, RANDOM, NONE, EXP);
        break;
    }
    if (effect == 23) {
      effect = 0;
    } else {
      effect++;
    };
    lastChange = millis();
  }
  driver.update();
}
