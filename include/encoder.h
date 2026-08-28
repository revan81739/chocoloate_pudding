#ifndef ENCODER_H
#define ENCODER_H

void encoderInit();
void encoderUpdate();

bool encoderMovedClockwise();
bool encoderMovedCounterClockwise();
bool encoderButtonPressed();

#endif