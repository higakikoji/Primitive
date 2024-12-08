#include <windows.h>
#include <string.h>
#include <shlwapi.h>
#include "p_sprintf.h"
#include "p_get_files.h"

#pragma comment (lib, "shlwapi.lib")

#define P_WILD_CARDA ("*")
#define P_WILD_CARDW (L"*")
#define P_WILD_CARD_LENGTH (1)
#define P_CURRENT_DIRECTORYA (".")
#define P_CURRENT_DIRECTORYW (L".")
#define P_CURRENT_DURECTORY_LENGTH (1)
#define P_PARENT_DIRECTORYA ("..")
#define P_PARENT_DIRECTORYW (L"..")
#define P_PARENT_DIRECTORY_LENGTH (2)
#define P_EXTENSION_MAX_LENGTH (10)

int p_get_file_counta(const char *path, const char *search_extension, unsigned char sub_directory) {
	char p_tmp_patha[MAX_PATH];
	p_sprintfa((char *const)p_tmp_patha, MAX_PATH, MAX_PATH, NULL, "%s\\%s", path, P_WILD_CARDA);
	WIN32_FIND_DATAA ffd;
	HANDLE h = FindFirstFileA((LPCSTR)p_tmp_patha, &ffd);
	if (h == INVALID_HANDLE_VALUE) {
		return -1;
	}

	int ret = 0;
	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (sub_directory == 1) {
				if (strncmp(ffd.cFileName, P_CURRENT_DIRECTORYA, P_CURRENT_DURECTORY_LENGTH) != 0 && strncmp(ffd.cFileName, P_PARENT_DIRECTORYA, P_PARENT_DIRECTORY_LENGTH) != 0) {
					p_sprintfa((char *const)p_tmp_patha, MAX_PATH, MAX_PATH, NULL, "%s\\%s", path, ffd.cFileName);
					ret += p_get_file_counta((LPCSTR)p_tmp_patha, search_extension, sub_directory);
				}
			}
		} else {
			if (search_extension == NULL) {
				ret++;
			} else {
				if (strncmp(search_extension, P_WILD_CARDA, P_WILD_CARD_LENGTH) == 0) {
					ret++;
				} else {
					LPCSTR e = PathFindExtensionA(ffd.cFileName);
					size_t e_len = strnlen_s(e, P_EXTENSION_MAX_LENGTH);
					if (e_len > 0) {
						if (strncmp(&e[1], search_extension, strnlen_s(search_extension, P_EXTENSION_MAX_LENGTH)) == 0) {
							ret++;
						}
					}
				}
			} 
		}
	} while (FindNextFileA(h, &ffd));

	if (FindClose(h) == 0) {
		return -1;
	}

	return ret;
}

int p_get_file_countw(const wchar_t *path, const wchar_t *search_extension, unsigned char sub_directory) {
	wchar_t p_tmp_pathw[MAX_PATH];
	p_sprintfw((wchar_t *const)p_tmp_pathw, MAX_PATH, MAX_PATH, NULL, L"%s\\%s", path, P_WILD_CARDW);
	WIN32_FIND_DATAW ffd;
	HANDLE h = FindFirstFileW((LPCWSTR)p_tmp_pathw, &ffd);
	if (h == INVALID_HANDLE_VALUE) {
		return -1;
	}

	int ret = 0;
	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (sub_directory == 1) {
				if (wcsncmp(ffd.cFileName, P_CURRENT_DIRECTORYW, P_CURRENT_DURECTORY_LENGTH) != 0 && wcsncmp(ffd.cFileName, P_PARENT_DIRECTORYW, P_PARENT_DIRECTORY_LENGTH) != 0) {
					p_sprintfw((wchar_t *const)p_tmp_pathw, MAX_PATH, MAX_PATH, NULL, "%s\\%s", path, ffd.cFileName);
					ret += p_get_file_countw((LPCWSTR)p_tmp_pathw, search_extension, sub_directory);
				}
			}
		} else {
			if (search_extension == NULL) {
				ret++;
			} else {
				if (wcsncmp(search_extension, P_WILD_CARDW, P_WILD_CARD_LENGTH) == 0) {
					ret++;
				} else {
					LPWSTR e = PathFindExtensionW(ffd.cFileName);
					size_t e_len = wcsnlen_s(e, P_EXTENSION_MAX_LENGTH);
					if (e_len > 0) {
						if (wcsncmp(&e[1], search_extension, wcsnlen_s(search_extension, P_EXTENSION_MAX_LENGTH)) == 0) {
							ret++;
						}
					}
				}
			}
		}
	} while (FindNextFileW(h, &ffd));

	if (FindClose(h) == 0) {
		return -1;
	}

	return ret;
}

