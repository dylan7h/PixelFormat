#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "image.h"

/* RGB Domain */
void IMG_MakeBGRAtoBGR24(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgra,
                            __INOUT int32_t* bgr24stride, __INOUT void** bgr24, __INOUT int32_t* bgr24len)
{
    int32_t padding;

    padding = (((BPP24 * width) / BYTE_PER_BITS) % BYTE4_ALIGN);
    if(padding != 0)
    {
        padding = BYTE4_ALIGN - padding;
    }
    *bgr24stride    = ((BPP24 * width) / BYTE_PER_BITS) + padding;
    *bgr24len       = height * (*bgr24stride);
    *bgr24          = malloc(*bgr24len);
    assert((*bgr24) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dst;

    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(bgra + (row * stride) + (col * (BPP32 / BYTE_PER_BITS)));
            dst = (uint8_t*)((*bgr24) + (row * (*bgr24stride)) + (col * (BPP24 / BYTE_PER_BITS)));

            dst[0] = src[0];    /* Blue */
            dst[1] = src[1];    /* Green */
            dst[2] = src[2];    /* Red */
            // ?   = src[3]     /* Alpha */
        }
    }
}

void IMG_MakeBGR24toBGR565le(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24,
                                __INOUT int32_t* bgr565lestride, __INOUT void** bgr565le, __INOUT int32_t* bgr565lelen)
{
    int32_t padding;

    padding = (((BPP16 * width) / BYTE_PER_BITS) % BYTE4_ALIGN);
    if(padding != 0)
    {
        padding = BYTE4_ALIGN - padding;
    }
    *bgr565lestride    = ((BPP16 * width) / BYTE_PER_BITS) + padding;
    *bgr565lelen       = height * (*bgr565lestride);
    *bgr565le          = malloc(*bgr565lelen);
    assert((*bgr565le) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dst;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(bgr24 + (row * stride) + (col * (BPP24 / BYTE_PER_BITS)));
            dst = (uint8_t*)((*bgr565le) + (row * (*bgr565lestride)) + ((col * BPP16) / BYTE_PER_BITS));
            
            /* 
                src[0]: Blue
                src[1]: Green
                src[2]: Red
            */
            /* Low Order Byte */
            dst[0] = ((src[1] >> 2) << 5) | (src[2] >> 3);
            /* High Order Byte */
            dst[1] = ((src[0] >> 3) << 3) | ((src[1] >> 2) >> 3);
        }
    }
}

void IMG_MakeBGR24toBGR555le(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24,
                                __INOUT int32_t* bgr555lestride, __INOUT void** bgr555le, __INOUT int32_t* bgr555lelen)
{
    int32_t padding;

    padding = (((BPP16 * width) / BYTE_PER_BITS) % BYTE4_ALIGN);
    if(padding != 0)
    {
        padding = BYTE4_ALIGN - padding;
    }
    *bgr555lestride    = ((BPP16 * width) / BYTE_PER_BITS) + padding;
    *bgr555lelen       = height * (*bgr555lestride);
    *bgr555le          = malloc(*bgr555lelen);
    assert((*bgr555le) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dst;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(bgr24 + (row * stride) + (col * (BPP24 / 8)));
            dst = (uint8_t*)((*bgr555le) + (row * (*bgr555lestride)) + (col * (BPP16 / 8)));
            
            /* 
                src[0]: Blue
                src[1]: Green
                src[2]: Red
            */
            /* Low Order Byte */
            dst[0] = ((src[1] >> 3) << 5) | (src[2] >> 3);
            /* High Order Byte */
            dst[1] = ((src[0] >> 3) << 2) | ((src[1] >> 3) >> 3);
        }
    }
}

void IMG_MakeBGR24toBGR565be(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24,
                                __INOUT int32_t* bgr565bestride, __INOUT void** bgr565be, __INOUT int32_t* bgr565belen)
{
    int32_t padding;

    padding = (((BPP16 * width) / BYTE_PER_BITS) % BYTE4_ALIGN);
    if(padding != 0)
    {
        padding = BYTE4_ALIGN - padding;
    }
    *bgr565bestride    = ((BPP16 * width) / BYTE_PER_BITS) + padding;
    *bgr565belen       = height * (*bgr565bestride);
    *bgr565be          = malloc(*bgr565belen);
    assert((*bgr565be) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dst;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(bgr24 + (row * stride) + (col * (BPP24 / BYTE_PER_BITS)));
            dst = (uint8_t*)((*bgr565be) + (row * (*bgr565bestride)) + (col * (BPP16 / BYTE_PER_BITS)));
            
            /* 
                src[0]: Blue
                src[1]: Green
                src[2]: Red
            */
            /* Low Order Byte */
            dst[1] = ((src[1] >> 2) << 5) | (src[2] >> 3);
            /* High Order Byte */
            dst[0] = ((src[0] >> 3) << 3) | ((src[1] >> 2) >> 3);
        }
    }
}

