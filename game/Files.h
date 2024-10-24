#pragma once
#include <stddef.h>

// Engines path is like this: dir/file.ext (root dir is the place where the
// executable is located)
char *GetOSPath(const char *epath);
char *ReadFile(const char *epath, size_t *size);
