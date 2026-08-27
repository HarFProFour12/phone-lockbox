#include "stats.h"
#include "globals.h"
#include "graphics.h"
#include "ui.h"

void drawStats() {
  drawBackground();
  tft.pushImage(1, 46, 152, 184, image_byte_happy_copy_1_pixels);

  drawTitle("STATS");

  unsigned long hours = totalLockSeconds / 3600UL;
  unsigned long minutes = (totalLockSeconds % 3600UL) / 60UL;

  drawBody("Locks", 183, 102, 2);
  drawBody(String(lockCount), 183, 122, 2);
  drawBody("Time locked", 183, 152, 2);
  drawBody(String(hours) + "h " + String(minutes) + "m", 183, 172, 2);
  drawBatteryIcon();
}
