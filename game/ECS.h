#pragma once
#include <stdbool.h>
#include <stdint.h>
typedef uint64_t Entity;
#include "ScriptCmp.h"
#include "SpriteCmp.h"
#include "TransformCmp.h"

#define AddComponent(entity, type) Add##type##Component(entity)
#define RemoveComponent(entity, type) Remove##type##Component(entity)
#define GetComponent(entity, type) Get##type##Component(entity)

#define TRANSFORM_CMP 0
#define SPRITE_CMP 1
#define SCRIPT_CMP 2

// Set error
void InitComponents();

Entity *CreateEntity();
void DestroyEntity(Entity *entity);
void RemoveAllComponents(Entity *entity);
bool HasComponent(Entity *entity, int type);

void UpdateSystems();

void UninitComponents();
