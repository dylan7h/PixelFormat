#ifndef __PNG__H__
#define __PNG__H__

#include "common.h"
#include "endian.h"
#include "crc.h"

#define PNG_8BIT_MASK                           (0xFF)
#define PNG_16BIT_MASK                          (0xFFFF)
#define PNG_32BIT_MASK                          (0xFFFFFFFF)

/* 
 ***************************************************************************
    Common PNG File Structure
 ***************************************************************************
 */
#define PNG_FILE_SIGNATURE_OFFSET                   (0)
#define     PNG_SIGNATURE                           (0x0A1A0A0D474E5089)
#define PNG_CHUNK_ENTRY_OFFSET                      (8)
#define     PNG_CHUNK_SIZE_POS                      (0)
#define         PNG_CHUNK_SIZE_LEN                  (4)
#define     PNG_CHUNK_TYPE_POS                      (4)
#define         PNG_CHUNK_TYPE_LEN                  (4)
#define             PNG_CHUNK_TYPE_IHDR             (0x52444849)    /* "IHDR" */
#define             PNG_CHUNK_TYPE_IDAT             (0x54414449)    /* "IDAT" */
#define             PNG_CHUNK_TYPE_IEND             (0x444E4549)    /* "IEND" */
#define             PNG_CHUNK_TYPE_sRGB             (0x42475273)    /* "sRGB" */
#define             PNG_CHUNK_TYPE_pHYs             (0x73594870)    /* "pHYs" */
#define     PNG_CHUNK_DATA_POS                      (8)
#define         PNG_CHUNK_CRC_LEN                   (4)

#define GET_PNG_CHUNK_SIZE(CHUNK) *((uint32_t *)((CHUNK) + PNG_CHUNK_SIZE_POS))
#define GET_PNG_CHUNK_TYPE(CHUNK) *((uint32_t *)((CHUNK) + PNG_CHUNK_TYPE_POS))
#define GET_PNG_CHUNK_DATA_POS(CHUNK) (void *)((CHUNK) + PNG_CHUNK_DATA_POS)
#define GET_PNG_CHUNK_CRC(CHUNK) *(uint32_t *)((CHUNK) + PNG_CHUNK_DATA_POS + EndianSwap32(GET_PNG_CHUNK_SIZE(CHUNK)))
#define GET_PNG_NEXT_CHUNK(CHUNK) (void *)((CHUNK) + PNG_CHUNK_DATA_POS + EndianSwap32(GET_PNG_CHUNK_SIZE(CHUNK)) + PNG_CHUNK_CRC_LEN)


/* 
 ***************************************************************************
    PNG IHDR Structure
 ***************************************************************************
 */
#define PNG_IHDR_WIDTH_POS                          (0)
#define PNG_IHDR_HEIGHT_POS                         (4)
#define PNG_IHDR_BIT_DEPTH_POS                      (8)
#define PNG_IHDR_COLOR_TYPE_POS                     (9)
#define PNG_IHDR_COMPRESSION_METHOD_POS             (10)
#define PNG_IHDR_FILTER_METHOD_POS                  (11)
#define PNG_IHDR_INTERLACE_METHOD_POS               (12)

#define GET_PNG_IHDR_WIDTH(DATA_POS)                *(uint32_t*)((DATA_POS) + PNG_IHDR_WIDTH_POS)
#define GET_PNG_IHDR_HEIGHT(DATA_POS)               *(uint32_t*)((DATA_POS) + PNG_IHDR_HEIGHT_POS)
#define GET_PNG_IHDR_BIT_DEPTH(DATA_POS)            *(uint8_t*)((DATA_POS) + PNG_IHDR_BIT_DEPTH_POS)
#define GET_PNG_IHDR_COLOR_TYPE(DATA_POS)           *(uint8_t*)((DATA_POS) + PNG_IHDR_COLOR_TYPE_POS)
#define GET_PNG_IHDR_COMPRESSION_METHOD(DATA_POS)   *(uint8_t*)((DATA_POS) + PNG_IHDR_COMPRESSION_METHOD_POS)
#define GET_PNG_IHDR_FILTER_METHOD(DATA_POS)        *(uint8_t*)((DATA_POS) + PNG_IHDR_FILTER_METHOD_POS)
#define GET_PNG_IHDR_INTERLACE_METHOD(DATA_POS)     *(uint8_t*)((DATA_POS) + PNG_IHDR_INTERLACE_METHOD_POS)

void PNG_ShowFileInformation(void* png);

#endif  //!__PNG__H__
