#pragma once

#include <vcruntime.h>

#if defined(_MBCS)
#define p_get_file_count p_get_file_counta
#define p_get_files p_get_filesa
#else
#define p_get_file_count p_get_file_countw
#define p_get_files p_get_filesw
#endif

int p_get_file_counta(const char *path, const char *search_extension, unsigned char sub_directory);

int p_get_file_countw(const wchar_t *path, const wchar_t *search_extension, unsigned char sub_directory);

int p_get_filesa(const char *path, const char *search_extension, unsigned char sub_directory, int *index, char *files[]);

int p_get_filesw(const wchar_t *path, const wchar_t *search_extension, unsigned char sub_directory, int *index, wchar_t *files[]);
