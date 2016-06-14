#ifndef _LIB_COMMON_STRUTIL_INC
#define _LIB_COMMON_STRUTIL_INC
#include "libnucommon.h"
char *strutil_append_no_mutate(const char *first, const char *second);
char *strutil_appendn_no_mutate(const char *first, const char *second, int count);
char *strutil_append_and_free_both(char *first, char *second);
char *strutil_trim_spaces(const char *in);
char *strutil_next_token(const char *in, const char *token);
unsigned int strutil_remove_unicode(const uint8_t *in, const size_t length, char **out);
#endif