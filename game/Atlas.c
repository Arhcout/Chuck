#include "Atlas.h"
#include "Context.h"
#include "Files.h"
#include "Renderer.h"
#include <Error.h>
#include <SDL3_image/SDL_image.h>
#include <assert.h>
#include <ctype.h>
#include <map.h>
#include <stdlib.h>

#define CHECK_CURSOR                                                           \
  if (*cursor == '\0') {                                                       \
    WARNING("Malformed .atlas\n");                                             \
    SetError(WARNING_LV);                                                      \
    atlas->w = 0;                                                              \
    atlas->h = 0;                                                              \
    atlas->tex = NULL;                                                         \
    atlas->subs = NULL;                                                        \
    return;                                                                    \
  }

static void _ParseAtlasInfo(Atlas *atlas, char *atlasInfo, size_t infoSize) {
  char *cursor = atlasInfo;
  // Get resolution
  while (!(isdigit(*cursor) && !(*cursor == '0')) && *cursor != '\0') {
    cursor++;
  }
  CHECK_CURSOR

  atlas->w = atoi(cursor);
  while (isdigit(*cursor) && *cursor != '\0') {
    cursor++;
  }
  CHECK_CURSOR
  atlas->h = atoi(cursor);
  while (isdigit(*cursor) && *cursor != '\0') {
    cursor++;
  }
  CHECK_CURSOR;
  while (*cursor != '\n' && *cursor != '\0') {
    cursor++;
  }
  CHECK_CURSOR;
  cursor++;

  while (*cursor != '\0') {

    char *key = malloc(512);
    memset(key, 0, 512);
    int i = 0;
    while (*cursor != '\t' && i < 512 && *cursor != '\0') {
      key[i] = *cursor;
      i++;
      cursor++;
    }

    CHECK_CURSOR;
    if (i == 512) {
      WARNING("filename of %512s might be too long\n", key);
    }

    SDL_Rect *val = malloc(sizeof(SDL_Rect));

    cursor++;
    val->x = atoi(cursor);

    while (*cursor != '\t' && *cursor != '\0') {
      cursor++;
    }
    CHECK_CURSOR;
    cursor++;
    val->y = atoi(cursor);

    while (*cursor != '\t' && *cursor != '\0') {
      cursor++;
    }
    CHECK_CURSOR;
    cursor++;
    val->w = atoi(cursor);

    while (*cursor != '\t' && *cursor != '\0') {
      cursor++;
    }
    CHECK_CURSOR;
    cursor++;
    val->h = atoi(cursor);

    hashmap_set((hashmap *)atlas->subs, key, 512, (uintptr_t)val);

    while (*cursor != '\n' && *cursor != '\0') {
      cursor++;
    }
    CHECK_CURSOR;
    cursor++;
  }
}
#undef CHECK_CURSOR

Atlas *ReadAtlas(const char *atlasName) {
  assert(atlasName);

  // Get info from atlas name
  char nameFileInfo[MAX_FILENAME] = {0};
  strncpy(nameFileInfo, atlasName, MAX_FILENAME - 1);
  if (nameFileInfo[MAX_FILENAME - 1] != '\0') {
    goto file_name_to_long;
  }
  strncat(nameFileInfo, ".atlas", MAX_FILENAME - 1);
  if (nameFileInfo[MAX_FILENAME - 1] != '\0') {
    goto file_name_to_long;
  }

  size_t infoSize;
  char *atlasInfo = ReadFile(nameFileInfo, &infoSize);
  if (!atlasInfo) {
    goto file_read_fail;
  }

  // Get image from atlas name

  char *nameFileImg = GetOSPath(atlasName);
  strncat(nameFileImg, ".png", strlen(nameFileImg) - 1);
  if (nameFileImg[MAX_FILENAME - 1] != '\0') {
    goto file_name_to_long;
  }

  SDL_Surface *atlasImg;
  atlasImg = IMG_Load(nameFileImg);
  if (!atlasImg) {
    WARNING("SDL Image IMG_LoadFailed: %s\n", SDL_GetError());
    goto file_read_fail;
  }
  free(nameFileImg);

  Atlas *atlas = malloc(sizeof(Atlas));
  MALLOC_CHECK(atlas, NULL);
  atlas->tex = CreateTexture(atlasImg);
  SDL_DestroySurface(atlasImg);

  atlas->subs = hashmap_create();

  _ParseAtlasInfo(atlas, atlasInfo, infoSize);

  return atlas;
file_name_to_long:
  WARNING("File name '%s' is to long!\n", atlasName);
  SetError(WARNING_LV);
  return NULL;

file_read_fail:
  WARNING("Can't read atlas: %s\n", atlasName);
  SetError(WARNING_LV);
  return NULL;
}

int _FreeSubs(const void *key, size_t keySize, uintptr_t val, void *usr) {
  memset((void *)val, 0, sizeof(SDL_Rect));
  free((void *)val);

  memset((void *)key, 0, keySize);
  free((void *)key);
  return 0;
}

void DestroyAtlas(Atlas *atlas) {
  assert(atlas);
  SDL_DestroyTexture(atlas->tex);
  hashmap_iterate((hashmap *)atlas->subs, _FreeSubs, NULL);
  hashmap_free((hashmap *)atlas->subs);
  memset(atlas, 0, sizeof(Atlas));
  free(atlas);
}
