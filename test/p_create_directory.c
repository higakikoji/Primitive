#include <shlobj_core.h>
#include "p_create_directory.h"

int p_create_directory(struct p_directory_t directory) {
  /* https://learn.microsoft.com/ja-jp/windows/win32/api/shlobj_core/nf-shlobj_core-shcreatedirectoryexa */
  return SHCreateDirectoryExA(directory.wnd, directory.path, NULL);
}
