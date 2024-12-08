#include <vcruntime.h>
#include <stdlib.h>
#include "p_get_files.h"
#include "p_printf.h"

int main(int argc, char *argv[]) {
  const char *path = "C:\\users\\pakkun\\data";
  const char *extension = "csv";
  int count;
  int ret = p_get_file_counta(path, extension, 1, &count);
  p_printfa(NULL, NULL, "%d, %d\n", ret, count);

  char **files = (char **)malloc(sizeof(char *) * count);
  for (int i = 0; i < count; i++) {
    files[i] = (char *)malloc(sizeof(char) * _MAX_PATH);
  }
  int index = 0;
  ret = p_get_filesa(path, extension, 1, &index, files);
  for (int i = 0; i < count; i++) {
    p_printfa(NULL, NULL, "%s\n", files[i]);
  }
  for (int i = 0; i < count; i++) {
    free(files[i]);
  }
  free(files);
  return 0;
}
