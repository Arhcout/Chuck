#include "Atlas.h"
#include "Context.h"
#include "Files.h"
#include "Renderer.h"
#include "SubTexture.h"
#include <Array.h>
#include <Error.h>
#include <SDL3_image/SDL_image.h>
#include <assert.h>
#include <map.h>
#include <stdlib.h>

#define CHECK_CURSOR                                                           \
  if (*cursor == '\0') {                                                       \
    WARNING("Malformed .atlas\n");                                             \
    SetError(WARNING_LV);                                                      \
    return;                                                                    \
  }

static SDL_Texture *registeredAtlas;

static void _ParseSubtextures(SDL_Texture *atlas, char *atlasInfo,
                              size_t infoSize) {
  char *cursor = atlasInfo;
  while (*cursor != '\n' && *cursor != '\0') {
    cursor++;
  }
  CHECK_CURSOR
  cursor++;

  while (*cursor != '\0') {

    char *key = malloc(512);
    memset(key, 0, 512);
    size_t keySize = 0;
    while (*cursor != '\t' && keySize < 512 && *cursor != '\0') {
      key[keySize] = *cursor;
      keySize++;
      cursor++;
    }

    CHECK_CURSOR;
    if (keySize == 512) {
      WARNING("filename of %512s might be too long\n", key);
    }
    key = realloc(key, keySize + 1);

    SubTexture *val = malloc(sizeof(SubTexture));

    cursor++;
    val->src.x = atoi(cursor);

    while (*cursor != '\t' && *cursor != '\0') {
      cursor++;
    }
    CHECK_CURSOR;
    cursor++;
    val->src.y = atoi(cursor);

    while (*cursor != '\t' && *cursor != '\0') {
      cursor++;
    }
    CHECK_CURSOR;
    cursor++;
    val->src.w = atoi(cursor);

    while (*cursor != '\t' && *cursor != '\0') {
      cursor++;
    }
    CHECK_CURSOR;
    cursor++;
    val->src.h = atoi(cursor);

    val->atlas = atlas;

    RegisterSubtexture(val, key, keySize);

    while (*cursor != '\n' && *cursor != '\0') {
      cursor++;
    }
    CHECK_CURSOR;
    cursor++;
  }
}
#undef CHECK_CURSOR

void ReadAtlas(const char *atlasName) {
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

  SDL_Texture *atlas = CreateTexture(atlasImg);
  SDL_DestroySurface(atlasImg);

  _ParseSubtextures(atlas, atlasInfo, infoSize);
  ArrayPush(registeredAtlas, atlas);

  return;

file_name_to_long:
  WARNING("File name '%s' is to long!\n", atlasName);
  SetError(WARNING_LV);
  return;

file_read_fail:
  WARNING("Can't read atlas: %s\n", atlasName);
  SetError(WARNING_LV);
  return;
}

void UninitAtlas() { DestroyArray(registeredAtlas); }
void InitAtlas() { registeredAtlas = InitArray(SDL_Texture, 4); }
