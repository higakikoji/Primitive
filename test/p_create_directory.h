#pragma once

#include <vcruntime.h>

#if defined(_MBCS)
#define p_create_directory p_create_directorya
#else
#define p_create_directory p_create_directoryw
#endif

int p_create_directorya(const char *const path);

int p_create_directoryw(const wchar_t *const path);
