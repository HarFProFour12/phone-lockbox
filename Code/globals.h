#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

extern const uint16_t bg_color;
extern const uint16_t title_color;
extern const uint16_t main_color;

extern const int upPin;
extern const int downPin;
extern const int okPin;
extern const int backPin;
extern const int solenoidPin;
extern const int backlightPin;
extern const int buzzerPin;
extern const int batteryPin;

extern const unsigned long idleTimeoutMs;
extern unsigned long lastActivityMs;
extern bool screenAsleep;

extern int selected;
extern int arrowY;
extern int brightness;
extern int lockTimeHours;
extern int batteryPercent;
extern bool phone_locked;
extern bool soundsOn;

extern bool cameFromHome;

extern unsigned long lockStartMs;
extern unsigned long lockDurationMs;
extern unsigned long lastLockDrawMs;

extern unsigned int lockCount;
extern unsigned long totalLockSeconds;

enum Screen {
  HOME,
  SETTINGS,
  STATS,
  ABOUT,
  LOCK_TIME,
  SOUNDS,
  BRIGHTNESS,
  SYSTEM,
  LOCKED
};

extern Screen currentScreen;

void loadSettings();
void saveSettings();
void saveLockProgress();
unsigned long lockRemainingMs();

#endif
