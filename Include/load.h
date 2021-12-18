#ifndef __LOAD__H__
#define __LOAD__H__

#include "common.h"

void loadFile(__IN const char* path, __INOUT void** ppMem, __INOUT int32_t* pSize);
void saveFile(__IN const char* path, __IN void* pMem, __IN int32_t Size);

#endif  //!__LOAD__H__
