#include "buttons.h"
#include "globals.h"
#include "hardware.h"
#include "home.h"
#include "settings.h"
#include "stats.h"
#include "lock.h"

static bool lastUp = false;
static bool lastDown = false;
static bool lastOk = false;
static bool lastBack = false;

static const int CANCEL_PRESS_COUNT = 5;
static const unsigned long CANCEL_WINDOW_MS = 2000UL;
static int cancelPressCount = 0;
static unsigned long cancelWindowStart = 0;

static bool justPressed(int pin, bool &wasDown) {
  bool isDown = digitalRead(pin) == LOW;
  bool pressed = isDown && !wasDown;
  wasDown = isDown;
  return pressed;
}

static void resetCursor() {
  selected = 0;
  arrowY = 102;
}

static void moveCursor(int step) {
  selected += step;
  if (selected > 3) selected = 0;
  if (selected < 0) selected = 3;
  arrowY = 102 + selected * 30;
}

static void goHome() {
  currentScreen = HOME;
  resetCursor();
  drawHome();
}

static void goSettings() {
  currentScreen = SETTINGS;
  resetCursor();
  drawSettings();
}

static void trackCancelPress() {
  unsigned long now = millis();
  if (cancelPressCount == 0 || now - cancelWindowStart > CANCEL_WINDOW_MS) {
    cancelPressCount = 1;
    cancelWindowStart = now;
  } else {
    cancelPressCount++;
  }

  beepClick();

  if (cancelPressCount >= CANCEL_PRESS_COUNT) {
    cancelPressCount = 0;
    cancelLock();
  }
}

void handleButtons() {
  bool up = justPressed(upPin, lastUp);
  bool down = justPressed(downPin, lastDown);
  bool ok = justPressed(okPin, lastOk);
  bool back = justPressed(backPin, lastBack);

  if (up || down || ok ||back) {
    lastActivityMs = millis();
    if (screenAsleep) {
      wakeScreen();
      return;
    }
  }

  if (currentScreen == LOCKED) {
    if (ok) trackCancelPress();
    return;
  }

  if (phone_locked) {
    return;
  }

  if (currentScreen == HOME) {
    if (down) {
      beepClick();
      moveCursor(1);
      drawHome();
    }
    else if (up) {
      beepClick();
      moveCursor(-1);
      drawHome();
    }
    else if (ok) {
      beepConfirm();
      if (selected == 0) {
        cameFromHome = true;
        currentScreen = LOCK_TIME;
        drawLocktime();
      } 
      else if (selected == 1) {
        currentScreen = STATS;
        drawStats();
      } 
      else if (selected == 2) {
        goSettings();
      } 
      else if (selected == 3) {
        currentScreen = ABOUT;
        drawAbout();
      }
    }
  } 
  else if (currentScreen == SETTINGS) {
    if (down) {
      beepClick();
      moveCursor(1);
      drawSettings();
    } 
    else if (up) {
      beepClick();
      moveCursor(-1);
      drawSettings();
    } 
    else if (ok) {
      beepConfirm();
      if (selected == 0) {
        cameFromHome = false;
        currentScreen = LOCK_TIME;
        drawLocktime();
      } 
      else if (selected == 1) {
        currentScreen = BRIGHTNESS;
        drawBrightness();
      } 
      else if (selected == 2) {
        currentScreen = SOUNDS;
        drawSounds();
      } 
      else if (selected == 3) {
        currentScreen = SYSTEM;
        drawSystem();
      }
    }
  } 
  else if (currentScreen == LOCK_TIME) {
    if (up && lockTimeHours < 24) {
      lockTimeHours++;
      beepClick();
      saveSettings();
      drawLocktime();
    } 
    else if (down && lockTimeHours > 1) {
      lockTimeHours--;
      beepClick();
      saveSettings();
      drawLocktime();
    } 
    else if (ok) {
      beepConfirm();
      saveSettings();
      if (cameFromHome) startLock();
      else goSettings();
    }
  } 
  else if (currentScreen == BRIGHTNESS) {
    if (up && brightness < 100) {
      brightness += 10;
      beepClick();
      saveSettings();
      drawBrightness();
    } 
    else if (down && brightness > 10) {
      brightness -= 10;
      beepClick();
      saveSettings();
      drawBrightness();
    }
  } 
  else if (currentScreen == SOUNDS) {
    if (up) {
      soundsOn = true;
    }
    else if (down) {
      soundsOn = false;
    }
    else if (ok) {
      soundsOn = !soundsOn;
    }
    else {
      return;
    }

    saveSettings();
    beepClick();
    drawSounds();
  }

  if (!back) {
    return;
  }
  beepClick();

  if (currentScreen == SETTINGS || currentScreen == STATS || currentScreen == ABOUT) {
    goHome();
  }
  else if (currentScreen == LOCK_TIME && cameFromHome) {
    goHome();
  }
  else if (currentScreen == LOCK_TIME || currentScreen == BRIGHTNESS || currentScreen == SOUNDS || currentScreen == SYSTEM) {
    goSettings();
  }
}
