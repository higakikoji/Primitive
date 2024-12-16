#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include "p_printf.h"
#include "p_scanf.h"
#include "p_create_directory.h"
#include "p_get_files.h"
#include "p_process_start.h"

#define P_UT_FUNCTION_NAME_INDEX (5)
#define P_UT_P_PRINTFA_TEST_STR ("abcdefghijklmnopqrstuvwxyz")

static void test_p_printf(int argc, TCHAR *argv[], TCHAR *envp[]) {
  if (argc == 1) {
    int ret = 0;
    size_t format_size = strlen(P_UT_P_PRINTFA_TEST_STR);
    p_printf(NULL,
      TEXT("Start a unit test of the %s function\n")
      TEXT("  (1) Multiple byte charactor set test\n")
      TEXT("  (1-1) When NULL is specified for \"locale\"\n")
      TEXT("  (1-1-1) When NULL is specified for \"format\"\n")
      TEXT("          %sa(NULL, NULL);\n"), &__FUNCTION__[P_UT_FUNCTION_NAME_INDEX], &__FUNCTION__[P_UT_FUNCTION_NAME_INDEX]);
    //ret = p_printfa(NULL, NULL);
    p_printf(NULL,
      TEXT("          Skip\n")
      TEXT("  (1-1-2) When all alphabet letters (%s: %d bytes) is specified for \"format\"\n")
      TEXT("          %sa(NULL, \"%s\");\n"), P_UT_P_PRINTFA_TEST_STR, format_size, &__FUNCTION__[P_UT_FUNCTION_NAME_INDEX], P_UT_P_PRINTFA_TEST_STR);
    ret = p_printfa(NULL, P_UT_P_PRINTFA_TEST_STR);
    p_printf(NULL, TEXT("\n"));
    if (ret == format_size) {
      p_printf(NULL, TEXT("          return value is %d: OK\n"), ret);
    } else {
      p_printf(NULL, TEXT("          NG"));
    }
    p_printf(NULL,
      TEXT("  (2) Wide charactor set test\n")
      TEXT("  (2-1) %sw(NULL, NULL);\n"), &__FUNCTION__[P_UT_FUNCTION_NAME_INDEX]);
    //ret = p_printfw(NULL, NULL);
    p_printf(NULL,
      TEXT("        Skip\n"));
    p_printf(NULL,
      TEXT("End all OK\n\n"));
  } else if ((argc >= 4) && (argc <= 5)) {
    int ret = 0;
    if (argv[2][0] == 'a') {
      if (argv[3][0] == 'n') {
        //if (strstr)
        ret = p_printfa(NULL, argv[4]);
      } else {
        //ret = p_printfa(argv[3], )
      }
    } else if (argv[2][0] == 'w') {

    } else {

    }
  } else {
    p_printf(NULL,
      TEXT("p_printf function test:\n")
      TEXT("  (1) test.exe\n")
      TEXT("      Automatically run unit tests if no arguments are specified\n")
      TEXT("  (2) test.exe <charactor set> <locale> <format> [<argument>]\n")
      TEXT("      Check any parameter\n")
      TEXT("      <charactor set> a: Use the p_printfa function\n")
      TEXT("                      w: Use the p_printfw function\n")
      TEXT("                      t: Use the p_printf macro (depends on the system\n")
      TEXT("      <locale>        Specify string if locale is used, such as 'ja_jp', 'en_us' ...\n")
      TEXT("                      Specify 'n' if locale is not used\n")
      TEXT("      <format>        Specify any format string\n")
      TEXT("      [<argument>]    Specify any argument\n\n"));
  }
  return;
}

static void test_p_scanf(int argc, TCHAR *argv[], TCHAR *envp[]) {
  return;
}

static void test_p_create_directory(int argc, TCHAR *argv[], TCHAR *envp[]) {
  return;
}

static void test_p_get_files(int argc, TCHAR *argv[], TCHAR *envp[]) {
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

static void test_p_create_process(int argc, TCHAR *argv[], TCHAR *envp[]) {
  int ret = p_process_start(NULL, "notepad.exe", 0);
  p_printf(NULL, "ret: %d\n", ret);
  return;
}

static void (*functions[])(int argc, TCHAR *argv[], TCHAR *envp[]) = {
  test_p_printf,
  test_p_scanf,
  test_p_create_directory,
  test_p_get_files,
  test_p_create_process
};

#if defined(_CONSOLE)
int _tmain(int argc, TCHAR *argv[], TCHAR *envp[]) {
#else
int _tWinMain(HINSTANCE instance, HINSTANCE prev_instance, LPTSTR cmd_line, int show_cmd) {
#endif
  int func_count = sizeof(functions) / sizeof(void (*)(int, TCHAR*, TCHAR*));
  int num;
  do {
    p_printf(NULL,
      "[1] p_printf\n"
      "[2] p_scanf\n"
      "[3] p_create_directory\n"
      "[4] p_get_files\n"
      "[5] p_create_process\n"
      "[6] p_compress\n"
      "[7] p_decompress\n"
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
