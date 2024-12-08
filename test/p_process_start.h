#pragma once

#include <vcruntime.h>

#if defined(_MBCS)
#define p_process_start p_process_starta
#else
#define p_process_start p_process_startw
#endif

int p_process_starta(const char *application_name, char *command_line);

int p_process_startw(const wchar_t *application_name, wchar_t *command_line);
