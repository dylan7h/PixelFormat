#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "png.h"

void PNG_ShowFileInformation(void *png)
{
    void *pChunk = png;
    void *pData;
    char *chChunkType;

    assert(*(uint64_t *)pChunk == PNG_SIGNATURE);

    for (pChunk += PNG_CHUNK_ENTRY_OFFSET; GET_PNG_CHUNK_TYPE(pChunk) != PNG_CHUNK_TYPE_IEND; pChunk = GET_PNG_NEXT_CHUNK(pChunk))
    {
        chChunkType = (char*)(&GET_PNG_CHUNK_TYPE(pChunk));
        pData = GET_PNG_CHUNK_DATA_POS(pChunk);

        puts("======================================================");
        printf("Length      : %u\n", EndianSwap32(GET_PNG_CHUNK_SIZE(pChunk)));
        printf("Chunk Type  : %c%c%c%c\n", chChunkType[0], chChunkType[1], chChunkType[2], chChunkType[3]);

        if (GET_PNG_CHUNK_TYPE(pChunk) == PNG_CHUNK_TYPE_IHDR)
        {
            static const char* lpszColorType[] = {
                "(0) - Each pixel is a grayscale sample. [ 1,2,4,8,16 bit ]",
                "(1) - Unknown",
                "(2) - Each pixel is an R,G,B triple. [ 8, 16 bit ]",
                "(3) - Each pixel is a palette index a PLTE chunk must appear. [ 1, 2, 4, 8 bit ]",
                "(4) - Each pixel is a grayscale sample, followed by an alpha sample. [ 8, 16 bit ]",
                "(5) - Unknown",
                "(6) - Each pixel is an R,G,B triple, followed by an alpha sample. [ 8, 16 bit ]",
            };

            static const char* lpszFilterType[] = {
                "(0) - None",
                "(1) - Sub",
                "(2) - Up",
                "(3) - Average",
                "(4) - Paeth",
            };

            static const char* lpszInterlaceType[] = {
                "(0) - Sequential : No Interlaced",
                "(1) - ADAM7"
            };

            printf("    > Width              : %u\n", EndianSwap32(GET_PNG_IHDR_WIDTH(pData)));
            printf("    > Height             : %u\n", EndianSwap32(GET_PNG_IHDR_HEIGHT(pData)));
            printf("    > Bit Depth          : %u bit\n", GET_PNG_IHDR_BIT_DEPTH(pData));
            printf("    > Color Type         : %s\n", lpszColorType[ GET_PNG_IHDR_COLOR_TYPE(pData) ]);
            printf("    > Compression Method : %u\n", GET_PNG_IHDR_COMPRESSION_METHOD(pData));
            printf("    > Filter Method      : %s\n", lpszFilterType[ GET_PNG_IHDR_FILTER_METHOD(pData) ]);
            printf("    > Interlace Method   : %s\n", lpszInterlaceType [ GET_PNG_IHDR_INTERLACE_METHOD(pData) ]);
        }
        
        if (GET_PNG_CHUNK_TYPE(pChunk) == PNG_CHUNK_TYPE_sRGB)
        {
            static const char* lpszRenderingIntent[] = {
                "(0) - Perceptual",
                "(1) - Relative colorimetric",
                "(2) - Saturation",
                "(3) - Absolute colorimetric",
            };
            printf("    > Rendering Intent   : %s\n", lpszRenderingIntent[ *(uint8_t*)pData ]);
        }

        if (GET_PNG_CHUNK_TYPE(pChunk) == PNG_CHUNK_TYPE_pHYs)
        {
            printf("    > Pixels per unit, X axis : %u\n", EndianSwap32(*((uint32_t*)pData)));
            printf("    > Pixels per unit, Y axis : %u\n", EndianSwap32(*((uint32_t*)(pData + 4))));
            printf("    > Unit specifier          : unit is %s\n", *((uint8_t*)(pData + 8)) ? "the meter (1)" : "unknown (0)");
        }

        printf("Calc CRC    : %08x\n", EndianSwap32( (uint32_t)crc((uint8_t*)chChunkType, 4 + (int32_t)EndianSwap32(GET_PNG_CHUNK_SIZE(pChunk))) ));
        printf("CRC         : %08x\n\n", GET_PNG_CHUNK_CRC(pChunk));
    }
}

void PNG_ExportRawData(__IN void* png, __INOUT int32_t* width, __INOUT int32_t* height, __INOUT int32_t* bpp, __INOUT int32_t* stride, __INOUT void** raw, __INOUT int32_t* rawlen)
{
    void *pChunk = png;
    void *pData;

    assert(*(uint64_t *)pChunk == PNG_SIGNATURE);

    for (pChunk += PNG_CHUNK_ENTRY_OFFSET; GET_PNG_CHUNK_TYPE(pChunk) != PNG_CHUNK_TYPE_IEND; pChunk = GET_PNG_NEXT_CHUNK(pChunk))
    {
        pData = GET_PNG_CHUNK_DATA_POS(pChunk);
    
        if (GET_PNG_CHUNK_TYPE(pChunk) == PNG_CHUNK_TYPE_IHDR)
        {
            *width  = EndianSwap32(GET_PNG_IHDR_WIDTH(pData));
            *height = EndianSwap32(GET_PNG_IHDR_HEIGHT(pData));
            *bpp    = (int32_t)GET_PNG_IHDR_BIT_DEPTH(pData);

            // printf("    > Width              : %u\n", EndianSwap32(GET_PNG_IHDR_WIDTH(pData)));
            // printf("    > Height             : %u\n", EndianSwap32(GET_PNG_IHDR_HEIGHT(pData)));
            // printf("    > Bit Depth          : %u bit\n", GET_PNG_IHDR_BIT_DEPTH(pData));
            // printf("    > Color Type         : %s\n", lpszColorType[ GET_PNG_IHDR_COLOR_TYPE(pData) ]);
            // printf("    > Compression Method : %u\n", GET_PNG_IHDR_COMPRESSION_METHOD(pData));
            // printf("    > Filter Method      : %s\n", lpszFilterType[ GET_PNG_IHDR_FILTER_METHOD(pData) ]);
            // printf("    > Interlace Method   : %s\n", lpszInterlaceType [ GET_PNG_IHDR_INTERLACE_METHOD(pData) ]);
        }
        
        if (GET_PNG_CHUNK_TYPE(pChunk) == PNG_CHUNK_TYPE_pHYs)
        {
            // printf("    > Pixels per unit, X axis : %u\n", EndianSwap32(*((uint32_t*)pData)));
            // printf("    > Pixels per unit, Y axis : %u\n", EndianSwap32(*((uint32_t*)(pData + 4))));
            // printf("    > Unit specifier          : unit is %s\n", *((uint8_t*)(pData + 8)) ? "the meter (1)" : "unknown (0)");
        }
    }
}
