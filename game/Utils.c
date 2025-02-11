#include "Utils.h"
#include <stddef.h>
#include <string.h>

bool ManualContainedIn(void *val, void *arr, size_t itemLen, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (memcmp(arr + itemLen * i, arr, itemLen) == 0) {
      return true;
    }
  }
  return false;
}

void ReplaceChar(char t, char c, char *str, size_t maxLen) {
  size_t l = strlen(str);
  for (int i = 0; i < l && i < maxLen; i++) {
    if (str[i] == t) {
      str[i] = c;
    }
  }
}
