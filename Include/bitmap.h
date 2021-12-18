#ifndef __BITMAP__H__
#define __BITMAP__H__

#include "common.h"

#define BMP_8BIT_MASK                           (0xFF)
#define BMP_16BIT_MASK                          (0xFFFF)
#define BMP_32BIT_MASK                          (0xFFFFFFFF)


#define BMP_VERSION1_LENGTH                     (12)    /* Not Supported */
#define BMP_VERSION2_LENGTH                     (64)    /* Not Supported */
#define BMP_VERSION3_LENGTH                     (40)
#define BMP_VERSION4_LENGTH                     (108)
#define BMP_VERSION5_LENGTH                     (124)

/* 
 ***************************************************************************
    Bitmap File Structure
 ***************************************************************************
 */
#define BMP_FILE_HDR_OFFSET                     (0)
#define     BMP_FILE_HDR_SIGNATURE_POS          (0)     /* Width: 16 - Signature Number: 42 4D | B M */
#define         BMP_SIGNATURE                   (0x4D42)
#define     BMP_FILE_HDR_LENGTH_POS             (2)     /* Width: 32 - Total File Size */
#define     BMP_FILE_HDR_OFFSET_POS             (10)    /* Width: 32 - Raw Data Offset */

#define BMP_INFO_HDR_OFFSET                     (14)
#define     BMP_INFO_HDR_LENGTH_POS             (0)     /* Width: 32 - Size Of This Header */
#define     BMP_INFO_HDR_WIDTH_POS              (4)     /* Width: 32 - BMP Width */
#define     BMP_INFO_HDR_HEIGHT_POS             (8)     /* Width: 32 - BMP Height */
#define     BMP_INFO_HDR_PLANES_POS             (12)    /* Width: 16 - Color Plane : Must be 1 */
#define     BMP_INFO_HDR_BIT_COUNT_POS          (14)    /* Width: 16 - Depth: 1, 4, 8, 16, 24, 32 */
#define     BMP_INFO_HDR_COMPRESSION_POS        (16)    /* Width: 32 - Type Of Compression */
#define         BI_RGB                          (0)     /* Normal */
#define         BI_RLE8                         (1)     /* 8bit/pixel */
#define         BI_RLE4                         (2)     /* 4bit/pixel */
#define         BI_BITFIELD                     (3)     /* 16,32bit/pixel */
#define         BI_JPEG                         (4)     /* JPEG Image */
#define         BI_PNG                          (5)     /* PNG Image */
#define     BMP_INFO_HDR_IMG_SIZE_POS           (20)    /* Width: 32 - Non-Compressed data size */
#define     BMP_INFO_HDR_XPELS_PER_METER_POS    (24)    /* Width: 32 - Resolution of width */
#define     BMP_INFO_HDR_YPELS_PER_METER_POS    (28)    /* Width: 32 - Resolution of height */
#define     BMP_INFO_HDR_CLR_USED_POS           (32)    /* Width: 32 - Used Num Of Color Palette(0 or 2^n) */
#define     BMP_INFO_HDR_CLR_IMPORTANT_POS      (36)    /* Width: 32 - Important Num Of Color( normaly 0 ) */
/* Since BITMAP Version4 */
#define     BMP_INFO_HDR_RED_MASK_POS           (40)
#define     BMP_INFO_HDR_GREEN_MASK_POS         (44)
#define     BMP_INFO_HDR_BLUE_MASK_POS          (48)
#define     BMP_INFO_HDR_ALPHA_MASK_POS         (52)
#define     BMP_INFO_HDR_CS_TYPE_POS            (56)
#define     BMP_INFO_HDR_RED_X_POS              (60)
#define     BMP_INFO_HDR_RED_Y_POS              (64)
#define     BMP_INFO_HDR_RED_Z_POS              (68)
#define     BMP_INFO_HDR_GREEND_X_POS           (72)
#define     BMP_INFO_HDR_GREEND_Y_POS           (76)
#define     BMP_INFO_HDR_GREEND_Z_POS           (80)
#define     BMP_INFO_HDR_BLUE_X_POS             (84)
#define     BMP_INFO_HDR_BLUE_Y_POS             (88)
#define     BMP_INFO_HDR_BLUE_Z_POS             (92)
#define     BMP_INFO_HDR_GAMMA_RED_POS          (96)
#define     BMP_INFO_HDR_GAMMA_GREEN_POS        (100)
#define     BMP_INFO_HDR_GAMMA_BLUE_POS         (104)
/* Since BITMAP Version5 */
#define     BMP_INFO_HDR_INTENT_POS             (108)
#define     BMP_INFO_HDR_PROFILE_DATA_POS       (112)
#define     BMP_INFO_HDR_PROFILE_LENGTH_POS     (116)

