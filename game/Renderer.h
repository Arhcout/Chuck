#pragma once
#include "ECS.h"
#include <SDL3/SDL.h>

// Set error
void InitRenderer(int w, int h);
void UninitRenderer();
void Render();
SDL_Window *GetWindow();
SDL_Renderer *GetRenderer();

void RegisterEntityToRender(const Entity *entity);
SDL_Texture *CreateTexture(SDL_Surface *surface);
