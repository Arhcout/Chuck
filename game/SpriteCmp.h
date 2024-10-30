#pragma once
#include "ECS.h"
#include "SubTexture.h"
#include "Vec.h"

typedef struct Sprite_s {
  Vecf2 offset;
  Vecf2 scale;
  const SubTexture *tex;
  float rotation;
  bool enabled;
} Sprite;

Sprite *AddSpriteComponent(Entity *entity);
void RemoveSpriteComponent(Entity *entity);
bool HasSpriteComponent(Entity *entity);
Sprite *GetSpriteComponent(Entity *entity);

void InitSpriteComponents();
void UpdateSpriteSystem();
