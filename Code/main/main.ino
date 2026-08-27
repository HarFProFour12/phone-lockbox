#include "globals.h"
#include "hardware.h"
#include "buttons.h"
#include "lock.h"
#include "home.h"

void setup() {
  loadSettings();
  initDisplay();
  initPins();
  lastActivityMs = millis();
  updateBrightness();

  if (phone_locked) {
    drawLocked();
  } else {
    drawHome();
  }
}

void loop() {
  checkIdleSleep();
  updateBrightness();
  updateLock();
  handleButtons();
}
