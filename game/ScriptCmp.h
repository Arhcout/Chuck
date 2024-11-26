#pragma once
#include "ECS.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct Script_s {
  int functionTableRef;
  int envRef;
  bool enabled;
} Script;

Script *AddScriptComponent(Entity *entity);
void RemoveScriptComponent(Entity *entity);
bool HasScriptComponent(Entity *entity);
Script *GetScriptComponent(Entity *entity);

void InitScriptComponents();
void UninitScriptComponents();
void UpdateScriptSystem();
