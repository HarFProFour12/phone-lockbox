#include "globals.h"
#include <Preferences.h>

TFT_eSPI tft;

const uint16_t bg_color = 0x0883;
const uint16_t title_color = 0xE7D9;
const uint16_t main_color = 0xB6B3;

const int upPin = 15;
const int downPin = 16;
const int okPin = 17;
const int backPin = 18;
const int solenoidPin = 19;
const int backlightPin = 20;
const int buzzerPin = 21;
const unsigned long idleTimeoutMs = 180000UL;
unsigned long lastActivityMs = 0;
bool screenAsleep = false;
const int batteryPin = 34;

int selected = 0;
int arrowY = 102;
int brightness = 100;
int lockTimeHours = 1;
int batteryPercent = 100;
bool phone_locked = false;
bool soundsOn = true;
bool cameFromHome = false;

unsigned long lockStartMs = 0;
unsigned long lockDurationMs = 0;
unsigned long lastLockDrawMs = 0;

unsigned int lockCount = 0;
unsigned long totalLockSeconds = 0;

Screen currentScreen = HOME;

static Preferences prefs;

static int clampInt(int value, int lo, int hi) {
  if (value < lo) {
    return lo;
  }
  if (value > hi) {
    return hi;
  }
  return value;
}

unsigned long lockRemainingMs() {
  if (!phone_locked) {
    return 0;
  }
  unsigned long elapsed = millis() - lockStartMs;
  if (elapsed >= lockDurationMs) {
    return 0;
  }
  return lockDurationMs - elapsed;
}

void loadSettings() {
  prefs.begin("lockbox", false);

  lockTimeHours = clampInt(prefs.getInt("hours", 1), 1, 24);
  brightness = clampInt(prefs.getInt("bright", 100), 10, 100);
  soundsOn = prefs.getBool("sounds", true);
  lockCount = prefs.getUInt("locks", 0);
  totalLockSeconds = prefs.getULong("totalSec", 0);

  unsigned long remainingSec = prefs.getULong("remain", 0);
  if (remainingSec > 0) {
    phone_locked = true;
    currentScreen = LOCKED;
    lockStartMs = millis();
    lockDurationMs = remainingSec * 1000UL;
  }

  prefs.end();
}

void saveSettings() {
  prefs.begin("lockbox", false);
  prefs.putInt("hours", lockTimeHours);
  prefs.putInt("bright", brightness);
  prefs.putBool("sounds", soundsOn);
  prefs.putUInt("locks", lockCount);
  prefs.putULong("totalSec", totalLockSeconds);
  prefs.end();
}

void saveLockProgress() {
  prefs.begin("lockbox", false);
  prefs.putULong("remain", lockRemainingMs() / 1000UL);
  prefs.end();
}
