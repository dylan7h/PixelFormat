#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bitmap.h"


void BMP_ShowFileInformation(__IN void* bitmap)
{
    assert( GET_BMP_FILE_HDR_SIGNATURE(bitmap) == BMP_SIGNATURE );

    printf("[ BITMAP File Header ]\n");
    printf("  - length          : %u\n", GET_BMP_FILE_HDR_LENGTH(bitmap));
    printf("  - offset          : %x\n", GET_BMP_FILE_HDR_OFFSET(bitmap));

    printf("[ BITMAP Information Header ]\n");
    printf("  - hdr length      : %u\n", GET_BMP_INFO_HDR_LENGTH(bitmap));
    printf("  - width           : %u\n", GET_BMP_INFO_HDR_WIDTH(bitmap));
    printf("  - height          : %u\n", GET_BMP_INFO_HDR_HEIGHT(bitmap));
    printf("  - planes          : %u\n", GET_BMP_INFO_HDR_PLANES(bitmap));
    printf("  - bit count       : %u\n", GET_BMP_INFO_HDR_BIT_COUNT(bitmap));
    printf("  - compression     : %u\n", GET_BMP_INFO_HDR_COMPRESSION(bitmap));
    printf("  - raw img size    : %u\n", GET_BMP_INFO_HDR_IMG_SIZE(bitmap));
    printf("  - x pixel / m     : %u\n", GET_BMP_INFO_HDR_XPELS_PER_METER(bitmap));
    printf("  - y pixel / m     : %u\n", GET_BMP_INFO_HDR_YPELS_PER_METER(bitmap));
    printf("  - used color      : %u\n", GET_BMP_INFO_HDR_CLR_USED(bitmap));
    printf("  - important color : %u\n", GET_BMP_INFO_HDR_CLR_IMPORTANT(bitmap));
    if(GET_BMP_INFO_HDR_LENGTH(bitmap) >= BMP_VERSION4_LENGTH)
    {
        printf("  - red mask        : %08x\n", GET_BMP_INFO_HDR_RED_MASK(bitmap));
        printf("  - green mask      : %08x\n", GET_BMP_INFO_HDR_GREEN_MASK(bitmap));
        printf("  - blue mask       : %08x\n", GET_BMP_INFO_HDR_BLUE_MASK(bitmap));
        printf("  - alpha mask      : %08x\n", GET_BMP_INFO_HDR_ALPHA_MASK(bitmap));
        printf("  - cs type         : %x\n", GET_BMP_INFO_HDR_CS_TYPE(bitmap));
        printf("  - red coord       : %u, %u, %u\n", GET_BMP_INFO_HDR_RED_X(bitmap), GET_BMP_INFO_HDR_RED_Y(bitmap), GET_BMP_INFO_HDR_RED_Z(bitmap));
        printf("  - green coord     : %u, %u, %u\n", GET_BMP_INFO_HDR_GREEN_X(bitmap), GET_BMP_INFO_HDR_GREEN_Y(bitmap), GET_BMP_INFO_HDR_GREEN_Z(bitmap));
        printf("  - blue coord      : %u, %u, %u\n", GET_BMP_INFO_HDR_BLUE_X(bitmap), GET_BMP_INFO_HDR_BLUE_Y(bitmap), GET_BMP_INFO_HDR_BLUE_Z(bitmap));
        printf("  - gamma red       : %x\n", GET_BMP_INFO_HDR_GAMMA_RED(bitmap));
        printf("  - gamma green     : %x\n", GET_BMP_INFO_HDR_GAMMA_GREEN(bitmap));
        printf("  - gamma blue      : %x\n", GET_BMP_INFO_HDR_GAMMA_BLUE(bitmap));
    }

    if(GET_BMP_INFO_HDR_LENGTH(bitmap) >= BMP_VERSION5_LENGTH)
    {
        printf("  - intent          : %x\n", GET_BMP_INFO_HDR_INTENT(bitmap));
        printf("  - profile data pos: %x\n", GET_BMP_INFO_HDR_PROFILE_DATA(bitmap));
        printf("  - profile length  : %x\n", GET_BMP_INFO_HDR_PROFILE_LENGTH(bitmap));
    }
    puts("");
}