/* 
 ***************************************************************************
    Extract Bitmap Information MACRO Function
 ***************************************************************************
 */
#define GET_BMP_FILE_HDR_SIGNATURE(BMP_BASE)             (*(uint16_t*)((BMP_BASE) + BMP_FILE_HDR_OFFSET + BMP_FILE_HDR_SIGNATURE_POS) & BMP_16BIT_MASK)
#define GET_BMP_FILE_HDR_LENGTH(BMP_BASE)                (*(uint32_t*)((BMP_BASE) + BMP_FILE_HDR_OFFSET + BMP_FILE_HDR_LENGTH_POS) & BMP_32BIT_MASK)
#define GET_BMP_FILE_HDR_OFFSET(BMP_BASE)                (*(uint32_t*)((BMP_BASE) + BMP_FILE_HDR_OFFSET + BMP_FILE_HDR_OFFSET_POS) & BMP_32BIT_MASK)

#define GET_BMP_INFO_HDR_LENGTH(BMP_BASE)                (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_LENGTH_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_WIDTH(BMP_BASE)                 (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_WIDTH_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_HEIGHT(BMP_BASE)                (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_HEIGHT_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_PLANES(BMP_BASE)                (*(uint16_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_PLANES_POS) & BMP_16BIT_MASK)
#define GET_BMP_INFO_HDR_BIT_COUNT(BMP_BASE)             (*(uint16_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_BIT_COUNT_POS) & BMP_16BIT_MASK)
#define GET_BMP_INFO_HDR_COMPRESSION(BMP_BASE)           (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_COMPRESSION_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_IMG_SIZE(BMP_BASE)              (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_IMG_SIZE_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_XPELS_PER_METER(BMP_BASE)       (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_XPELS_PER_METER_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_YPELS_PER_METER(BMP_BASE)       (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_YPELS_PER_METER_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_CLR_USED(BMP_BASE)              (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_CLR_USED_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_CLR_IMPORTANT(BMP_BASE)         (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_CLR_IMPORTANT_POS) & BMP_32BIT_MASK)

#define GET_BMP_INFO_HDR_RED_MASK(BMP_BASE)              (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_RED_MASK_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_GREEN_MASK(BMP_BASE)            (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_GREEN_MASK_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_BLUE_MASK(BMP_BASE)             (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_BLUE_MASK_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_ALPHA_MASK(BMP_BASE)            (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_ALPHA_MASK_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_CS_TYPE(BMP_BASE)               (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_CS_TYPE_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_RED_X(BMP_BASE)                 (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_RED_X_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_RED_Y(BMP_BASE)                 (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_RED_Y_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_RED_Z(BMP_BASE)                 (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_RED_Z_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_GREEN_X(BMP_BASE)               (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_GREEND_X_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_GREEN_Y(BMP_BASE)               (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_GREEND_Y_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_GREEN_Z(BMP_BASE)               (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_GREEND_Z_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_BLUE_X(BMP_BASE)                (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_BLUE_X_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_BLUE_Y(BMP_BASE)                (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_BLUE_Y_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_BLUE_Z(BMP_BASE)                (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_BLUE_Z_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_GAMMA_RED(BMP_BASE)             (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_GAMMA_RED_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_GAMMA_GREEN(BMP_BASE)           (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_GAMMA_GREEN_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_GAMMA_BLUE(BMP_BASE)            (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_GAMMA_BLUE_POS) & BMP_32BIT_MASK)

#define GET_BMP_INFO_HDR_INTENT(BMP_BASE)                (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_INTENT_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_PROFILE_DATA(BMP_BASE)          (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_PROFILE_DATA_POS) & BMP_32BIT_MASK)
#define GET_BMP_INFO_HDR_PROFILE_LENGTH(BMP_BASE)        (*(uint32_t*)((BMP_BASE) + BMP_INFO_HDR_OFFSET + BMP_INFO_HDR_PROFILE_LENGTH_POS) & BMP_32BIT_MASK)

/* 
 ***************************************************************************
    
 ***************************************************************************
 */
typedef struct
{
    int32_t width;
    int32_t height;
    int32_t bpp;
    int32_t padding;
    int32_t stride;
    void*   raw;
    int32_t imgLen;
} SIMPLE_BMP_t;



/* 
 ***************************************************************************
    
 ***************************************************************************
 */
void BMP_ShowFileInformation(__IN void* bitmap);
void BMP_ExtractRawData(__IN void* bitmap, __INOUT SIMPLE_BMP_t* simpleBMP);

#endif  //!__BITMAP__H__

/* End Of File */
