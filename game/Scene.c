#include "Scene.h"
#include "Atlas.h"
#include "ECS.h"
#include "Files.h"
#include <Array.h>
#include <Error.h>
#include <cjson/cJSON.h>
#include <stdlib.h>

void DestroyScene(Scene *scene) {
  DestroyArray(scene->cmps);
  DestroyArray(scene->owner);
  free(scene);
}

Scene *ReadScene(const char *path) {
  size_t sz = 0;
  char *content = ReadFile(path, &sz);
  if (!content) {
    ERROR("Can't open scene '%s'\n", path);
    SetError(ERROR_LV);
    return NULL;
  }
  cJSON *json = cJSON_Parse(content);
  if (json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      ERROR("JSON parsing failed: %s\n", error_ptr);
    }
    cJSON_Delete(json);
    free(content);
    return NULL;
  }

  Scene *scene = malloc(sizeof(Scene));
  MALLOC_CHECK(scene, NULL);
  scene->cmps = InitArray(void *, 4);
  MALLOC_CHECK(scene->cmps, NULL);
  scene->owner = InitArray(Entity *, 4);
  MALLOC_CHECK(scene->cmps, NULL);

  cJSON *entities = cJSON_GetObjectItemCaseSensitive(json, "entities");
  if (!cJSON_IsArray(entities)) {
    ERROR("\"entities\" sould be an array\n");
    goto error;
  }

  cJSON *entity = NULL;
  cJSON_ArrayForEach(entity, entities) {
    if (!cJSON_IsObject(entity)) {
      ERROR("\"entities\" sould only contain objects\n");
      goto error;
    }

    Entity *eid = CreateEntity();

    cJSON *cmps = cJSON_GetObjectItemCaseSensitive(entity, "cmps");

    cJSON *cmp;
    cJSON_ArrayForEach(cmp, cmps) {
      if (!cJSON_IsObject(cmp)) {
        ERROR("\"cmps\" sould only contain objects\n");
        goto error;
      }

      cJSON *type = cJSON_GetObjectItemCaseSensitive(cmp, "type");
      if (!cJSON_IsNumber(type)) {
        ERROR("\"type\" sould be a number\n");
        goto error;
      }
      void *component = NULL;

      LOG("type: %d\n", type->valueint);

      CmpFnOnTypeWithRes(Deserialize, type->valueint, component, cmp, eid);
      if (!component) {
        ERROR("Can't desieralize component\n");
        goto error;
      }
      LOG("EID: %lu\n", *eid);
      ArrayPushI(scene->cmps, component);
      ArrayPushI(scene->owner, eid);
    }
  }

  assert(GetArrayLen(scene->cmps) == GetArrayLen(scene->owner));

  return scene;
error:
  ERROR("Can't parse scene '%s'\n", path);
  cJSON_Delete(json);
  DestroyScene(scene);
  free(content);
  return NULL;
}

void LoadScene(Scene *scene) {
  assert(scene);
  assert(scene->owner);
  assert(scene->cmps);
  for (int i = 0; i < GetArrayLen(scene->cmps); i++) {
    void *cmp = scene->cmps[i];
    LOG("type: %u\n", *(unsigned *)cmp);

    CmpFnOnType(Register, *(unsigned *)cmp, scene->owner[i], cmp);
  }
}
