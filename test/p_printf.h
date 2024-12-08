#ifndef P_PRINTF_H
#define P_PRINTF_H

int p_printfa(const char *locale, int *written_bytes, const char *const format, ...);

int p_printfw(const unsigned short *locale, int *written_bytes, const unsigned short *const format, ...);

int p_printfa_simple(const char *const format, ...);

int p_printfw_simple(const unsigned short *const format, ...);

#endif
