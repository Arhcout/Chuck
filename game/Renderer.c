#include "Renderer.h"
#include "ECS.h"
#include "Queue.h"
#include <Error.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

static SDL_Renderer *ren;
static SDL_Window *win;

static Queue *renderQueue;

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

  renderQueue = CreateQueue(sizeof(Entity), 16);
  if (!renderQueue) {
    ERROR("Can't create renderQueue");
    return;
  }
}

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

  SDL_RenderPresent(ren);
}

SDL_Texture *CreateTexture(SDL_Surface *surface) {
  return SDL_CreateTextureFromSurface(ren, surface);
}
