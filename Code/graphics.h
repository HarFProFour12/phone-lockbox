#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Arduino.h>

extern const unsigned char PROGMEM image_battery_full_bits[];
extern const uint16_t PROGMEM image_byte_idle_pixels[];
extern const unsigned char PROGMEM image_Pin_arrow_right_bits[];
extern const uint16_t PROGMEM image_byte_happy_copy_1_pixels[];
extern const uint16_t PROGMEM image_byte_sad_pixels[];
extern const uint16_t PROGMEM image_Tamagotchi_Lockbox_UI_Image_Jul_27_2026__2__copy_1_pixels[];
extern const uint16_t PROGMEM image_byte_celebrating_pixels[];

#define image_byte_excited_pixels image_byte_happy_copy_1_pixels
#define image_Pin_arrow_right_copy_1_bits image_Pin_arrow_right_bits
#define image_byte_idle_copy_1_pixels image_byte_idle_pixels

#endif
