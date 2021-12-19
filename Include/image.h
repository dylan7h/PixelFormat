#ifndef __IMAGE__H__
#define __IMAGE__H__

#include "common.h"

/* RGB Domain */
void IMG_MakeBGRAtoBGR24(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgra,
                            __INOUT int32_t* bgr24stride, __INOUT void** bgr24, __INOUT int32_t* bgr24len);
void IMG_MakeBGR24toBGR565le(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24,
                                __INOUT int32_t* bgr565lestride, __INOUT void** bgr565le, __INOUT int32_t* bgr565lelen);
void IMG_MakeBGR24toBGR555le(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24,
                                __INOUT int32_t* bgr555lestride, __INOUT void** bgr555le, __INOUT int32_t* bgr555lelen);
void IMG_MakeBGR24toBGR565be(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24,
                                __INOUT int32_t* bgr565bestride, __INOUT void** bgr565be, __INOUT int32_t* bgr565belen);
void IMG_MakeBGR24toBGR555be(   __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24,
                                __INOUT int32_t* bgr555bestride, __INOUT void** bgr555be, __INOUT int32_t* bgr555belen);

/* YUV Domain */
void IMG_MakeBGR24toYUV444( __IN int32_t width, __IN int32_t height, __IN int32_t stride, __IN void* bgr24, 
                            __INOUT void** yuv444, __INOUT int32_t* yuv444len);
void IMG_MakeYUV444toYUV444p(   __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                                __INOUT void** yuv444p, __INOUT int32_t* yuv444plen);
void IMG_MakeYUV444toYUYV422(    __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                                __INOUT void** yuyv422, __INOUT int32_t* yuyv422len);
void IMG_MakeYUV444toYUV422p(   __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                                __INOUT void** yuv422p, __INOUT int32_t* yuv422plen);
void IMG_MakeYUV444toYUV420p(   __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                                __INOUT void** yuv420p, __INOUT int32_t* yuv420plen);
void IMG_MakeYUV444toNV12(  __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                            __INOUT void** nv12, __INOUT int32_t* nv12len);
void IMG_MakeYUV444toNV21(  __IN int32_t width, __IN int32_t height, __IN void* yuv444, 
                            __INOUT void** nv21, __INOUT int32_t* nv21len);

#endif  //!__IMAGE__H__
