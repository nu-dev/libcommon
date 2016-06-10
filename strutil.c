#include "strutil.h"

/*
Returns a newly allocated string that is the concatenation of the first two.
*/
char *strutil_append_no_mutate(const char *first, const char *second) {
    int premier = strlen(first);
    int len = premier + strlen(second);
    char *ret = calloc(len, sizeof(char));
    strcpy(ret, first);
    strcpy(&ret[premier], second);
    return ret;
}

/*
Returns a newly allocated string that is the concatenation of the first string,
plus a certain number of characters from the second string.
*/
char *strutil_appendn_no_mutate(const char *first, const char *second, int count) {
    int premier = strlen(first);
    int len = premier + count;
    char *ret = calloc(len, sizeof(char));
    strcpy(ret, first);
    strncpy(&ret[premier], second, count);
    return ret;
}

/*
Returns a newly allocated string that is the concatenation of the first two,
and frees the two old strings.
*/
char *strutil_append_and_free_both(char *first, char *second) {
    char *ret = strutil_append_no_mutate(first, second);
    free(first);
    free(second);
    return ret;
}

/*
Strips trailing and leading spaces from a c string.
Returns a new c string. Does not free the old one.
*/
char *strutil_trim_spaces(const char *in) {
    const char *startLocation;
    int length = 0;
    
    // loop until the character is no longer a space
    while (*in == ' ') in++;
    
    // save the current location
    startLocation = in;
    
    // Loop until the character is a space or null (ie, string ended)
    while (*in != ' ' && *in != '\0') {
        length++;
        in++;
    }
    
    // return the newly allocated string
    return strndup(startLocation, length);
}


/*
get the next token
*/
char *strutil_next_token(const char *in, const char *token) {
    const char *currChar = in;
    int i;
    int tokenLen = strlen(token);
    // loop through the entire string
    while (*currChar != '\0') {
        // check if currChar matches the first token
        if (*currChar == *token) {
            // loop through for the rest of the token lengths to see if they are equal
            for (i = 1; i < tokenLen; i++) {
                if (currChar[i] != token[i]) {
                    // the match failed at some point, keep looping through string then.
                    goto noMatch;
                }
            }
            // the loop finished successfully (ie, everything matches), so return
            return (char *)currChar;
        }
        // keep looping through string
        noMatch:
        currChar++;
    }
    // nothing was found that matched
    return NULL;
}
