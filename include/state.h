#ifndef STATE_H
#define STATE_H

struct MacropadState {

  int volume = 50;

  bool muted = false;

};

extern MacropadState state;

#endif