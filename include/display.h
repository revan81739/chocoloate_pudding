#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

// The OLED display object (defined in display.cpp)
extern Adafruit_SSD1306 display;

// Initializes the OLED
void displayInit();

// Draws the volume screen
void drawVolumeScreen();

#endif