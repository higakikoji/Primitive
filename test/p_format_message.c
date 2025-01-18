#include <windows.h>

DWORD p_get_error_stringa(DWORD error, LPSTR buffer, DWORD size) {
  DWORD ret = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, size, NULL);
  return ret;
}

DWORD p_get_error_stringw(DWORD error, LPWSTR buffer, DWORD size) {
  DWORD ret = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, size, NULL);
  return ret;
}
