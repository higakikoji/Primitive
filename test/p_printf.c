#include <stdio.h>
#include <stdarg.h>
#include <locale.h>
#include "p_printf.h"

int p_printfa(const char *locale, const char *const format, ...) {
	va_list ap;
	va_start(ap, format);
	_locale_t l = _create_locale(LC_ALL, locale);
	int ret = _vprintf_s_l(format, l, ap);
	_free_locale(l);
	va_end(ap);
	return ret;
}

int p_printfw(const wchar_t *locale, const wchar_t *const format, ...) {
	va_list ap;
	va_start(ap, format);
	_locale_t l = _wcreate_locale(LC_ALL, locale);
	int ret = _vwprintf_s_l(format, l, ap);
	_free_locale(l);
	va_end(ap);
	return ret;
}
