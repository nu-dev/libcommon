#ifndef _LIB_COMMON_INC
#define _LIB_COMMON_INC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "dictionary.h"
#include "strutil.h"

/* color codes */
#ifndef _NU_COLORS
    #define _NU_COLORS
    #ifdef __linux__
        #define KNRM  "\x1B[0m"
        #define KRED  "\x1B[31m"
        #define KGRN  "\x1B[32m"
        #define KYEL  "\x1B[33m"
        #define KBLU  "\x1B[34m"
        #define KMAG  "\x1B[35m"
        #define KCYN  "\x1B[36m"
        #define KWHT  "\x1B[37m"
        #define RESET "\033[0m"
    #else
        #define KNRM  ""
        #define KRED  ""
        #define KGRN  ""
        #define KYEL  ""
        #define KBLU  ""
        #define KMAG  ""
        #define KCYN  ""
        #define KWHT  ""
        #define RESET ""
    #endif
#endif

#endif
