#ifndef P_SPRINTF_H
#define P_SPRINTF_H

int p_sprintfa(char *const buffer, const unsigned __int64 buffer_count, const unsigned __int64 max_count, const char *locale, int *written_bytes, const char *const format, ...);

int p_sprintfw(unsigned short *const buffer, const unsigned __int64 buffer_count, const unsigned __int64 max_count, const unsigned short *locale, int *written_bytes, const unsigned short *const format, ...);

int p_sprintfa_simple(char *const buffer, const unsigned __int64 buffer_count, const unsigned __int64 max_count, const char *const format, ...);

int p_sprintfw_simple(unsigned short *const buffer, const unsigned __int64 buffer_count, const unsigned __int64 max_count, const unsigned short *const format, ...);

#endif
