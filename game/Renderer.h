#pragma once
#include <SDL3/SDL.h>

// Set error
void InitRenderer();
void UninitRenderer();
void Render();

SDL_Texture *CreateTexture(SDL_Surface *surface);
