#include "dictionary.h"

char *td_fetch_val(const template_dictionary *in, const char *lookup) {
    // get the first entry
    template_dictionary_entry *curr = in->entryList;
    
    // loop through the entire list
    while (curr != NULL) {
        // until the key we're looking for is found
        if (strcmp(lookup, curr->key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }
    // not found
    return NULL;
}

void td_put_val(template_dictionary *in, const char *key, const char *value) {
    // set up the new template_dictionary_entry to add
    template_dictionary_entry *toAdd = malloc(sizeof(template_dictionary_entry));
    toAdd->key = strdup(key);
    toAdd->value = strdup(value);
    
    // check if this is the first template_dictionary_entry in the dictionary
    if (in->entryList == NULL) {
        in->entryList = toAdd;
        in->entryListTail = toAdd;
    } else {
        // not the first one
        (in->entryListTail)->next = toAdd;
        in->entryListTail = toAdd;
    }
    // incr length
    in->length++;
}

void td_remove_val(template_dictionary *in, const char *key) {
    // get the first entry
    template_dictionary_entry *curr = in->entryList;
    template_dictionary_entry *prev = NULL;
    
    // loop through the entire list
    while (curr != NULL) {
        // until the key we're looking for is found
        if (strcmp(key, curr->key) == 0) {
            if (prev == NULL) {
                // first item in the list, now curr's next is the first
                in->entryList = curr->next;
                if (curr->next == NULL) {
                    // curr was also the last item
                    in->entryListTail = NULL;
                }
            } if (curr->next == NULL) {
                // last item in the list, now prev is the last
                in->entryListTail = prev;
                prev->next = NULL;
            } else {
                // somewhere in the middle of the list
                prev->next = curr->next;
            }
            // clean up curr
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
    // get the first entry
    template_dictionary_entry *curr = in->entryList;
    template_dictionary_entry *next;
    
    // loop through the entire list
    while (curr != NULL) {
        next = curr->next;
        free(curr->key);
        free(curr->value);
        free(curr);
        curr = next;
    }
    
    free(in);
}

template_dictionary *td_merge(template_dictionary *in, template_dictionary *in2) {
    template_dictionary *ret = td_new();
    template_dictionary_entry *curr = in->entryList;
    template_dictionary_entry *currcopy;
    
    while (curr != NULL) {
        if (ret->entryList == NULL) {
            ret->entryList = curr;
            currcopy = ret->entryList;
        }
        curr = curr->next;
        currcopy->next = curr;
        ret->length++;
    }
    
    curr = in2->entryList;
    
    while (curr != NULL) {
        curr = curr->next;
        currcopy->next = curr;
        ret->length++;
    }
    
    free(in);
    free(in2);
    
    ret->entryListTail = currcopy;
    return ret;
}

template_dictionary *td_new() {
    // create a new empty template_dictionary with the right values set
    // so that it is ready to be used with other td_ functions
    template_dictionary *toCreate = malloc(sizeof(template_dictionary));
    toCreate->entryList = NULL;
    toCreate->entryListTail = NULL;
    toCreate->length = 0;
    return toCreate;
}