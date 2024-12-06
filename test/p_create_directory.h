#ifndef P_CREATE_DIRECTORY_H
#define P_CREATE_DIRECTORY_H

struct p_directory_t {
  void *wnd;
  char *path;
  void *security_descriptor;
  int inherit_handle;
};

int p_create_directory(struct p_directory_t directory);

#endif
