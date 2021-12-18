#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "load.h"

void loadFile(__IN const char* path, __INOUT void** ppMem, __INOUT int32_t* pSize)
{
    FILE* fp;
    fp = fopen(path, "rb");
    assert(fp != NULL);

    size_t fileLen;
    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    *ppMem = malloc(fileLen);
    assert(*ppMem != NULL);

    size_t readLen;
    readLen = fread(*ppMem, 1, fileLen, fp);
    assert(readLen == fileLen);

    *pSize = fileLen;

    fclose(fp);
}

void saveFile(__IN const char* path, __IN void* pMem, __IN int32_t Size)
{
    FILE* fp;
    fp = fopen(path, "wb");
    assert(fp != NULL);

    size_t writeLen;
    writeLen = fwrite(pMem, 1, Size, fp);
    assert(writeLen == Size);

    fclose(fp);
}
