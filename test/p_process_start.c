#include <windows.h>
#include <memory.h>
#include "p_process_start.h"

int p_process_starta(const char *application_name, char *command_line, DWORD creationFlags) {
  STARTUPINFOA si;
  memset(&si, 0, sizeof(si));
  si.cb = sizeof(si);
  PROCESS_INFORMATION pi;
  memset(&pi, 0, sizeof(pi));
  BOOL ret = CreateProcessA(application_name, command_line, NULL, NULL, FALSE, creationFlags, NULL, NULL, &si, &pi);
  if (ret == 0) {
    return -1;
  }
  WaitForSingleObject(pi.hProcess, INFINITE);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  return 0;
}

int p_process_startw(const wchar_t *application_name, wchar_t *command_line, DWORD creationFlags) {
  STARTUPINFOW si;
  memset(&si, 0, sizeof(si));
  si.cb = sizeof(si);
  PROCESS_INFORMATION pi;
  memset(&pi, 0, sizeof(pi));
  BOOL ret = CreateProcessW(application_name, command_line, NULL, NULL, FALSE, creationFlags, NULL, NULL, &si, &pi);
  if (ret == 0) {
    return -1;
  }
  WaitForSingleObject(pi.hProcess, INFINITE);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  return 0;
}
