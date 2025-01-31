#include "Input.h"
#include <Error.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const bool *_keys;
static bool *_prevKeys;
static int _numKeys;

void InitInput() {
  _keys = SDL_GetKeyboardState(&_numKeys);
  _prevKeys = malloc(_numKeys * sizeof(bool));
}

void UninitInput() {
  assert(_prevKeys);
  free(_prevKeys);
}

void InputPoll() {
  memcpy(_prevKeys, _keys, _numKeys * sizeof(bool));
  SDL_PumpEvents();
}

bool IsKeyDown(SDL_Scancode key) { return _keys[key]; }

bool IsKeyPressed(SDL_Scancode key) { return !_prevKeys[key] && _keys[key]; }

void GetMousePosition(Vecf2 *out_mousePos) {
  assert(out_mousePos != NULL);
  SDL_GetMouseState(&out_mousePos->x, &out_mousePos->y);
}

bool GetButtonState(enum MouseButtons button) {
  return SDL_GetMouseState(NULL, NULL) == (uint32_t)SDL_BUTTON_MASK(button);
}
