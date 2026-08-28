#include "encoder.h"

#include <Arduino.h>
#include "config.h"

static int lastCLKState;
static bool lastButtonState = HIGH;

static bool clockwiseEvent = false;
static bool counterClockwiseEvent = false;
static bool buttonEvent = false;

void encoderInit() {

    pinMode(CLK_PIN, INPUT_PULLUP);
    pinMode(DT_PIN, INPUT_PULLUP);
    pinMode(SW_PIN, INPUT_PULLUP);

    lastCLKState = digitalRead(CLK_PIN);

}

void encoderUpdate() {

    clockwiseEvent = false;
    counterClockwiseEvent = false;
    buttonEvent = false;

    int currentCLK = digitalRead(CLK_PIN);

    if (currentCLK != lastCLKState && currentCLK == LOW) {

        if (digitalRead(DT_PIN) != currentCLK) {
            clockwiseEvent = true;
        } else {
            counterClockwiseEvent = true;
        }

    }

    lastCLKState = currentCLK;

    bool currentButtonState = digitalRead(SW_PIN);

    if (lastButtonState == HIGH && currentButtonState == LOW) {
        buttonEvent = true;
    }

    lastButtonState = currentButtonState;

}

bool encoderMovedClockwise() {
    return clockwiseEvent;
}

bool encoderMovedCounterClockwise() {
    return counterClockwiseEvent;
}

bool encoderButtonPressed() {
    return buttonEvent;
}