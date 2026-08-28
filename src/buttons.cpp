#include "buttons.h"

#include <Arduino.h>
#include "config.h"

static bool previousState[NUM_BUTTONS];
static bool pressedEvent[NUM_BUTTONS];

void buttonsInit() {

    for (int i = 0; i < NUM_BUTTONS; i++) {

        pinMode(buttonPins[i], INPUT_PULLUP);

        previousState[i] = digitalRead(buttonPins[i]);

        pressedEvent[i] = false;

    }

}

void buttonsUpdate() {

    for (int i = 0; i < NUM_BUTTONS; i++) {

        bool currentState = digitalRead(buttonPins[i]);

        pressedEvent[i] = false;

        if (previousState[i] == HIGH && currentState == LOW) {
            pressedEvent[i] = true;
        }

        previousState[i] = currentState;

    }

}

bool buttonPressed(int index) {

    if (index < 0 || index >= NUM_BUTTONS)
        return false;

    return pressedEvent[index];

}