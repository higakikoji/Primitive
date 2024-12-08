#include <stdlib.h>
#include "p_get_files.h"
#include "p_printf.h"

int main(int argc, char *argv[]) {
  const char *path = "C:\\users\\pakkun\\data";
  const char *extension = "csv";
  int count = p_get_file_count(path, extension, 1);
  if (count < 0) {
    return -1;
  }
  p_printf(NULL, "%d\n", count);

  char **files = (char **)malloc(sizeof(char *) * count);
  if (files == NULL) {
    return -1;
  }

  int ret = 0;
  int alocated_count = 0;
  do {
    for (alocated_count = 0; alocated_count < count; alocated_count++) {
      files[alocated_count] = (char *)malloc(sizeof(char) * _MAX_PATH);
      if (files[alocated_count] == NULL) {
        ret = -1;
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

  return ret;
}
