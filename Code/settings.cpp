#include "settings.h"
#include "globals.h"
#include "graphics.h"
#include "hardware.h"
#include "ui.h"

void drawSettings() {
  drawBackground();
  tft.pushImage(1, 46, 152, 184, image_byte_happy_copy_1_pixels);

  drawTitle("SETTINGS");
  drawMenuRow("Lock Time", 0);
  drawMenuRow("Brightness", 1);
  drawMenuRow("Sounds", 2);
  drawMenuRow("System", 3);
  drawArrow();
  drawBatteryIcon();
}

void drawLocktime() {
  drawBackground();
  tft.pushImage(7, 31, 192, 208, image_Tamagotchi_Lockbox_UI_Image_Jul_27_2026__2__copy_1_pixels);

  drawTitle("LOCK TIME");
  String label = String(lockTimeHours) + (lockTimeHours == 1 ? " hour" : " hours");
  drawBody(label, 176, 139, 3);
  drawBody("+", 230, 107, 3);
  drawBody("-", 230, 171, 3);
  drawBody(cameFromHome ? "OK to lock" : "OK to save", 183, 210, 1);
  drawBatteryIcon();
}

void drawBrightness() {
  updateBrightness();

  drawBackground();
  tft.pushImage(7, 31, 192, 208, image_Tamagotchi_Lockbox_UI_Image_Jul_27_2026__2__copy_1_pixels);

  drawTitle("BRIGHTNESS");
  drawBody(String(brightness) + "%", 202, 143, 3);
  drawBody("+", 229, 112, 3);
  drawBody("-", 229, 174, 3);
  drawBatteryIcon();
}

void drawSounds() {
  drawBackground();
  tft.pushImage(7, 31, 192, 208, image_Tamagotchi_Lockbox_UI_Image_Jul_27_2026__2__copy_1_pixels);

  drawTitle("SOUNDS");

  tft.setTextSize(3);
  tft.setTextColor(soundsOn ? title_color : main_color, bg_color);
  tft.drawString("ON", 165, 141);
  tft.setTextColor(soundsOn ? main_color : title_color, bg_color);
  tft.drawString("OFF", 245, 141);

  drawBody("__", soundsOn ? 165 : 245, 170, 3);
  drawBatteryIcon();
}

void drawSystem() {
  drawBackground();
  tft.pushImage(10, 62, 136, 184, image_byte_idle_copy_1_pixels);

  drawTitle("SYSTEM");
  drawBody("Lock " + String(lockTimeHours) + "h", 175, 90, 2);
  drawBody("Bright " + String(brightness) + "%", 175, 120, 2);
  drawBody(soundsOn ? "Sound ON" : "Sound OFF", 175, 150, 2);
  drawBody("Locks " + String(lockCount), 175, 180, 2);
  drawBatteryIcon();
}

void drawAbout() {
  drawBackground();
  tft.pushImage(10, 62, 136, 184, image_byte_idle_copy_1_pixels);

  drawTitle("ABOUT");
  drawBody("Made By", 191, 81, 2);
  drawBody("Harry", 203, 110, 2);
  drawBody("Fanouriakis", 167, 139, 2);
  drawBody("___", 214, 161, 2);
  drawBody("MIT License", 166, 190, 2);
  drawBatteryIcon();
}
