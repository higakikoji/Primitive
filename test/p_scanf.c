#include <stdio.h>
#include <stdarg.h>
#include <locale.h>
#include "p_scanf.h"

int p_scanfa(const char *locale, const char *const format, ...) {
  va_list ap;
  va_start(ap, format);
  _locale_t l = _create_locale(LC_ALL, locale);
  int ret = _vscanf_s_l(format, l, ap);
  _free_locale(l);
  va_end(ap);
  return ret;
}

int p_scanfw(const wchar_t *locale, const wchar_t *const format, ...) {
  va_list ap;
  va_start(ap, format);
  _locale_t l = _wcreate_locale(LC_ALL, locale);
  int ret = _vwscanf_s_l(format, l, ap);
  _free_locale(l);
  va_end(ap);
  return ret;
}
