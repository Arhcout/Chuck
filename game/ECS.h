#pragma once
#include <cjson/cJSON.h>
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

#define NUM_CMP_TYPE 3

// if no return value use 'void' for res
#define CmpFnOnTypeWithRes(fn, type, res, ...)                                                     \
  switch ((type)) {                                                                                \
  case TRANSFORM_CMP:                                                                              \
    (res) = fn##TransformComponent(__VA_ARGS__);                                                   \
    break;                                                                                         \
  case SPRITE_CMP:                                                                                 \
    (res) = fn##SpriteComponent(__VA_ARGS__);                                                      \
    break;                                                                                         \
  case SCRIPT_CMP:                                                                                 \
    (res) = fn##ScriptComponent(__VA_ARGS__);                                                      \
    break;                                                                                         \
  }

#define CmpFnOnType(fn, type, ...)                                                                 \
  switch ((type)) {                                                                                \
  case TRANSFORM_CMP:                                                                              \
    fn##TransformComponent(__VA_ARGS__);                                                           \
    break;                                                                                         \
  case SPRITE_CMP:                                                                                 \
    fn##SpriteComponent(__VA_ARGS__);                                                              \
    break;                                                                                         \
  case SCRIPT_CMP:                                                                                 \
    fn##ScriptComponent(__VA_ARGS__);                                                              \
    break;                                                                                         \
  }

// Set error
void InitComponents();

Entity *CreateEntity(const char *name, size_t nameLen);
void DestroyEntity(Entity *entity);
void RemoveAllComponents(Entity *entity);
bool HasComponent(Entity *entity, int type);

void UpdateSystems();

void UninitComponents();

#ifdef DEBUG
Entity *GetAllEntitieIDs();
#endif
