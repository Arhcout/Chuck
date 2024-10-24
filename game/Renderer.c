#include "Renderer.h"
#include <Error.h>
#include <SDL3/SDL.h>

static SDL_Renderer *ren;
static SDL_Window *win;

void InitRenderer() {
  win = SDL_CreateWindow("Chuck", 800, 600, 0);
  if (!win) {
    ERROR("Can't create window: %s\n", SDL_GetError());
    SetError(ERROR_LV);
    return;
  }

  ren = SDL_CreateRenderer(win, NULL);
  if (!ren) {
    ERROR("Can't create renderer: %s\n", SDL_GetError());
    SetError(ERROR_LV);
    return;
  }
}

void UninitRenderer() {
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
}

void Render() {
  SDL_SetRenderDrawColor(ren, 172, 222, 134, 255);
  SDL_RenderClear(ren);

  SDL_RenderPresent(ren);
}

SDL_Texture *CreateTexture(SDL_Surface *surface) {
  return SDL_CreateTextureFromSurface(ren, surface);
}
