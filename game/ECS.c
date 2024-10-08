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

void DestroyEntity(Entity *entity) {
  // TODO: remove from all components
  free(entity);
}

#define InitCmp(type) Init##type##Components()
void InitComponents() { InitCmp(Transform); }

void UpdateSystems() { UpdateTransformSystem(); }
