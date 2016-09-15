#include "dictionary.h"

const char *td_fetch_val(const template_dictionary *in, const char *lookup) {
    /* get the first entry */
    template_dictionary_entry *curr = in->entryList;
    
    /* loop through the entire list */
    while (curr != NULL) {
        /* until the key we're looking for is found */
        if (strcmp(lookup, curr->key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }
    /* not found */
    return NULL;
}

const char *td_fetch_val_default(const template_dictionary *in, const char *lookup, const char *default_val) {
    /* get the first entry */
    template_dictionary_entry *curr = in->entryList;
    
    /* loop through the entire list */
    while (curr != NULL) {
        /* until the key we're looking for is found */
        if (strcmp(lookup, curr->key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }
    /* not found */
    return default_val;
}

void td_put_val(template_dictionary *in, const char *key, const char *value) {
    /* set up the new template_dictionary_entry to add */
    template_dictionary_entry *toAdd = malloc(sizeof(template_dictionary_entry));
    toAdd->key = strdup(key);
    toAdd->value = strdup(value);
    toAdd->next = NULL;
    
    /* check if this is the first template_dictionary_entry in the dictionary */
    if (in->entryList == NULL) {
        in->entryList = toAdd;
        in->entryListTail = toAdd;
    } else {
        /* not the first one */
        (in->entryListTail)->next = toAdd;
        in->entryListTail = toAdd;
    }
    /* incr length */
    in->length++;
}

void td_remove_val(template_dictionary *in, const char *key) {
    /* get the first entry */
    template_dictionary_entry *curr = in->entryList;
    template_dictionary_entry *prev = NULL;
    
    /* loop through the entire list */
    while (curr != NULL) {
        /* until the key we're looking for is found */
        if (strcmp(key, curr->key) == 0) {
            if (prev == NULL) {
                /* first item in the list, now curr's next is the first */
                in->entryList = curr->next;
                if (curr->next == NULL) {
                    /* curr was also the last item */
                    in->entryListTail = NULL;
                }
            } if (curr->next == NULL) {
                /* last item in the list, now prev is the last */
                in->entryListTail = prev;
                prev->next = NULL;
            } else {
                /* somewhere in the middle of the list */
                prev->next = curr->next;
            }
            /* clean up curr */
            free(curr->key);
            free(curr->value);
            free(curr);
            
            in->length--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void td_clean(template_dictionary *in) {
    /* get the first entry */
    template_dictionary_entry *curr = in->entryList;
    template_dictionary_entry *next;
    
    /* loop through the entire list */
    while (curr != NULL) {
        next = curr->next;
        free(curr->key);
        free(curr->value);
        free(curr);
        curr = next;
    }
    
    free(in);
}

void _td_dump(template_dictionary *td) {
    template_dictionary_entry *tde = td->entryList;
    while (tde != NULL) {
        printf("k: %s\n", tde->key);
        tde = tde->next;
    }
}

template_dictionary *td_merge(template_dictionary *in, template_dictionary *in2) {
    template_dictionary *ret = td_new();
    template_dictionary_entry *curr = in->entryList;
    template_dictionary_entry *currcopy = NULL, *temp;
    
    while (curr != NULL) {
        temp = malloc(sizeof(template_dictionary_entry));
        /* check if this is the first template_dictionary_entry in the dictionary */
        if (currcopy == NULL) {
            currcopy = temp;
            currcopy->key = curr->key;
            currcopy->value = curr->value;
            currcopy->next = NULL;
            ret->entryList = currcopy;
        } else {
            currcopy->next = temp;
            currcopy = temp;
            currcopy->key = curr->key;
            currcopy->value = curr->value;
            currcopy->next = NULL;
        }
        /* incr length */
        ret->length++;
        curr = curr->next;
    }
    
    curr = in2->entryList;
    
    while (curr != NULL) {
        temp = malloc(sizeof(template_dictionary_entry));

        currcopy->next = temp;
        currcopy = temp;
        currcopy->key = curr->key;
        currcopy->value = curr->value;
        currcopy->next = NULL;
        
        /* incr length */
        ret->length++;
        curr = curr->next;
    }
    
    ret->entryListTail = currcopy;
    return ret;
}

template_dictionary *td_new() {
    /* create a new empty template_dictionary with the right values set */
    /* so that it is ready to be used with other td_ functions */
    template_dictionary *toCreate = malloc(sizeof(template_dictionary));
    toCreate->entryList = NULL;
    toCreate->entryListTail = NULL;
    toCreate->length = 0;
    return toCreate;
}
