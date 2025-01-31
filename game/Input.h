#pragma once
#include "Vec.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

enum MouseButtons {
  MOUSE_LEFT = 1,
  MOUSE_MIDDLE = 2,
  MOUSE_RIGHT = 3,
};

void InitInput();
void UninitInput();

void InputPoll();

bool IsKeyDown(SDL_Scancode key);
bool IsKeyPressed(SDL_Scancode key);
void GetMousePosition(Vecf2 *mousePos);
bool GetButtonState(enum MouseButtons button);
