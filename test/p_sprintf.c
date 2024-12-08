#include <stdio.h>
#include <stdarg.h>
#include <locale.h>
#include "p_sprintf.h"

int p_sprintfa(char *const buffer, const size_t buffer_count, const size_t max_count, const char *locale, int *written_bytes, const char *const format, ...) {
	va_list ap;
	va_start(ap, format);
	_locale_t l = _create_locale(LC_ALL, locale);
	int ret = _vsnprintf_s_l(buffer, buffer_count, max_count, format, l, ap);
	_free_locale(l);
	va_end(ap);
	if (ret < 0) {
		return ret;
	}
	if (written_bytes != NULL) {
		*written_bytes = ret;
	}
	return 0;
}

int p_sprintfw(unsigned short *const buffer, const size_t buffer_count, const size_t max_count, const wchar_t *locale, int *written_bytes, const wchar_t *const format, ...) {
	va_list ap;
	va_start(ap, format);
	_locale_t l = _wcreate_locale(LC_ALL, locale);
	int ret = _vsnwprintf_s_l(buffer, buffer_count, max_count, format, l, ap);
	_free_locale(l);
	va_end(ap);
	if (ret < 0) {
		return ret;
	}
	if (written_bytes != NULL) {
		*written_bytes = ret;
	}
	return 0;
}

int p_sprintfa_simple(char *const buffer, const size_t buffer_count, const size_t max_count, const char *const format, ...) {
	va_list ap;
	va_start(ap, format);
	int ret = vsnprintf_s(buffer, buffer_count, max_count, format, ap);
	va_end(ap);
	if (ret < 0) {
		return ret;
	}
	return 0;
}

int p_sprintfw_simple(wchar_t *const buffer, const size_t buffer_count, const size_t max_count, const wchar_t *const format, ...) {
	va_list ap;
	va_start(ap, format);
	int ret = _vsnwprintf_s(buffer, buffer_count, max_count, format, ap);
	va_end(ap);
	if (ret < 0) {
		return ret;
	}
	return 0;
}
