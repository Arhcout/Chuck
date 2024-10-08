#pragma once
#include "ECS.h"
#include "Vec.h"

typedef struct {
  Vecf2 pos;
  Vecf2 scale;
  float rotation;
  int layer;
} Transform;

Transform *AddTransformComponent(Entity *entity);
void RemoveTransformComponent(Entity *entity);

void InitTransformComponents();
void UpdateTransformSystem();
