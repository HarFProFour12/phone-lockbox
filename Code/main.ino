#include "globals.h"
#include "hardware.h"
#include "buttons.h"
#include "lock.h"
#include "home.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Booting...");

  loadSettings();
  Serial.println("Settings loaded");

  initDisplay();
  Serial.println("Display initialized");

  initPins();
  Serial.println("Pins initialized");

  lastActivityMs = millis();
  updateBrightness();
  Serial.println("Brightness set");

  if (phone_locked) {
    Serial.println("Drawing locked screen");
    drawLocked();
  } else {
    Serial.println("Drawing home screen");
    drawHome();
  }

  Serial.println("Setup complete");
}

void loop() {
  checkIdleSleep();
  updateBrightness();
  updateLock();
  handleButtons();
}
