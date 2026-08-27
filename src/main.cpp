#include <Arduino.h>
#include "display.h"
#include "config.h"
#include "state.h"
MacropadState state;








int lastCLKState;

// Used so we only redraw when needed
bool screenNeedsUpdate = true;



void setup() {

  Serial.begin(115200);

  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);

  lastCLKState = digitalRead(CLK_PIN);

  displayInit();
  

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