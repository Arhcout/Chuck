#include "Atlas.h"
#include "Audio.h"
#include "ECS.h"
#include "Input.h"
#include "Renderer.h"
#include "SubTexture.h"
#include "Time.h"
#include "VM.h"
#include <Error.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <time.h>

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    ERROR("Can't init SDL3: %s\n", SDL_GetError());
    return 1;
  }

  if (!IMG_Init(IMG_INIT_PNG)) {
    ERROR("Can't init SDL3_image: %s\n", SDL_GetError());
    return 1;
  }

  if (InitAudio() < 0) {
    ERROR("Can't init SDL3_mixer: %s\n", SDL_GetError());
    return 1;
  }

  InitAtlas();
  InitSubTextures();

  InitRenderer();
  if (GetError() == ERROR_LV) {
    return 1;
  }

  InitComponents();
  if (GetError() == ERROR_LV) {
    return 1;
  }

  InitVM();

  Audio *music = LoadAudio("testlevel/snd/Dogcheck.wav");

  ReadAtlas("/test/atlas/test");

  Entity *a = CreateEntity();
  Transform *tr = AddComponent(a, Transform);
  tr->pos.x = 1;
  tr->pos.y = 1;
  tr->scale.x = 1;
  tr->scale.y = 1.12344;
  tr->rotation = 0;
  tr->layer = 10;

  Sprite *spr = AddComponent(a, Sprite);
  spr->offset = (Vecf2){100, 100};
  spr->rotation = 0;
  spr->scale = (Vecf2){2, 2};
  spr->enabled = true;
  spr->tex = GetSubtexture("mtgnes", sizeof("mtgnes") - 1);

  Script *script = AddComponent(a, Script);
  LoadScript(script, a, "test/scripts/test.lua");
  if (GetError() == ERROR_LV) {
    ERROR("Can't load script!\n");
    return 1;
  }
  script->enabled = true;

  bool running = true;

  time_t seconds = time(NULL);
  uint32_t frameCount = 0;
  clock_t start, end;
  PlayAudio(music, 100, true);

  while (running) {
    start = clock();
    if (difftime(time(NULL), seconds) >= 1.0f) {
      LOG("FPS: %u\n", frameCount);
      frameCount = 0;
      seconds = time(NULL);
    }
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

    UpdateSystems();
    Render();
    frameCount++;
    end = clock();
    e_deltaTime = (double)(end - start) / CLOCKS_PER_SEC;
  }

  DestroyEntity(a);
  DestroyAudio(music);

  UninitVM();
  UninitAtlas();
  UninitSubTextures();
  UninitRenderer();
  UninitAudio();

  IMG_Quit();
  SDL_Quit();

  return 0;
}
