#include "SubTexture.h"
#include "Error.h"
#include <stdlib.h>

SubTexture *CreateSubTexture(SDL_Texture *atlas, SDL_Rect src) {
  assert(atlas);
  SubTexture *sb = malloc(sizeof(SubTexture));
  MALLOC_CHECK(sb, NULL);
  sb->src = src;
  sb->atlas = atlas;
  return sb;
}
