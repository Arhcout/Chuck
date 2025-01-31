#include "Atlas.h"
#include "Audio.h"
#include "ECS.h"
#include "Input.h"
#include "Renderer.h"
#include "Scene.h"
#include "SubTexture.h"
#include "Time.h"
#include "VM.h"
#include <Error.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <time.h>

#ifdef DEBUG
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_SDL3
#define CIMGUI_USE_SDL_RENDERER3
#include <cimgui.h>
#include <cimgui_impl.h>
#endif

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    ERROR("Can't init SDL3: %s\n", SDL_GetError());
    return 1;
  }

  if (InitAudio() < 0) {
    ERROR("Can't init SDL3_mixer: %s\n", SDL_GetError());
    return 1;
  }

  InitAtlas();
  InitSubTextures();

  InitRenderer(800 * 1.5, 600 * 1.5);
  if (GetError() == ERROR_LV) {
    return 1;
  }

  InitComponents();
  if (GetError() == ERROR_LV) {
    return 1;
  }

  InitInput();

  InitVM();

  // Audio *music = LoadAudio("testlevel/snd/Dogcheck.wav");

  ReadAtlas("/test/atlas/test");

#ifdef DEBUG
  ImGuiContext *ctx = igCreateContext(NULL);
  ImGuiIO *io = igGetIO();

  ImGui_ImplSDL3_InitForSDLRenderer(GetWindow(), GetRenderer());
  ImGui_ImplSDLRenderer3_Init(GetRenderer());

  igStyleColorsDark(NULL);
#endif

  /*Entity *a = CreateEntity();*/
  /*Transform *tr = AddComponent(a, Transform);*/
  /*tr->pos.x = 1;*/
  /*tr->pos.y = 1;*/
  /*tr->scale.x = 1;*/
  /*tr->scale.y = 1.12344;*/
  /*tr->rotation = 0;*/
  /*tr->layer = 10;*/
  /**/
  /*Sprite *spr = AddComponent(a, Sprite);*/
  /*spr->offset = (Vecf2){100, 100};*/
  /*spr->rotation = 0;*/
  /*spr->scale = (Vecf2){2, 2};*/
  /*spr->enabled = true;*/
  /*spr->tex = GetSubtexture("mtgnes", sizeof("mtgnes") - 1);*/
  /**/
  /*Script *script = AddComponent(a, Script);*/
  /*LoadScript(script, a, "test/scripts/test.lua");*/
  /*if (GetError() == ERROR_LV) {*/
  /*  ERROR("Can't load script!\n");*/
  /*  return 1;*/
  /*}*/
  /*script->enabled = true;*/

  Scene *scene = ReadScene("test/scene.json");
  LoadScene(scene);

  bool running = true;

  time_t seconds = time(NULL);
  uint32_t frameCount = 0;
  clock_t start, end;
  // PlayAudio(music, 100, true);

  while (running) {
    start = clock();
    if (difftime(time(NULL), seconds) >= 1.0f) {
      LOG("FPS: %u\n", frameCount);
      frameCount = 0;
      seconds = time(NULL);
    }
    SDL_Event e;
    InputPoll();
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_EVENT_QUIT:
        running = false;
        break;
      }
#ifdef DEBUG
      ImGui_ImplSDL3_ProcessEvent(&e);
#endif
    }

    UpdateSystems();
    Render();
    frameCount++;
    end = clock();
    e_deltaTime = (double)(end - start) / CLOCKS_PER_SEC;
  }

#ifdef DEBUG
  ImGui_ImplSDL3_Shutdown();
  ImGui_ImplSDLRenderer3_Shutdown();
#endif

  // DestroyEntity(a);
  // DestroyAudio(music);

  UninitVM();
  UninitAtlas();
  UninitSubTextures();
  UninitRenderer();
  UninitAudio();
  UninitInput();

  SDL_Quit();

  return 0;
}
