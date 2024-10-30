#include "ECS.h"
#include "Error.h"
#include "UUID.h"
#include <stdint.h>
#include <stdlib.h>

Entity *CreateEntity() {
  Entity *e = malloc(sizeof(Entity));
  MALLOC_CHECK(e, NULL);
  *e = GenerateUUID();
  return e;
}

#define GarantiRemoveCmp(type, entity)                                         \
  if (Has##type##Component((entity))) {                                        \
    Remove##type##Component(entity);                                           \
  }
void DestroyEntity(Entity *entity) {
  GarantiRemoveCmp(Transform, entity);
  GarantiRemoveCmp(Sprite, entity);
  free(entity);
}
#undef GarantiRemoveCmp

void InitComponents() {
  InitTransformComponents();
  InitSpriteComponents();
}

void UpdateSystems() {
  UpdateTransformSystem();
  UpdateSpriteSystem();
}