int p_get_filesa(const char *path, const char *search_extension, unsigned char sub_directory, int *index, char *files[]) {
	char p_tmp_patha[MAX_PATH];
	p_sprintfa((char *const)p_tmp_patha, MAX_PATH, MAX_PATH, NULL, "%s\\%s", path, P_WILD_CARDA);
	WIN32_FIND_DATAA ffd;
	HANDLE h = FindFirstFileA((LPCSTR)p_tmp_patha, &ffd);
	if (h == INVALID_HANDLE_VALUE) {
		return -1;
	}

	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (sub_directory == 1) {
				if (strncmp(ffd.cFileName, P_CURRENT_DIRECTORYA, P_CURRENT_DURECTORY_LENGTH) != 0 && strncmp(ffd.cFileName, P_PARENT_DIRECTORYA, P_PARENT_DIRECTORY_LENGTH) != 0) {
					p_sprintfa((char *const)p_tmp_patha, MAX_PATH, MAX_PATH, NULL, "%s\\%s", path, ffd.cFileName);
					p_get_filesa((LPCSTR)p_tmp_patha, search_extension, sub_directory, index, files);
				}
			}
		} else {
			if (search_extension == NULL) {
				p_sprintfa((char *const)p_tmp_patha, MAX_PATH, MAX_PATH, NULL, "%s\\%s", path, ffd.cFileName);
				strncpy_s(files[*index], MAX_PATH, (const char*)p_tmp_patha, MAX_PATH);
				(*index)++;
			} else {
				if (strncmp(search_extension, P_WILD_CARDA, P_WILD_CARD_LENGTH) == 0) {
					p_sprintfa((char *const)p_tmp_patha, MAX_PATH, MAX_PATH, NULL, "%s\\%s", path, ffd.cFileName);
					strncpy_s(files[*index], MAX_PATH, (const char *)p_tmp_patha, MAX_PATH);
					(*index)++;
				} else {
					LPCSTR e = PathFindExtensionA(ffd.cFileName);
					size_t e_len = strnlen_s(e, P_EXTENSION_MAX_LENGTH);
					if (e_len > 0) {
						if (strncmp(&e[1], search_extension, strnlen_s(search_extension, P_EXTENSION_MAX_LENGTH)) == 0) {
							p_sprintfa((char *const)p_tmp_patha, MAX_PATH, MAX_PATH, NULL, "%s\\%s", path, ffd.cFileName);
							strncpy_s(files[*index], MAX_PATH, (const char *)p_tmp_patha, MAX_PATH);
							(*index)++;
						}
					}
				}
			}
		}
	} while (FindNextFileA(h, &ffd));

	if (FindClose(h) == 0) {
		return -1;
	}

	return 0;
}

int p_get_filesw(const wchar_t *path, const wchar_t *search_extension, unsigned char sub_directory, int *index, wchar_t *files[]) {
	char p_tmp_pathw[MAX_PATH];
	p_sprintfw((wchar_t *const)p_tmp_pathw, MAX_PATH, MAX_PATH, NULL, L"%s\\%s", path, P_WILD_CARDW);
	WIN32_FIND_DATAW ffd;
	HANDLE h = FindFirstFileW((LPWSTR)p_tmp_pathw, &ffd);
	if (h == INVALID_HANDLE_VALUE) {
		return -1;
	}

	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (sub_directory == 1) {
				if (wcsncmp(ffd.cFileName, P_CURRENT_DIRECTORYW, P_CURRENT_DURECTORY_LENGTH) != 0 && wcsncmp(ffd.cFileName, P_PARENT_DIRECTORYW, P_PARENT_DIRECTORY_LENGTH) != 0) {
					p_sprintfw((wchar_t *const)p_tmp_pathw, MAX_PATH, MAX_PATH, NULL, L"%s\\%s", path, ffd.cFileName);
					p_get_filesw((LPWSTR)p_tmp_pathw, search_extension, sub_directory, index, files);
				}
			}
		} else {
			if (search_extension == NULL) {
				p_sprintfw((wchar_t *const)p_tmp_pathw, MAX_PATH, MAX_PATH, NULL, L"%s\\%s", path, ffd.cFileName);
				wcsncpy_s(files[*index], MAX_PATH, (const wchar_t *)p_tmp_pathw, MAX_PATH);
				(*index)++;
			} else {
				if (wcsncmp(search_extension, P_WILD_CARDW, P_WILD_CARD_LENGTH) == 0) {
					p_sprintfw((wchar_t *const)p_tmp_pathw, MAX_PATH, MAX_PATH, NULL, L"%s\\%s", path, ffd.cFileName);
					wcsncpy_s(files[*index], MAX_PATH, (const wchar_t *)p_tmp_pathw, MAX_PATH);
					(*index)++;
				} else {
					LPWSTR e = PathFindExtensionW(ffd.cFileName);
					size_t e_len = wcsnlen_s(e, P_EXTENSION_MAX_LENGTH);
					if (e_len > 0) {
						if (wcsncmp(&e[1], search_extension, wcsnlen_s(search_extension, P_EXTENSION_MAX_LENGTH)) == 0) {
							p_sprintfw((wchar_t *const)p_tmp_pathw, MAX_PATH, MAX_PATH, NULL, L"%s\\%s", path, ffd.cFileName);
							wcsncpy_s(files[*index], MAX_PATH, (const wchar_t *)p_tmp_pathw, MAX_PATH);
							(*index)++;
						}
					}
				}
			}
		}
	} while (FindNextFileW(h, &ffd));

	if (FindClose(h) == 0) {
		return -1;
	}

	return 0;
}
