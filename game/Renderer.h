#pragma once
#include "ECS.h"
#include <SDL3/SDL.h>

// Set error
void InitRenderer();
void UninitRenderer();
void Render();

void RegisterEntityToRender(const Entity *entity);
SDL_Texture *CreateTexture(SDL_Surface *surface);
