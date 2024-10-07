#include "Input.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool _keys[322];

void InputPoll(SDL_Event* event){
  assert(event != NULL);

  switch (event->type) {
    case SDL_KEYDOWN:
      _keys[event->key.keysym.sym % 322] = true;
      break;

    case SDL_KEYUP:
      _keys[event->key.keysym.sym % 322] = false;
      break;
  }
}

bool IsKeyDown(SDL_KeyCode key){
  assert(key > 0);
  assert(key < 322);
  return _keys[key];
}

void GetMousePosition(Veci2* out_mousePos){
  assert(out_mousePos != NULL);
  SDL_GetMouseState(&out_mousePos->x, &out_mousePos->y);
}

bool GetButtonState(enum MouseButtons button){
  return SDL_GetMouseState(NULL, NULL) == (uint32_t)SDL_BUTTON(button);
}

