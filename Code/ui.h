#ifndef UI_H
#define UI_H

#include <Arduino.h>

void drawBackground();
void drawTitle(const char* text);
void drawBody(const String& text, int x, int y, int size);
void drawMenuRow(const char* text, int row);
void drawArrow();
void drawBatteryIcon();

#endif
