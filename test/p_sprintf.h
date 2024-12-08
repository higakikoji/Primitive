#pragma once

#include <vcruntime.h>

#if defined(_MBCS)
#define p_sprintf p_sprintfa
#else
#define p_sprintf p_sprintfw
#endif

int p_sprintfa(char *const buffer, const size_t buffer_count, const size_t max_count, const char *locale, const char *const format, ...);

int p_sprintfw(wchar_t *const buffer, const size_t buffer_count, const size_t max_count, const wchar_t *locale, const wchar_t *const format, ...);
