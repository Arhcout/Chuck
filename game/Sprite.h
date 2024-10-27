#pragma once
#include "SubTexture.h"
#include "Vec.h"

typedef struct Sprite_s {
  SubTexture *tex;
  Vecf2 offset;
  Vecf2 scale;
  float rotation;
} Sprite;

typedef struct SpriteCreateInfo_s {
  const char *textureName;
  Vecf2 offset;
  Vecf2 scale;
  float rotation;
} SpriteCreateInfo;

Sprite *CreateSprite(SpriteCreateInfo *info);
