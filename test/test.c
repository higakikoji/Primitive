#include <vcruntime.h>
#include <stdlib.h>
#include "p_get_files.h"
#include "p_printf.h"

int main(int argc, char *argv[]) {
  const char *path = "C:\\users\\pakkun\\data";
  const char *extension = "csv";
  int ret = p_get_file_counta(path, extension, 1);
  p_printfa(NULL, "%d\n", ret);

  char **files = (char **)malloc(sizeof(char *) * ret);
  for (int i = 0; i < ret; i++) {
    files[i] = (char *)malloc(sizeof(char) * _MAX_PATH);
  }
  int index = 0;
  ret = p_get_filesa(path, extension, 1, &index, files);
  for (int i = 0; i < ret; i++) {
    p_printfa(NULL, "%s\n", files[i]);
  }
  for (int i = 0; i < ret; i++) {
    free(files[i]);
  }
  free(files);
  return 0;
}
