#include "keypad.h"

/// @ingroup Keypad
/// @{

struct Keypad {
  KeyState keystates[KeyButtons_SIZE];
};

Keypad g_Keypad;

Keypad* Keypad_Init() {
  // TODO! Init
  return &g_Keypad;
}

KeyState Keypad_GetState(Keypad* keypad, KeyButtons key) { return Unpressed; }

/// @}
