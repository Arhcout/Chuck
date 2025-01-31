#include "Renderer.h"
#include "ECS.h"
#include "Queue.h"
#include <Error.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

static SDL_Renderer *ren;
static SDL_Window *win;

static Queue *renderQueue;

#ifdef DEBUG
#include "Input.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_SDL3
#define CIMGUI_USE_SDL_RENDERER3
#include "Editor.h"
#include <cimgui.h>
#include <cimgui_impl.h>

#endif

void InitRenderer(int w, int h) {
  win = SDL_CreateWindow("Chuck", w, h, SDL_WINDOW_RESIZABLE);
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

  renderQueue = CreateQueue(sizeof(Entity), 16);
  if (!renderQueue) {
    ERROR("Can't create renderQueue");
    return;
  }
}

SDL_Window *GetWindow() { return win; }

SDL_Renderer *GetRenderer() { return ren; }

void UninitRenderer() {
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  DestroyQueue(renderQueue);
}

void RegisterEntityToRender(const Entity *entity) {
  Enqueue(renderQueue, entity);
}

void Render() {
  SDL_SetRenderDrawColor(ren, 172, 222, 134, 255);
  SDL_RenderClear(ren);

  Entity *entity = 0;
  while ((entity = Dequeue(renderQueue))) {
    Transform *tr = GetComponent(entity, Transform);
    Sprite *spr = GetComponent(entity, Sprite);

    SDL_FRect dest;
    dest.x = tr->pos.x + spr->offset.x;
    dest.y = tr->pos.y + spr->offset.y;
    dest.w = spr->tex->src.w * tr->scale.x * spr->scale.x;
    dest.h = spr->tex->src.h * tr->scale.y * spr->scale.y;
    SDL_RenderTextureRotated(ren, spr->tex->atlas, &spr->tex->src, &dest,
                             tr->rotation + spr->rotation, NULL, SDL_FLIP_NONE);
    free(entity);
  }
#ifdef DEBUG
  ImGui_ImplSDL3_NewFrame();
  ImGui_ImplSDLRenderer3_NewFrame();
  igNewFrame();
  static bool showEditor = true;
  if (IsKeyPressed(SDL_SCANCODE_F3))
    showEditor = !showEditor;

  if (showEditor)
    RenderEditor();

  igRender();
  ImGui_ImplSDLRenderer3_RenderDrawData(igGetDrawData(), ren);
#endif

  SDL_RenderPresent(ren);
}

SDL_Texture *CreateTexture(SDL_Surface *surface) {
  return SDL_CreateTextureFromSurface(ren, surface);
}
