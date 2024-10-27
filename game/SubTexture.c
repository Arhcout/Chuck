#include "SubTexture.h"
#include "map.h"
#include <Error.h>
#include <assert.h>
#include <stdlib.h>

static hashmap *subs;

void InitSubTextures() { subs = hashmap_create(); }

int _FreeSubs(const void *key, size_t keySize, uintptr_t val, void *usr) {
  memset((void *)val, 0, sizeof(SubTexture));
  free((void *)val);

  memset((void *)key, 0, keySize);
  free((void *)key);
  return 0;
}

void UninitSubTextures() {
  hashmap_iterate(subs, _FreeSubs, NULL);
  hashmap_free(subs);
}

void RegisterSubtexture(SubTexture *sub, const char *key, size_t keySize) {
  assert(sub);
  assert(subs);

  hashmap_set(subs, key, keySize, (uintptr_t)sub);
}

const SubTexture *GetSubtexture(const char *key, size_t keySize) {
  SubTexture *out = NULL;
  hashmap_get(subs, key, keySize, (uintptr_t *)&out);
  if (!out) {
    WARNING("subtexture: '%s' does not exist.\n", key);
  }
  return out;
}
