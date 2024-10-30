#pragma once
#include "ECS.h"
#include "Vec.h"

typedef struct {
  Vecf2 pos;
  Vecf2 scale;
  float rotation;
  int layer;
  bool enabled;
} Transform;

Transform *AddTransformComponent(Entity *entity);
void RemoveTransformComponent(Entity *entity);
bool HasTransformComponent(Entity *entity);
Transform *GetTransformComponent(Entity *entity);

void InitTransformComponents();
void UpdateTransformSystem();
