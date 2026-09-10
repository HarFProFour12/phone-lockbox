#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
public:
  lgfx::Panel_ST7789 _panel_instance;
  lgfx::Bus_SPI       _bus_instance;

  LGFX(void) {
    auto bus_cfg = _bus_instance.config();
    bus_cfg.spi_host = SPI2_HOST;
    bus_cfg.spi_mode = 3;
    bus_cfg.freq_write = 27000000;
    bus_cfg.freq_read  = 20000000;
    bus_cfg.pin_sclk = 5;
    bus_cfg.pin_mosi = 4;
    bus_cfg.pin_miso = -1;
    bus_cfg.pin_dc   = 6;
    _bus_instance.config(bus_cfg);
    _panel_instance.setBus(&_bus_instance);

    auto panel_cfg = _panel_instance.config();
    panel_cfg.pin_cs  = 10;
    panel_cfg.pin_rst = 7;
    panel_cfg.pin_busy = -1;
    panel_cfg.panel_width  = 240;
    panel_cfg.panel_height = 320;
    panel_cfg.invert = true;
    _panel_instance.config(panel_cfg);

    setPanel(&_panel_instance);
  }
};

extern LGFX tft;

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
