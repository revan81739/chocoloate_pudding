#include <Arduino.h>
#include "buttons.h"
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
  buttonsInit();
  displayInit();
  

  drawVolumeScreen();
}

void loop() {

    encoderUpdate();
    buttonsUpdate();

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

    for (int i = 0; i < NUM_BUTTONS; i++) {

    if (buttonPressed(i)) {

        Serial.print("Button ");
        Serial.print(i + 1);
        Serial.println(" pressed");

    }



    if (screenNeedsUpdate) {

        drawVolumeScreen();
        screenNeedsUpdate = false;

    }

    delay(2);

}
}