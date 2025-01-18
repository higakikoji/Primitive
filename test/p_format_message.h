#pragma once

#if defined(_MBCS)
#define p_get_error_string p_get_error_stringa
#else
#define p_get_error_string p_get_error_stringw
#endif

DWORD p_get_error_stringa(DWORD error, LPSTR buffer, DWORD size);

DWORD p_get_error_stringw(DWORD error, LPWSTR buffer, DWORD size);
