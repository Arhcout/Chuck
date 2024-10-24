#include "Utils.h"
#include <stddef.h>
#include <string.h>

void ReplaceChar(char t, char c, char *str, size_t maxLen) {
  size_t l = strlen(str);
  for (int i = 0; i < l && i < maxLen; i++) {
    if (str[i] == t) {
      str[i] = c;
    }
  }
}