void IMG_MakeBGR24toBGR555be(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24,
                                __INOUT int32_t* bgr555bestride, __INOUT void** bgr555be, __INOUT int32_t* bgr555belen)
{
    int32_t padding;

    padding = (((BPP16 * width) / BYTE_PER_BITS) % BYTE4_ALIGN);
    if(padding != 0)
    {
        padding = BYTE4_ALIGN - padding;
    }
    *bgr555bestride    = ((BPP16 * width) / BYTE_PER_BITS) + padding;
    *bgr555belen       = height * (*bgr555bestride);
    *bgr555be          = malloc(*bgr555belen);
    assert((*bgr555be) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dst;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(bgr24 + (row * stride) + (col * (BPP24 / BYTE_PER_BITS)));
            dst = (uint8_t*)((*bgr555be) + (row * (*bgr555bestride)) + (col * (BPP16 / BYTE_PER_BITS)));
            
            /* 
                src[0]: Blue
                src[1]: Green
                src[2]: Red
            */
            /* Low Order Byte */
            dst[1] = ((src[1] >> 3) << 5) | (src[2] >> 3);
            /* High Order Byte */
            dst[0] = ((src[0] >> 3) << 2) | ((src[1] >> 3) >> 3);
        }
    }
}


/* YUV Domain */
void IMG_MakeBGR24toYUV444( __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24, 
                            __INOUT void** yuv444, __INOUT int32_t* yuv444len)
{
    *yuv444len = width * height * (BPP24 / BYTE_PER_BITS);
    *yuv444 = malloc(*yuv444len);
    assert((*yuv444) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dst;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(bgr24 + (row * stride) + (col * (BPP24 / BYTE_PER_BITS)));
            dst = (uint8_t*)((*yuv444) + (row * (width * (BPP24 / BYTE_PER_BITS))) + (col * (BPP24 / BYTE_PER_BITS)));
            /* 
                Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16
                U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128
                V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128 
            */
            dst[0] = ( (  66 * src[2] + 129 * src[1] +  25 * src[0] + 128) >> 8) +  16;
            dst[1] = ( ( -38 * src[2] -  74 * src[1] + 112 * src[0] + 128) >> 8) + 128;
            dst[2] = ( ( 112 * src[2] -  94 * src[1] -  18 * src[0] + 128) >> 8) + 128;
        }
    }
}

void IMG_MakeYUV444toYUV444p(   __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                                __INOUT void** yuv444p, __INOUT int32_t* yuv444plen)
{
    *yuv444plen = width * height * (BPP24 / BYTE_PER_BITS);
    *yuv444p = malloc(*yuv444plen);
    assert((*yuv444p) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dstY;
    uint8_t* dstU;
    uint8_t* dstV;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src     = (uint8_t*)(yuv444 + (row * (width * (BPP24 / BYTE_PER_BITS))) + (col * (BPP24 / BYTE_PER_BITS)));
            dstY    = (uint8_t*)((*yuv444p) + (row * width) + col);
            dstU    = dstY + (width * height);
            dstV    = dstU + (width * height);
           
           *dstY    = src[0];
           *dstU    = src[1];
           *dstV    = src[2];
        }
    }
}

void IMG_MakeYUV444toYUYV422(   __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                                __INOUT void** yuyv422, __INOUT int32_t* yuyv422len)
{
    *yuyv422len = ((BPP16 / BYTE_PER_BITS) * width) * height;
    *yuyv422 = malloc(*yuyv422len);
    assert((*yuyv422) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dst;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(yuv444 + (row * (width * (BPP24 / BYTE_PER_BITS))) + (col * (BPP24 / BYTE_PER_BITS)));
            dst = (uint8_t*)((*yuyv422) + (row * (width * (BPP16 / BYTE_PER_BITS))) + (col * (BPP16 / BYTE_PER_BITS)));

            dst[0] = src[0];        /* Y */
            if((col % 2) == 0)
            {
                dst[1] = src[1];    /* U */
            }
            else
            {
                src = src - (BPP24 / BYTE_PER_BITS);
                dst[1] = src[2];    /* V */
            }
        }
    }
}

