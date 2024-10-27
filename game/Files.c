#include "Files.h"
#include "Context.h"
#include "Error.h"
#include <SDL3/SDL.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
// 4 days

char *GetOSPath(const char *epath) {
  const char *base = SDL_GetBasePath();
  assert(base);

  size_t baseSize = strlen(base);

  char *path = calloc(sizeof(char), MAX_FILENAME);
  MALLOC_CHECK(path, NULL);
  strncpy(path, base, MAX_FILENAME);

  strncpy(path + baseSize, epath, MAX_FILENAME - baseSize);
  if (path[MAX_FILENAME - 1] != '\0') {
    ERROR("Combination of:\n\t%s\n\tand:\n\t%s\n\tis to big!\n", base, epath);
    SetError(ERROR_LV);
    free(path);
    path = NULL;
    return NULL;
  }
#if defined(CH_WINDOWS)
#include "Utils.h"
  ReplaceChar('/', '\\', path, MAX_FILENAME);
#endif
  return path;
}

char *ReadFile(const char *epath, size_t *size) {
  assert(epath);
  assert(size);

  char *path = GetOSPath(epath);
  if (GetError() == ERROR_LV) {
    return NULL;
  }

  FILE *f = fopen(path, "r");
  if (!f) {
    WARNING("Can't open file '%s'!\n", path);
    SetError(WARNING_LV);
    free(path);
    return NULL;
  }

  fseek(f, 0L, SEEK_END);
  *size = ftell(f);
  fseek(f, 0L, SEEK_SET);

  char *res = malloc(*size);
  MALLOC_CHECK(res, NULL);

  fread(res, sizeof(char), *size, f);

  free(path);
  path = NULL;
  return res;
}
