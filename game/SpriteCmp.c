#include "SpriteCmp.h"
#include "ECS.h"
#include "Error.h"
#include "Renderer.h"
#include "Time.h"
#include <assert.h>
#include <map.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static hashmap *components;

void InitSpriteComponents() {
  components = hashmap_create();
  if (!components) {
    SetError(ERROR_LV);
    ERROR("Can't initialize Sprites!\n");
  }
}

void UninitSpriteComponents() {
  assert(components);
  hashmap_free(components);
}

Sprite *AddSpriteComponent(Entity *entity) {
  Sprite *new = malloc(sizeof(Sprite));
  MALLOC_CHECK(new, NULL);
  hashmap_set(components, entity, sizeof(Entity), (uintptr_t)new);
  return new;
}

static int FreeSprite(const void *key, size_t keysize, uintptr_t component,
                      void *usr) {
  Sprite *cmp = (Sprite *)component;
  if (!cmp)
    return 1;
  free(cmp);
  return 0;
}

void RemoveSpriteComponent(Entity *entity) {
  assert(entity);
  int err = hashmap_set_free(components, entity, sizeof(uint64_t),
                             (uintptr_t)NULL, FreeSprite, NULL);
  if (err != 0) {
    WARNING("Entity %lx doesn't have a Sprite to remove!\n",
            (uintptr_t)*entity);
    SetError(WARNING_LV);
  }
}

bool HasSpriteComponent(Entity *entity) {
  uintptr_t out;
  return hashmap_get(components, entity, sizeof(Entity), &out);
}

Sprite *GetSpriteComponent(Entity *entity) {
  uintptr_t out;
  hashmap_get(components, entity, sizeof(Entity), &out);
  return (void *)out;
}

static int UpdateSprite(const void *key, size_t keysize, uintptr_t component,
                        void *usr) {
  const Entity *entity = key;
  Sprite *cmp = (Sprite *)component;
  if (!cmp->enabled) {
    return 0;
  }
  static double theta = 0;
  theta += e_deltaTime;
  cmp->rotation += 50.0f * e_deltaTime;
  cmp->scale.x = sin(theta) * 2;
  RegisterEntityToRender(entity);
  return 0;
}

void UpdateSpriteSystem() { hashmap_iterate(components, UpdateSprite, NULL); }
