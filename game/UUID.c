#include "UUID.h"
#include <Error.h>
#include <stdint.h>
#include <stdio.h>

#if defined(CH_WINDOWS)
uint64_t GenerateUUID_Win() {
#error TODO GenerateUUID_Win
}
#elif defined(CH_LINUX)
uint64_t GenerateUUID_Linux() {
  FILE *f = fopen("/dev/random", "r");
  if (!f) {
    ERROR("Can't open /dev/random!\n");
    SetError(ERROR_LV);
    return 0;
  }
  uint64_t res;
  fread(&res, sizeof(uint64_t), 1, f);
  return res;
}
#endif
