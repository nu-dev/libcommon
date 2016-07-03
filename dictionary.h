#ifndef _LIB_COMMON_DICTIONARY_INC
#define _LIB_COMMON_DICTIONARY_INC
#include "libnucommon.h"
/*
Dictionary for the template engine

In the future, this will use a proper hashmap, but for now, it uses a list.
*/

typedef struct _template_dictionary_entry {
    char *key;
    char *value;
    struct _template_dictionary_entry *next;
} template_dictionary_entry;

typedef struct _template_dictionary {
    template_dictionary_entry *entryList;
    template_dictionary_entry *entryListTail;
    unsigned int length;
} template_dictionary;

const char *td_fetch_val(const template_dictionary *in, const char *lookup);
template_dictionary *td_new();
void td_clean(template_dictionary *in);
template_dictionary *td_merge(template_dictionary *in, template_dictionary *in2);
void td_put_val(template_dictionary *in, const char *key, const char *value);
void td_remove_val(template_dictionary *in, const char *key);
#endif
