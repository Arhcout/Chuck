#pragma once
#include "ECS.h"
#include <math.h>

typedef struct Scene_s {
  void **cmps;
  Entity **owner;
} Scene;

#define DESERIAL_VECF2(obj, field, res)                                        \
  {                                                                            \
    cJSON *vec = cJSON_GetObjectItemCaseSensitive((obj), (field));             \
    if (!cJSON_IsObject(vec)) {                                                \
      ERROR("\"%s\" sould be an object\n", (field));                           \
      (res) = VECF2_ZERO;                                                      \
    } else {                                                                   \
      cJSON *x = cJSON_GetObjectItemCaseSensitive((vec), "x");                 \
      cJSON *y = cJSON_GetObjectItemCaseSensitive((vec), "y");                 \
      if (!cJSON_IsNumber(x) || !cJSON_IsNumber(y)) {                          \
        ERROR("\"x\" and \"y\" sould be numbers\n");                           \
        (res) = VECF2_ZERO;                                                    \
      } else {                                                                 \
        (res) = (Vecf2){x->valuedouble, y->valuedouble};                       \
      }                                                                        \
    }                                                                          \
  }

#define DESERIAL_STRING(obj, field, res)                                       \
  {                                                                            \
    cJSON *value = cJSON_GetObjectItemCaseSensitive((obj), (field));           \
    if (!cJSON_IsString(value)) {                                              \
      ERROR("\"%s\" sould be a number\n", (field));                            \
      (res) = NULL;                                                            \
    } else {                                                                   \
      (res) = value->valuestring;                                              \
    }                                                                          \
  }

#define DESERIAL_FLOAT(obj, field, res)                                        \
  {                                                                            \
    cJSON *value = cJSON_GetObjectItemCaseSensitive((obj), (field));           \
    if (!cJSON_IsNumber(value)) {                                              \
      ERROR("\"%s\" sould be a number\n", (field));                            \
      (res) = NAN;                                                             \
    } else {                                                                   \
      (res) = value->valuedouble;                                              \
    }                                                                          \
  }

#define DESERIAL_INT(obj, field, res)                                          \
  {                                                                            \
    cJSON *value = cJSON_GetObjectItemCaseSensitive((obj), (field));           \
    if (!cJSON_IsNumber(value)) {                                              \
      ERROR("\"%s\" sould be a number\n", (field));                            \
      (res) = 0;                                                               \
    } else {                                                                   \
      (res) = value->valueint;                                                 \
    }                                                                          \
  }

#define DESERIAL_BOOL(obj, field, res)                                         \
  {                                                                            \
    cJSON *value = cJSON_GetObjectItemCaseSensitive((obj), (field));           \
    if (!cJSON_IsBool(value)) {                                                \
      ERROR("\"%s\" sould be a bool\n", (field));                              \
      (res) = false;                                                           \
    } else {                                                                   \
      (res) = cJSON_IsTrue(value);                                             \
    }                                                                          \
  }

void DestroyScene(Scene *scene);
Scene *ReadScene(const char *path);
void LoadScene(Scene *scene);
