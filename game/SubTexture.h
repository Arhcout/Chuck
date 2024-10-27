#pragma once
#include <SDL3/SDL.h>

typedef struct SubTexture_s {
  SDL_Texture *atlas;
  SDL_Rect src;
} SubTexture;

void InitSubTextures();
void UninitSubTextures();
void RegisterSubtexture(SubTexture *sub, const char *key, size_t keySize);
const SubTexture *GetSubtexture(const char *key, size_t keySize);
