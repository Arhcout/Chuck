#pragma once
#include <SDL3/SDL.h>

typedef struct SubTexture_s {
  SDL_Texture *atlas;
  SDL_Rect src;
} SubTexture;

SubTexture *CreateSubTexture(SDL_Texture *atlas, SDL_Rect src);
