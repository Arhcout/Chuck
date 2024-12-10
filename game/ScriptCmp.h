#pragma once
#include "ECS.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct Script_s {
  unsigned type;
  int functionTableRef;
  int envRef;
  bool enabled;
} Script;

Script *AddScriptComponent(Entity *entity);
void RegisterScriptComponent(Entity *entity, Script *cmp);
void RemoveScriptComponent(Entity *entity);
bool HasScriptComponent(Entity *entity);
Script *GetScriptComponent(Entity *entity);

Script *DeserializeScriptComponent(cJSON *component, Entity *eid);

void InitScriptComponents();
void UninitScriptComponents();
void UpdateScriptSystem();
