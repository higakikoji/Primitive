#include <shlobj_core.h>
#include "p_create_directory.h"

int p_create_directory(const char *path) {
  return SHCreateDirectoryExA(NULL, path, NULL);
}
