#include "ECS.h"
#include "Error.h"
#include "UUID.h"
#include <openssl/sha.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG

#include <Array.h>
Entity *entitieIDArray;

#endif
Entity *CreateEntity(const char *name, size_t nameLen) {
  Entity *e = malloc(sizeof(Entity));
  MALLOC_CHECK(e, NULL);
  unsigned char tmp[20];
  SHA1((const unsigned char *)name, nameLen, tmp);
  *e = *(Entity *)tmp;

#ifdef DEBUG
  ArrayPush(entitieIDArray, e);
#endif
  return e;
}

void DestroyEntity(Entity *entity) {
  assert(entity);
  RemoveAllComponents(entity);
  free(entity);
}

#define GarantiRemoveCmp(type, entity)                                                             \
  if (Has##type##Component((entity))) {                                                            \
    Remove##type##Component(entity);                                                               \
  }
void RemoveAllComponents(Entity *entity) {
  assert(entity);
  GarantiRemoveCmp(Transform, entity);
  GarantiRemoveCmp(Sprite, entity);
  GarantiRemoveCmp(Script, entity);
}
#undef GarantiRemoveCmp

bool HasComponent(Entity *entity, int type) {
  assert(entity);
  switch (type) {
  case TRANSFORM_CMP:
    return HasTransformComponent(entity);
  case SPRITE_CMP:
    return HasSpriteComponent(entity);
  case SCRIPT_CMP:
    return HasScriptComponent(entity);
  }
  WARNING("TODO: Add support for cmp type: %d\n", type);
  return false;
}

void InitComponents() {
#ifdef DEBUG
  entitieIDArray = InitArray(Entity, 8);
#endif
  InitTransformComponents();
  InitSpriteComponents();
  InitScriptComponents();
}

void UninitComponents() {
  UninitTransformComponents();
  UninitSpriteComponents();
  UninitScriptComponents();
}

void UpdateSystems() {
  UpdateTransformSystem();
  UpdateSpriteSystem();
  UpdateScriptSystem();
}

#ifdef DEBUG
Entity *GetAllEntitieIDs() { return entitieIDArray; }
#endif
