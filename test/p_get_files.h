#ifndef P_GET_FILES_H
#define P_GET_FILES_H

int p_get_file_counta(const char *path, const char *search_extension, unsigned char sub_directory, int *count);

int p_get_file_countw(const unsigned short *path, const unsigned short *search_extension, unsigned char sub_directory, int *count);

int p_get_filesa(const char *path, const char *search_extension, unsigned char sub_directory, int *index, char *files[]);

int p_get_filesw(const unsigned short *path, const unsigned short *search_extension, unsigned char sub_directory, int *index, unsigned short *files[]);

#endif
