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

#ifndef BPP32
#define BPP32           (32)
#endif 

#ifndef BPP24
#define BPP24           (24)
#endif

#ifndef BPP16
#define BPP16           (16)
#endif

#ifndef BYTE_PER_BITS
#define BYTE_PER_BITS   (8)
#endif

#ifndef BYTE4_ALIGN
#define BYTE4_ALIGN     (4)
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(PTR)  if((PTR) != NULL) { free((PTR)); (PTR) = NULL; }
#endif

#endif  //!__COMMON__H__
