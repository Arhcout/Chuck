#pragma once

// Check OS
#if defined(_WIN32)
#define CH_WINDOWS 1
#elif defined(__linux__)
#define CH_LINUX 1
#else
#error Operating system not supported sry
#endif
