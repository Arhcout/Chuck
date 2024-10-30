#pragma once
#include <SDL3/SDL.h>

typedef struct SubTexture_s {
  SDL_Texture *atlas;
  SDL_FRect src;
} SubTexture;

void InitSubTextures();
void UninitSubTextures();
void RegisterSubtexture(SubTexture *sub, const char *key, size_t keySize);
const SubTexture *GetSubtexture(const char *key, size_t keySize);
