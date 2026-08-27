#include "ui.h"
#include "globals.h"
#include "graphics.h"
#include "hardware.h"

void drawBackground() {
  tft.fillScreen(bg_color);
}

void drawTitle(const char* text) {
  tft.setTextColor(title_color, bg_color);
  tft.setTextSize(4);
  tft.drawString(text, 22, 20);
}

void drawBody(const String& text, int x, int y, int size) {
  tft.setTextColor(main_color, bg_color);
  tft.setTextSize(size);
  tft.drawString(text, x, y);
}

void drawMenuRow(const char* text, int row) {
  drawBody(text, 183, 102 + row * 30, 2);
}

void drawArrow() {
  tft.drawBitmap(150, arrowY, image_Pin_arrow_right_bits, 18, 14, main_color);
}

void drawBatteryIcon() {
  updateBattery();
  tft.drawBitmap(253, 21, image_battery_full_bits, 48, 32, title_color);

  int cover = 0;
  if (batteryPercent < 17) cover = 36;
  else if (batteryPercent < 34) cover = 30;
  else if (batteryPercent < 50) cover = 24;
  else if (batteryPercent < 67) cover = 18;
  else if (batteryPercent < 100) cover = 12;

  if (cover > 0) {
    tft.fillRect(262, 26, cover, 19, bg_color);
  }
}
