#include "home.h"
#include "globals.h"
#include "graphics.h"
#include "ui.h"

void drawHome() {
  drawBackground();
  tft.pushImage(10, 62, 136, 184, image_byte_idle_pixels);

  drawTitle("READY!");
  drawMenuRow("Lock Phone", 0);
  drawMenuRow("Stats", 1);
  drawMenuRow("Settings", 2);
  drawMenuRow("About", 3);
  drawArrow();
  drawBatteryIcon();
}
