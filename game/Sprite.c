#include "Sprite.h"
#include <Error.h>
#include <stdlib.h>

Sprite *CreateSprite(SpriteCreateInfo *info) {
  Sprite *spr = malloc(sizeof(Sprite));
  MALLOC_CHECK(spr, NULL);
  spr->scale = info->scale;
  spr->offset = info->offset;
  spr->rotation = info->rotation;
}
