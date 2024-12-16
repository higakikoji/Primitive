#pragma once

#include <vcruntime.h>

#if defined(_MBCS)
#define p_printf p_printfa
#else
#define p_printf p_printfw
#endif

int p_printfa(const char *locale, const char *const format, ...);

int p_printfw(const wchar_t *locale, const wchar_t *const format, ...);
