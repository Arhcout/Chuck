#pragma once
#include "ECS.h"
#include "SubTexture.h"
#include "Vec.h"

typedef struct Sprite_s {
  unsigned type;
  Vecf2 offset;
  Vecf2 scale;
  const SubTexture *tex;
  float rotation;
  bool enabled;
} Sprite;

Sprite *AddSpriteComponent(Entity *entity);
void RegisterSpriteComponent(Entity *entity, Sprite *cmp);
void RemoveSpriteComponent(Entity *entity);
bool HasSpriteComponent(Entity *entity);
Sprite *GetSpriteComponent(Entity *entity);

Sprite *DeserializeSpriteComponent(cJSON *component, Entity *eid);

void InitSpriteComponents();
void UninitSpriteComponents();
void UpdateSpriteSystem();
