#pragma once
#include "ECS.h"
#include "Vec.h"
#include <cjson/cJSON.h>

typedef struct {
  unsigned type;
  Vecf2 pos;
  Vecf2 scale;
  float rotation;
  int layer;
  bool enabled;
} Transform;

Transform *AddTransformComponent(Entity *entity);
void RegisterTransformComponent(Entity *entity, Transform *cmp);
void RemoveTransformComponent(Entity *entity);
bool HasTransformComponent(Entity *entity);
Transform *GetTransformComponent(Entity *entity);

Transform *DeserializeTransformComponent(cJSON *component, Entity *eid);
// TODO Serialization

void InitTransformComponents();
void UninitTransformComponents();
void UpdateTransformSystem();
