#include <stdio.h>
#include <stdarg.h>
#include <locale.h>

int p_printfa(const char *locale, int *written_bytes, const char *const format, ...) {
	va_list ap;
	va_start(ap, format);
	_locale_t l = _create_locale(LC_ALL, locale);
	int ret = _vprintf_s_l(format, l, ap);
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

int p_printfw(const wchar_t *locale, int *written_bytes, const wchar_t *const format, ...) {
	va_list ap;
	va_start(ap, format);
	_locale_t l = _wcreate_locale(LC_ALL, locale);
	int ret = _vwprintf_s_l(format, l, ap);
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

int p_printfa_simple(const char *const format, ...) {
	va_list ap;
	va_start(ap, format);
	int ret = vprintf_s(format, ap);
	va_end(ap);
	if (ret < 0) {
		return ret;
	}
	return 0;
}

int p_printfw_simple(const wchar_t *const format, ...) {
	va_list ap;
	va_start(ap, format);
	int ret = vwprintf_s(format, ap);
	va_end(ap);
	if (ret < 0) {
		return ret;
	}
	return 0;
}
