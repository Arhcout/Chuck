#include "TransformCmp.h"
#include "ECS.h"
#include "Error.h"
#include <assert.h>
#include <map.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static hashmap *components;

void InitTransformComponents() {
  components = hashmap_create();
  if (!components) {
    SetError(ERROR_LV);
    ERROR("Can't initialize Transforms!\n");
  }
}

Transform *AddTransformComponent(Entity *entity) {
  Transform *new = malloc(sizeof(Transform));
  MALLOC_CHECK(new, NULL);
  hashmap_set(components, entity, sizeof(Entity), (uintptr_t)new);
  return new;
}

static int FreeTransform(const void *key, size_t keysize, uintptr_t component,
                         void *usr) {
  Transform *cmp = (Transform *)component;
  if (!cmp)
    return 1;
  free(cmp);
  return 0;
}

void RemoveTransformComponent(Entity *entity) {
  assert(entity);
  int err = hashmap_set_free(components, entity, sizeof(uint64_t),
                             (uintptr_t)NULL, FreeTransform, NULL);
  if (err != 0) {
    WARNING("Entity %lx doesn't have a Transform to remove!\n",
            (uintptr_t)*entity);
    SetError(WARNING_LV);
  }
}

bool HasTransformComponent(Entity *entity) {
  uintptr_t out;
  return hashmap_get(components, entity, sizeof(Entity), &out);
}

Transform *GetTransformComponent(Entity *entity) {
  uintptr_t out;
  hashmap_get(components, entity, sizeof(Entity), &out);
  return (void *)out;
}

static int UpdateTransform(const void *key, size_t keysize, uintptr_t component,
                           void *usr) {
  const Entity *entity = key;
  Transform *cmp = (Transform *)component;
  if (!cmp->enabled) {
    return 0;
  }
  LOG("Transform:\n\
\tentity %lx\n\
\tpos: %f, %f\n\
\tscale: %f, %f\n\
\trotation: %f\n\
\tlayer %d\n\n",
      *entity, cmp->pos.x, cmp->pos.y, cmp->scale.x, cmp->scale.y,
      cmp->rotation, cmp->layer);
  return 0;
}

void UpdateTransformSystem() {
  hashmap_iterate(components, UpdateTransform, NULL);
}
