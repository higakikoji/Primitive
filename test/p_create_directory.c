#include <shlobj_core.h>
#include "p_create_directory.h"

int p_create_directorya(const char *const path) {
  return SHCreateDirectoryExA(NULL, path, NULL);
}

int p_create_directoryw(const wchar_t *const path) {
  return SHCreateDirectoryExW(NULL, path, NULL);
}
