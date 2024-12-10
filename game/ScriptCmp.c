#include "ScriptCmp.h"
#include "ECS.h"
#include "Error.h"
#include "Scene.h"
#include "VM.h"
#include <assert.h>
#include <lauxlib.h>
#include <lua.h>
#include <map.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static hashmap *components;

void InitScriptComponents() {
  components = hashmap_create();
  if (!components) {
    SetError(ERROR_LV);
    ERROR("Can't initialize Scripts!\n");
  }
}

void UninitScriptComponents() {
  assert(components);
  hashmap_free(components);
}

Script *AddScriptComponent(Entity *entity) {
  Script *new = malloc(sizeof(Script));
  MALLOC_CHECK(new, NULL);
  hashmap_set(components, entity, sizeof(Entity), (uintptr_t)new);
  new->type = SCRIPT_CMP;
  return new;
}

void RegisterScriptComponent(Entity *entity, Script *cmp) {
  assert(entity);
  assert(cmp);
  hashmap_set(components, entity, sizeof(Entity), (uintptr_t)cmp);
}

static int FreeScript(const void *key, size_t keysize, uintptr_t component,
                      void *usr) {
  Script *cmp = (Script *)component;
  if (!cmp)
    return 1;
  free(cmp);
  return 0;
}

void RemoveScriptComponent(Entity *entity) {
  assert(entity);
  int err = hashmap_set_free(components, entity, sizeof(uint64_t),
                             (uintptr_t)NULL, FreeScript, NULL);
  if (err != 0) {
    WARNING("Entity %lx doesn't have a Script to remove!\n",
            (uintptr_t)*entity);
    SetError(WARNING_LV);
  }
}

static int UpdateScript(const void *key, size_t keysize, uintptr_t component,
                        void *usr) {
  const Entity *entity = key;
  Script *cmp = (Script *)component;
  if (!cmp->enabled) {
    return 0;
  }
  RunScriptFn(cmp, "Update");

  return 0;
}

void UpdateScriptSystem() { hashmap_iterate(components, UpdateScript, NULL); }

bool HasScriptComponent(Entity *entity) {
  uintptr_t out;
  return hashmap_get(components, entity, sizeof(Entity), &out);
}

Script *GetScriptComponent(Entity *entity) {
  uintptr_t out;
  hashmap_get(components, entity, sizeof(Entity), &out);
  return (void *)out;
}

Script *DeserializeScriptComponent(cJSON *component, Entity *eid) {
  assert(component);
  Script *script = malloc(sizeof(Script));
  MALLOC_CHECK(script, NULL);

  char *path;
  DESERIAL_STRING(component, "path", path);
  DESERIAL_BOOL(component, "enabled", script->enabled);
  script->type = SCRIPT_CMP;

  LoadScript(script, eid, path);
  if (GetError() == ERROR_LV) {
    ERROR("Can't load script!\n");
    return NULL;
  }

  return script;
}
