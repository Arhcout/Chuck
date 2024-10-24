#pragma once
#include "SubTexture.h"
#include <SDL3/SDL.h>
#include <map.h>

typedef struct Atlas_s {
  SDL_Texture *tex;
  unsigned w, h;
  const hashmap *subs;
} Atlas;

Atlas *ReadAtlas(const char *file);
void DestroyAtlas(Atlas *atlas);
