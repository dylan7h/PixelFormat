#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "load.h"
#include "bitmap.h"

int main(int argc, char* argv[]) 
{
    char path[255];
    void* pMem = NULL;
    SIMPLE_BMP_t bmp;

    /* hsv_1280x720_alpha */
    sprintf(path, "%s/%s", argv[1], "hsv_1280x720_alpha.bmp");
    loadFile(path, &pMem, &bmp.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bmp, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bmp);
    sprintf(path, "%s/%s", argv[1], "hsv_1280x720_alpha.raw");
    saveFile(path, bmp.raw, bmp.imgLen);
    SAFE_FREE(pMem);
    SAFE_FREE(bmp.raw);

    /* BGR24_1277x720 */
    sprintf(path, "%s/%s", argv[1], "BGR24_1277x720.bmp");
    loadFile(path, &pMem, &bmp.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bmp, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bmp);
    sprintf(path, "%s/%s", argv[1], "BGR24_1277x720.raw");
    saveFile(path, bmp.raw, bmp.imgLen);
    SAFE_FREE(pMem);
    SAFE_FREE(bmp.raw);

    /* BGR_16bpp_1277x720 */
    sprintf(path, "%s/%s", argv[1], "BGR_16bpp_1277x720.bmp");
    loadFile(path, &pMem, &bmp.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bmp, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bmp);
    sprintf(path, "%s/%s", argv[1], "BGR_16bpp_1277x720.raw");
    saveFile(path, bmp.raw, bmp.imgLen);
    SAFE_FREE(pMem);
    SAFE_FREE(bmp.raw);

    /* BGR_4bpp_1277x720 */
    sprintf(path, "%s/%s", argv[1], "BGR_4bpp_1277x720.bmp");
    loadFile(path, &pMem, &bmp.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bmp, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bmp);
    sprintf(path, "%s/%s", argv[1], "BGR_4bpp_1277x720.raw");
    saveFile(path, bmp.raw, bmp.imgLen);
    SAFE_FREE(pMem);
    SAFE_FREE(bmp.raw);

    return 0;
}
