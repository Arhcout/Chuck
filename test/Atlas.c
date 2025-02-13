#include <Atlas.h>
#include <Error.h>
#include <Renderer.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SubTexture.h>

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    ERROR("Can't init SDL3\n");
    return 1;
  }
  if (!IMG_Init(IMG_INIT_PNG)) {
    ERROR("Can't init SDL3_image\n");
    return 3;
  }
  InitRenderer();
  if (GetError() == ERROR_LV) {
    ERROR("Can't initialize renderer!\n");
    return 4;
  }

  InitAtlas();
  InitSubTextures();

  ReadAtlas("atlas/test");
  if (GetError() != 0) {
    return 2;
  }

  if (!GetSubtexture(hashmap_str_lit("dog"))) {
    return 5;
  }

  UninitSubTextures();
  UninitAtlas();
  UninitRenderer();

  IMG_Quit();
  SDL_Quit();
  return 0;
}
