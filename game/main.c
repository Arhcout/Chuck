#include "ECS.h"
#include "Input.h"
#include "Renderer.h"
#include <Error.h>
#include <SDL3/SDL.h>

int main() {

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    ERROR("Can't init SDL3: %s\n", SDL_GetError());
    return 1;
  }

  InitRenderer();
  if (GetError() == ERROR_LV) {
    return 1;
  }

  InitComponents();
  if (GetError() == ERROR_LV) {
    return 1;
  }

  Entity *a = CreateEntity();
  Transform *tr = AddComponent(a, Transform);
  tr->pos.x = 10;
  tr->pos.y = 10.12344;
  tr->scale.x = 10;
  tr->scale.y = 10.12344;
  tr->rotation = 14.43253;
  tr->layer = 10;

  bool running = true;

  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_EVENT_QUIT:
        running = false;
        break;

      case SDL_EVENT_KEY_UP:
      case SDL_EVENT_KEY_DOWN:
        InputPoll(&e);
        break;
      }
    }

    // UpdateSystems();
    Render();
  }
  return 0;
}
