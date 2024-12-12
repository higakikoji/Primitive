#include <windows.h>
#include <stdlib.h>
#include "p_printf.h"
#include "p_scanf.h"
#include "p_create_directory.h"
#include "p_get_files.h"
#include "p_process_start.h"

static void test_p_printf(int argc, char *argv[], char *envp[]) {
  return;
}

static void test_p_scanf(int argc, char *argv[], char *envp[]) {
  return;
}

static void test_p_create_directory(int argc, char *argv[], char *envp[]) {
  return;
}

static void test_p_get_files(int argc, char *argv[], char *envp[]) {
  const char *path = "C:\\users\\pakkun\\data";
  const char *extension = "csv";
  int count = p_get_file_count(path, extension, 1);
  if (count < 0) {
    return;
  }
  p_printf(NULL, "%d\n", count);

  char **files = (char **)malloc(sizeof(char *) * count);
  if (files == NULL) {
    return;
  }

  int ret = 0;
  int alocated_count = 0;
  do {
    for (alocated_count = 0; alocated_count < count; alocated_count++) {
      files[alocated_count] = (char *)malloc(sizeof(char) * _MAX_PATH);
      if (files[alocated_count] == NULL) {
        break;
      }
    }
    count = p_get_files(path, extension, 1, files, _MAX_PATH);
    for (int i = 0; i < alocated_count; i++) {
      p_printf(NULL, "%s\n", files[i]);
    }
  } while (0);

  for (int i = 0; i < alocated_count; i++) {
    free(files[i]);
  }
  free(files);
  return;
}

static void test_p_create_process(int argc, char *argv[], char *envp[]) {
  int ret = p_process_start(NULL, "notepad.exe", 0);
  p_printf(NULL, "ret: %d\n", ret);
  return;
}

static void (*functions[])(int argc, char *argv[], char *envp[]) = {
  test_p_printf,
  test_p_scanf,
  test_p_create_directory,
  test_p_get_files,
  test_p_create_process
};

#if defined(_CONSOLE)
int main(int argc, char *argv[], char *envp[]) {
#else
int WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line, _In_ int show_cmd) {
#endif
  int func_count = sizeof(functions) / sizeof(void (*)(int, char**, char**));
  int num;
  do {
    p_printf(NULL,
      "[1] p_printf\n"
      "[2] p_scanf\n"
      "[3] p_create_directory\n"
      "[4] p_get_files\n"
      "[5] p_create_process\n"
      "[0] Exit\n");
    p_printf(NULL, "Command: ");
    p_scanf(NULL, "%d", &num);
    p_printf(NULL, "=> %d\n", num);
    if ((num > 0) && (num <= func_count)) {
#if defined(_CONSOLE)
      functions[num - 1](argc, argv, envp);
#else
      functions[num - 1](__argc, __argv, NULL);
#endif
    }
  } while (num > 0);
  return 0;
}
