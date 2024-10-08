#pragma once
#include <stdint.h>
typedef uint64_t Entity;
#include "TransformCmp.h"

#define AddComponent(entity, type) Add##type##Component(entity)
#define RemoveComponent(entity, type) Remove##type##Component(entity)

// Set error
void InitComponents();

Entity *CreateEntity();
void DestroyEntity(Entity *entity);

void UpdateSystems();