void BMP_ExtractRawData(__IN void* bitmap, __INOUT SIMPLE_BMP_t* simpleBMP)
{
    simpleBMP->width    = GET_BMP_INFO_HDR_WIDTH(bitmap);
    simpleBMP->height   = GET_BMP_INFO_HDR_HEIGHT(bitmap);
    simpleBMP->bpp      = GET_BMP_INFO_HDR_BIT_COUNT(bitmap);
    simpleBMP->padding  = (((simpleBMP->bpp * simpleBMP->width) / BYTE_PER_BITS) % BYTE4_ALIGN);
    if(simpleBMP->padding != 0)
    {
        simpleBMP->padding = BYTE4_ALIGN - simpleBMP->padding;
        printf("  - padding : %d\n", simpleBMP->padding);
    }
    simpleBMP->stride   = ((simpleBMP->bpp * simpleBMP->width) / 8) + simpleBMP->padding;

    /* Is Exit Color palette  */
    if(GET_BMP_FILE_HDR_OFFSET(bitmap) > (BMP_INFO_HDR_OFFSET + GET_BMP_INFO_HDR_LENGTH(bitmap)))
    {
        uint8_t*                palette;
        int32_t                 newPadiing;
        int32_t                 newStride;

        palette     = bitmap + BMP_INFO_HDR_OFFSET + GET_BMP_INFO_HDR_LENGTH(bitmap);
        newPadiing  = (((BPP24 * simpleBMP->width) / BYTE_PER_BITS) % BYTE4_ALIGN);
        if(newPadiing != 0)
        {
            newPadiing = BYTE4_ALIGN - newPadiing;
            printf("  - new padding : %d\n", newPadiing);
        }
        newStride = ((BPP24 * simpleBMP->width) / BYTE_PER_BITS) + newPadiing;

        printf("new padiing: %d\n", newPadiing);
        printf("palette size: %d\n", GET_BMP_FILE_HDR_OFFSET(bitmap) - (BMP_INFO_HDR_OFFSET + GET_BMP_INFO_HDR_LENGTH(bitmap)));

        simpleBMP->imgLen   = simpleBMP->height * newStride;
        simpleBMP->raw      = malloc(simpleBMP->imgLen);
        assert(simpleBMP->raw != NULL);

        int32_t row, col;
        uint8_t* dst;
        uint8_t* src;
        uint8_t idx;
        for(row = 0; row < simpleBMP->height; row++)
        {
            for(col = 0; col < simpleBMP->width; col++)
            {
                dst = (uint8_t*)(simpleBMP->raw + (((simpleBMP->height - 1) - row) * newStride) + (col * (BPP24 / BYTE_PER_BITS)));
                src = (uint8_t*)((bitmap + GET_BMP_FILE_HDR_OFFSET(bitmap)) + (row * simpleBMP->stride) + ((col * simpleBMP->bpp) / BYTE_PER_BITS));
                switch (simpleBMP->bpp)
                {
                    case 1:
                        idx = ((*src) >> ( col % 8 ))  & 0x01;
                    break;

                    case 2:
                        idx = ((*src) >> ( ( col % 4 ) * 2 ))  & 0x03;
                    break;

                    case 4:
                        idx = ((*src) >> ( ( col % 2 ) * 4 ))  & 0x0f;
                    break;

                    case 8:
                    case 16:
                        idx = *src;
                    break;
                
                    default:
                        abort();
                    break;
                }
                
                dst[0]  = *(palette + (idx * 4) + 0);
                dst[1]  = *(palette + (idx * 4) + 1);
                dst[2]  = *(palette + (idx * 4) + 2);
            }
        }

        simpleBMP->padding = newPadiing;
        simpleBMP->stride = newStride;
    }
    else
    {
        simpleBMP->imgLen   = GET_BMP_INFO_HDR_IMG_SIZE(bitmap);
        simpleBMP->raw      = malloc(GET_BMP_INFO_HDR_IMG_SIZE(bitmap));
        assert(simpleBMP->raw != NULL);

        /* Reverse Row */
        int32_t row;
        void*   data = bitmap + GET_BMP_FILE_HDR_OFFSET(bitmap);
        data += simpleBMP->stride * (GET_BMP_INFO_HDR_HEIGHT(bitmap) - 1);
        for(row = 0; row < GET_BMP_INFO_HDR_HEIGHT(bitmap); row++ )
        {
            memcpy(simpleBMP->raw + (row * simpleBMP->stride), data, simpleBMP->stride);
            data -= simpleBMP->stride;
        }
    }
}
