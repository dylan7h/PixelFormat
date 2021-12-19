#include "crc.h"

/* Table of CRCs of all 8-bit messages. */
uint64_t crc_table[256];

/* Flag: has the table been computed? Initially false. */
int crc_table_computed = 0;

/* Make the table for a fast CRC. */
void make_crc_table(void)
{
    uint64_t c;
    int32_t n, k;

    for (n = 0; n < 256; n++)
    {
        c = (uint64_t)n;
        for (k = 0; k < 8; k++)
        {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc_table[n] = c;
    }
    crc_table_computed = 1;
}

/* Update a running CRC with the bytes buf[0..len-1]--the CRC
      should be initialized to all 1's, and the transmitted value
      is the 1's complement of the final running CRC (see the
      crc() routine below). */

uint64_t update_crc(uint64_t crc, uint8_t *buf,
                         int32_t len)
{
    uint64_t c = crc;
    int32_t n;

    if (!crc_table_computed)
        make_crc_table();
    for (n = 0; n < len; n++)
    {
        c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }
    return c;
}

/* Return the CRC of the bytes buf[0..len-1]. */
uint64_t crc(uint8_t *buf, int32_t len)
{
    return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;
}
