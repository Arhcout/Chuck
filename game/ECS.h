#pragma once
#include <stdbool.h>
#include <stdint.h>
typedef uint64_t Entity;
#include "SpriteCmp.h"
#include "TransformCmp.h"

#define AddComponent(entity, type) Add##type##Component(entity)
#define RemoveComponent(entity, type) Remove##type##Component(entity)
#define GetComponent(entity, type) Get##type##Component(entity)
#define HasComponent(entity, type) Has##type##Component(entity)

// Set error
void InitComponents();

Entity *CreateEntity();
void DestroyEntity(Entity *entity);

void UpdateSystems();
