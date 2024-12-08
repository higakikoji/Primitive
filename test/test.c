#include <stdlib.h>
#include "p_get_files.h"
#include "p_printf.h"

int main(int argc, char *argv[]) {
  const char *path = "C:\\users\\pakkun\\data";
  const char *extension = "csv";
  int ret = p_get_file_count(path, extension, 1);
  p_printf(NULL, "%d\n", ret);

  char **files = (char **)malloc(sizeof(char *) * ret);
  for (int i = 0; i < ret; i++) {
    files[i] = (char *)malloc(sizeof(char) * 154);
  }
  ret = p_get_files(path, extension, 1, files, 154);
  for (int i = 0; i < ret; i++) {
    p_printf(NULL, "%s\n", files[i]);
  }
  for (int i = 0; i < ret; i++) {
    free(files[i]);
  }
  free(files);
  return 0;
}
