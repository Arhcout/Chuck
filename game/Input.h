#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Error.h"
#include "Vec.h"

enum MouseButtons{
  MOUSE_LEFT = 1,
  MOUSE_MIDDLE = 2,
  MOUSE_RIGHT = 3,
};

void InputPoll(SDL_Event* event);

bool IsKeyDown(SDL_KeyCode key);
void GetMousePosition(Veci2* mousePos);
bool GetButtonState(enum MouseButtons button);
