#include "TransformCmp.h"
#include "ECS.h"
#include "Error.h"
#include "Scene.h"
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

void UninitTransformComponents() {
  assert(components);
  hashmap_free(components);
}

Transform *AddTransformComponent(Entity *entity) {
  Transform *new = malloc(sizeof(Transform));
  MALLOC_CHECK(new, NULL);
  hashmap_set(components, entity, sizeof(Entity), (uintptr_t)new);
  new->type = TRANSFORM_CMP;
  return new;
}

void RegisterTransformComponent(Entity *entity, Transform *cmp) {
  assert(entity);
  assert(cmp);
  hashmap_set(components, entity, sizeof(Entity), (uintptr_t)cmp);
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
  return 0;
}

void UpdateTransformSystem() {
  hashmap_iterate(components, UpdateTransform, NULL);
}

Transform *DeserializeTransformComponent(cJSON *component, Entity *eid) {
  (void)eid;
  assert(component);
  Transform *t = malloc(sizeof(Transform));
  MALLOC_CHECK(t, NULL);

  DESERIAL_VECF2(component, "pos", t->pos);
  DESERIAL_VECF2(component, "scale", t->scale);
  DESERIAL_FLOAT(component, "rotation", t->rotation);
  DESERIAL_INT(component, "layer", t->layer);
  DESERIAL_BOOL(component, "enabled", t->enabled);

  t->type = TRANSFORM_CMP;

  LOG("\ntransform:\n\tpos: %f %f\n\tscale: %f %f\n\trotation: %f\n\tlayer: "
      "%d\n\tenabled: %d\n",
      t->pos.x, t->pos.y, t->scale.x, t->scale.y, t->rotation, t->layer,
      t->enabled);

  return t;
}
