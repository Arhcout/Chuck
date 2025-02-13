#pragma once

#define MAX_FILENAME 1024

// Check OS
#if defined(_WIN32)
#define CH_WINDOWS 1
#elif defined(__linux__)
#define CH_LINUX 1
#else
#error Operating system not supported sry
#endif

#if defined(CH_LINUX)
#define CH_DIR_SEP '/'
#elif defined(CH_WINDOWS)
#define CH_DIR_SEP '\\'
#endif
