#ifndef CONFIG_H
#define CONFIG_H

// ----------------------
// Encoder
// ----------------------
const int CLK_PIN = 1;
const int DT_PIN  = 2;
const int SW_PIN  = 3;

// ----------------------
// OLED
// ----------------------
const int OLED_SDA = 11;
const int OLED_SCL = 12;

constexpr int OLED_WIDTH = 128;
constexpr int OLED_HEIGHT = 64;

// ----------------------
// Buttons
// ----------------------
const int NUM_BUTTONS = 10;

const int buttonPins[NUM_BUTTONS] = {
  4,
  5,
  6,
  7,
  15,
  16,
  17,
  18,
  8,
  9
};

#endif