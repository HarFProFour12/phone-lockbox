#include "hardware.h"
#include "globals.h"

void initDisplay() {
  tft.init();
  tft.setRotation(1);
}

void initPins() {
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(okPin, INPUT_PULLUP);
  pinMode(backPin, INPUT_PULLUP);

  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, LOW);

  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  pinMode(batteryPin, INPUT);

  ledcAttach(backlightPin, 5000, 8);
}

void pulseSolenoid() {
  digitalWrite(solenoidPin, HIGH);
  delay(7500);
  digitalWrite(solenoidPin, LOW);
}

void updateBrightness() {
  if screenAsleep {
    return;
  }
  int pwm = map(brightness, 0, 100, 0, 255);
  ledcWrite(backlightPin, pwm);
}

void updateBattery() {
  int raw = analogRead(batteryPin);
  float voltage = (raw / 4095.0) * 3.3 * 2.0;

  int percentage = map(voltage * 100, 300, 420, 0, 100);
  percentage = constrain(percentage, 0, 100);
  batteryPercent = percentage;
}

static void beep(unsigned int freq, unsigned int durationMs) {
  if (!soundsOn) {
    return;
  }
  tone(buzzerPin, freq, durationMs);
}

void beepClick() {
  beep(1200, 40);
}

void beepConfirm() {
  beep(1800, 80);
}

void beepLockStart() {
  beep(880, 120);
  delay(130);
  beep(1320, 160);
}

void beepUnlock() {
  beep(1320, 100);
  delay(110);
  beep(1760, 100);
  delay(110);
  beep(2200, 160);
}

void beepCancel() {
  beep(600, 150);
  delay(160);
  beep(400, 220);
}

void sleepScreen() {
  screenAsleep = True;
  ledcWrite(backlightPin, 0);
}

void wakeScreen() {
  screenAsleep = false;
  updateBrightness();
}

void checkIdleSleep() {
  if (!screenAsleep && millis() - lastActivityMs >= idleTimeoutMs) {
    sleepScreen();
  }
}