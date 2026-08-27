#include "lock.h"
#include "globals.h"
#include "graphics.h"
#include "hardware.h"
#include "home.h"
#include "ui.h"

static unsigned long lastSaveMs = 0;

static String remainingClock() {
  unsigned long totalSec = lockRemainingMs() / 1000UL;
  int hours = totalSec / 3600UL;
  int mins = (totalSec % 3600UL) / 60UL;
  int secs = totalSec % 60UL;

  auto two = [](int n) {
    return n < 10 ? "0" + String(n) : String(n);
  };

  return two(hours) + ":" + two(mins) + ":" + two(secs);
}

static void drawLockMessage(const char* title) {
  drawBackground();
  tft.pushImage(1, 46, 152, 184, image_byte_happy_copy_1_pixels);
  drawTitle(title);

  drawBatteryIcon();
}

void drawLocked() {
  drawBackground();

  tft.setTextColor(main_color, bg_color);
  tft.setTextSize(6);
  tft.drawString(remainingClock(), 19, 99);

  tft.setTextColor(title_color, bg_color);
  tft.setTextSize(3);
  tft.drawString("CANCEL?", 189, 211);

  drawBatteryIcon();
}

void startLock() {
  currentScreen = LOCKED;
  drawLockMessage("LOCKING...");
  pulseSolenoid();

  phone_locked = true;
  lockStartMs = millis();
  lockDurationMs = (unsigned long)lockTimeHours * 3600UL * 1000UL;
  lastLockDrawMs = millis();
  lastSaveMs = millis();

  beepLockStart();
  saveLockProgress();
  drawLocked();
}

static void finishUnlock() {
  totalLockSeconds += (millis() - lockStartMs) / 1000UL;
  lockCount += 1;

  phone_locked = false;
  lockDurationMs = 0;
  saveLockProgress();
  saveSettings();

  beepUnlock();

  drawBackground();
  tft.pushImgae(1, 46, 152, 184, image_byte_celebrating_pixels)
  drawTitle("UNLOCKED!");
  drawBatteryIcon();
  delay(2500);

  currentScreen = HOME;
  selected = 0;
  arrowY = 102;
  drawHome();
}

void cancelLock() {
  drawBackground();
  tft.pushImage(1, 46, 136, 184, image_byte_sad_pixels);
  drawTitle("CANCELLED");
  drawBatteryIcon();
  beepCancel();
  pulseSolenoid();

  phone_locked = false;
  lockDurationMs = 0;
  saveLockProgress();

  currentScreen = HOME;
  selected = 0;
  arrowY = 102;
  drawHome();
}

void updateLock() {
  if (!phone_locked) return;

  if (lockRemainingMs() == 0) {
    drawLockMessage("UNLOCKING");
    pulseSolenoid();
    finishUnlock();
    return;
  }

  if (millis() - lastLockDrawMs >= 1000UL) {
    lastLockDrawMs = millis();
    drawLocked();
  }

  if (millis() - lastSaveMs >= 30000UL) {
    lastSaveMs = millis();
    saveLockProgress();
  }
}
