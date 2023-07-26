#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
//#define __ARMCLIB_VERSION 5030076

  #ifndef __cplusplus /* In C++, 'bool', 'true' and 'false' and keywords */
    #define bool _Bool
    #define true 1
    #define false 0
  #else
    #ifdef __GNUC__
      /* GNU C++ supports direct inclusion of stdbool.h to provide C99
         compatibility by defining _Bool */
      #define _Bool bool
    #endif
  #endif

#endif
