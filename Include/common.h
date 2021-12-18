#ifndef __COMMON__H__
#define __COMMON__H__

#include <stdint.h>
#include <stdbool.h>

#ifndef __IN
#define __IN
#endif

#ifndef __OUT
#define __OUT
#endif

#ifndef __INOUT
#define __INOUT
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(PTR)  if((PTR) != NULL) { free((PTR)); (PTR) = NULL; }
#endif

#endif  //!__COMMON__H__
