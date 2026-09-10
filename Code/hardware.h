#ifndef HARDWARE_H
#define HARDWARE_H

void initDisplay();
void initPins();
void pulseSolenoid();
void updateBrightness();
void updateBattery();
void sleepScreen();
void wakeScreen();
void checkIdleSleep();

void beepClick();
void beepConfirm();
void beepLockStart();
void beepUnlock();
void beepCancel();

#endif
