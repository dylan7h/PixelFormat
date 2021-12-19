#include "endian.h"

uint16_t EndianSwap16(uint16_t val)
{
    return (uint16_t)(((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8));
}

uint32_t EndianSwap32(uint32_t val)
{
    uint32_t result = 0;

	result |= (val & 0xFF000000) >> 24;
	result |= (val & 0x00FF0000) >> 8;
	result |= (val & 0x0000FF00) << 8;
	result |= (val & 0x000000FF) << 24;

	return result;
}