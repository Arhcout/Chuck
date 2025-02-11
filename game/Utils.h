#pragma once
#include <stdbool.h>
#include <stddef.h>

#define ContainedIn(val, arr, len) ManualContainedIn((val), (arr), sizeof(typeof(val)), (len))
#define ContainedInI(val, arr, len)                                                                \
  {                                                                                                \
    typeof((val)) __x__ = (val);                                                                   \
    ManualContainedIn(__x__, (arr), sizeof(typeof(val)), (len));                                   \
  }                                                                                                \
  (void)
bool ManualContainedIn(void *val, void *arr, size_t itemLen, size_t len);

// Replace ocurences of t and replace it by char c in string str
void ReplaceChar(char t, char c, char *str, size_t maxLen);