void IMG_MakeYUV444toYUV422p(   __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                                __INOUT void** yuv422p, __INOUT int32_t* yuv422plen)
{
    *yuv422plen = ((BPP16 / BYTE_PER_BITS) * width) * height;
    *yuv422p = malloc(*yuv422plen);
    assert((*yuv422p) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dstY;
    uint8_t* dstU;
    uint8_t* dstV;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(yuv444 + (row * (width * (BPP24 / BYTE_PER_BITS))) + (col * (BPP24 / BYTE_PER_BITS)));
            dstY = (uint8_t*)((*yuv422p) + (row * width) + col);

            *dstY = src[0];         /* Y */
            if((col % 2) == 0)
            {
                dstU = (uint8_t*)((*yuv422p) + (width * height) + ((width / 2) * row) + (col / 2));
                *dstU = src[1];     /* U */
            }
            else
            {
                src     = src - (BPP24 / BYTE_PER_BITS);
                dstV    = (uint8_t*)((*yuv422p) + (width * height) + ((width / 2) * height)  + ((width / 2) * row) + (col / 2));
                *dstV   = src[2];   /* V */
            }
        }
    }
}

void IMG_MakeYUV444toYUV420p(   __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                                __INOUT void** yuv420p, __INOUT int32_t* yuv420plen)
{
    *yuv420plen = ((BPP16 / BYTE_PER_BITS) * width) * height;
    *yuv420p = malloc(*yuv420plen);
    assert((*yuv420p) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dstY;
    uint8_t* dstU;
    uint8_t* dstV;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(yuv444 + (row * (width * (BPP24 / BYTE_PER_BITS))) + (col * (BPP24 / BYTE_PER_BITS)));
            dstY = (uint8_t*)((*yuv420p) + (row * width) + col);

            *dstY = src[0];             /* Y */
            if((row % 2) == 0)
            {
                if((col % 2) == 0)
                {
                    dstU    = (uint8_t*)((*yuv420p) + (width * height) + ((width / 2) * (row / 2)) + (col / 2));
                    *dstU   = src[1];   /* U */
                }
                else
                {
                    src     = src - (BPP24 / BYTE_PER_BITS);
                    dstV    = (uint8_t*)((*yuv420p) + (width * height) + ((width / 2) * (height / 2))  + ((width / 2) * (row / 2)) + (col / 2));
                    *dstV   = src[2];   /* V */
                }
            }
        }
    }
}

void IMG_MakeYUV444toNV12(  __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                            __INOUT void** nv12, __INOUT int32_t* nv12len)
{
    *nv12len = ((BPP16 / BYTE_PER_BITS) * width) * height;
    *nv12 = malloc(*nv12len);
    assert((*nv12) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dstY;
    uint8_t* dstUV;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(yuv444 + (row * (width * (BPP24 / BYTE_PER_BITS))) + (col * (BPP24 / BYTE_PER_BITS)));
            dstY = (uint8_t*)((*nv12) + (row * width) + col);

            *dstY               = src[0];   /* Y */
            if((row % 2) == 0)
            {
                dstUV = (uint8_t*)((*nv12) + (width * height) + (width * (row / 2)) + col);
                if((col % 2) == 0)
                {
                    *dstUV      = src[1];   /* U */
                }
                else
                {
                    src         = src - (BPP24 / BYTE_PER_BITS);
                    *dstUV      = src[2];   /* V */
                }
            }
        }
    }
}

void IMG_MakeYUV444toNV21(  __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                            __INOUT void** nv21, __INOUT int32_t* nv21len)
{
    *nv21len = ((BPP16 / BYTE_PER_BITS) * width) * height;
    *nv21 = malloc(*nv21len);
    assert((*nv21) != NULL);

    int32_t row, col;
    uint8_t* src;
    uint8_t* dstY;
    uint8_t* dstUV;
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            src = (uint8_t*)(yuv444 + (row * (width * (BPP24 / BYTE_PER_BITS))) + (col * (BPP24 / BYTE_PER_BITS)));
            dstY = (uint8_t*)((*nv21) + (row * width) + col);

            *dstY               = src[0];   /* Y */
            if((row % 2) == 0)
            {
                dstUV = (uint8_t*)((*nv21) + (width * height) + (width * (row / 2)) + col);
                if((col % 2) != 0)
                {
                    *dstUV      = src[1];   /* U */
                }
                else
                {
                    src         = src - (BPP24 / BYTE_PER_BITS);
                    *dstUV      = src[2];   /* V */
                }
            }
        }
    }
}

