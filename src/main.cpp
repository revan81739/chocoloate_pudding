#include <Arduino.h>
#include "encoder.h"
#include "display.h"
#include "config.h"
#include "state.h"
MacropadState state;






// Used so we only redraw when needed
bool screenNeedsUpdate = true;



void setup() {

  Serial.begin(115200);

  encoderInit();

  displayInit();
  

  drawVolumeScreen();
}

void loop() {

    encoderUpdate();

    if (encoderMovedClockwise()) {

        if (state.volume < 100) {
            state.volume++;
            screenNeedsUpdate = true;
        }

    }

    if (encoderMovedCounterClockwise()) {

        if (state.volume > 0) {
            state.volume--;
            screenNeedsUpdate = true;
        }

    }

    if (encoderButtonPressed()) {

        state.muted = !state.muted;
        screenNeedsUpdate = true;

    }

    if (screenNeedsUpdate) {

        drawVolumeScreen();
        screenNeedsUpdate = false;

    }

    delay(2);

}