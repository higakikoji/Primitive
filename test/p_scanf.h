#pragma once

#include <vcruntime.h>

#if defined(_MBCS)
#define p_scanf p_scanfa
#else
#define p_scanf p_scanfw
#endif

int p_scanfa(const char *locale, const char *const format, ...);

int p_scanfw(const wchar_t *locale, const wchar_t *const format, ...);
