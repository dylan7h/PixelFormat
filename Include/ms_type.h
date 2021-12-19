#ifndef __MS_TYPE__H__
#define __MS_TYPE__H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define ASSERT assert
#define TRACE0 printf
#define TRACE1 printf

typedef int64_t LONG;
typedef uint64_t ULONG;
typedef uint32_t UINT;
typedef uint32_t DWORD;
typedef uint32_t* LPDWORD;
typedef uint16_t WORD;
typedef uint16_t* LPWORD;
typedef uint8_t BYTE;
typedef uint8_t* LPBYTE;
typedef void* LPVOID;
typedef uint8_t BOOL;
typedef const char* LPCTSTR;

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif  //!__MS_TYPE__H__
