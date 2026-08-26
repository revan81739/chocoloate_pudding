#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"
#include "state.h"
MacropadState state;




Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);



int lastCLKState;

// Used so we only redraw when needed
bool screenNeedsUpdate = true;

void drawVolumeScreen() {

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Volume");

  // Percentage
  display.setTextSize(2);
  display.setCursor(0,16);

  if (state.muted) {
    display.print("MUTED");
  } else {
    display.print(state.volume);
    display.print("%");
  }

  // Outline
  display.drawRect(10, 50, 108, 10, SSD1306_WHITE);

  // Filled section
  int barWidth = map(state.volume, 0, 100, 0, 106);

  if (!state.muted) {
    display.fillRect(11, 51, barWidth, 8, SSD1306_WHITE);
  }

  display.display();
}

void setup() {

  Serial.begin(115200);

  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);

  lastCLKState = digitalRead(CLK_PIN);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }

  drawVolumeScreen();
}

void loop() {

  int currentCLK = digitalRead(CLK_PIN);

  // Encoder rotated
  if (currentCLK != lastCLKState && currentCLK == LOW) {

    if (digitalRead(DT_PIN) != currentCLK) {

      if (state.volume < 100)
        state.volume++;

    } else {

      if (state.volume > 0)
        state.volume--;

    }

    screenNeedsUpdate = true;
  }

  lastCLKState = currentCLK;

  // Encoder button
  static bool lastButtonState = HIGH;

  bool currentButtonState = digitalRead(SW_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {

    state.muted = !state.muted;
    screenNeedsUpdate = true;

  }

  lastButtonState = currentButtonState;

  if (screenNeedsUpdate) {

    drawVolumeScreen();
    screenNeedsUpdate = false;

  }

  delay(2);

}