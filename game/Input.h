#pragma once
#include "Vec.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

enum MouseButtons {
  MOUSE_LEFT = 1,
  MOUSE_MIDDLE = 2,
  MOUSE_RIGHT = 3,
};

void InputPoll(SDL_Event *event);

bool IsKeyDown(SDL_Keycode key);
void GetMousePosition(Vecf2 *mousePos);
bool GetButtonState(enum MouseButtons button);
