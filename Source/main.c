#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "load.h"
#include "bitmap.h"
#include "image.h"

int main(int argc, char* argv[]) 
{
    char path[255];
    void* pMem = NULL;
    SIMPLE_BMP_t bgra, bmp;

    /* bgra_1280x720 */
    sprintf(path, "%s/%s", argv[1], "bgra_1280x720.bmp");
    loadFile(path, &pMem, &bgra.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bgra, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bgra);
    sprintf(path, "%s/%s", argv[1], "bgra_1280x720.raw");
    saveFile(path, bgra.raw, bgra.imgLen);
    SAFE_FREE(pMem);

    /* bgr24_1277x720 */
    sprintf(path, "%s/%s", argv[1], "bgr24_1277x720.bmp");
    loadFile(path, &pMem, &bmp.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bmp, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bmp);
    sprintf(path, "%s/%s", argv[1], "bgr24_1277x720.raw");
    saveFile(path, bmp.raw, bmp.imgLen);
    SAFE_FREE(pMem);
    SAFE_FREE(bmp.raw);

    /* bgr_16bpp_1277x720 */
    sprintf(path, "%s/%s", argv[1], "bgr_16bpp_1277x720.bmp");
    loadFile(path, &pMem, &bmp.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bmp, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bmp);
    sprintf(path, "%s/%s", argv[1], "bgr_16bpp_1277x720.raw");
    saveFile(path, bmp.raw, bmp.imgLen);
    SAFE_FREE(pMem);
    SAFE_FREE(bmp.raw);

    /* bgr_4bpp_1277x720 */
    sprintf(path, "%s/%s", argv[1], "bgr_4bpp_1277x720.bmp");
    loadFile(path, &pMem, &bmp.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bmp, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bmp);
    sprintf(path, "%s/%s", argv[1], "bgr_4bpp_1277x720.raw");
    saveFile(path, bmp.raw, bmp.imgLen);
    SAFE_FREE(pMem);
    SAFE_FREE(bmp.raw);

    /* bgr_1bpp_1277x720 */
    sprintf(path, "%s/%s", argv[1], "bgr_1bpp_1277x720.bmp");
    loadFile(path, &pMem, &bmp.imgLen);
    BMP_ShowFileInformation(pMem);
    memset((void*)&bmp, 0, sizeof(SIMPLE_BMP_t));
    BMP_ExtractRawData(pMem, &bmp);
    sprintf(path, "%s/%s", argv[1], "bgr_1bpp_1277x720.raw");
    saveFile(path, bmp.raw, bmp.imgLen);
    SAFE_FREE(pMem);
    SAFE_FREE(bmp.raw);

    /* bgra_1280x720.bmp to bgr24_1280x720.raw */
    int32_t bgr24stride, bgr24len;
    void*   bgr24;
    IMG_MakeBGRAtoBGR24(bgra.width, bgra.height, bgra.stride, bgra.raw,
                        &bgr24stride, &bgr24, &bgr24len);
    sprintf(path, "%s/%s", argv[1], "bgr24_1280x720.raw");
    saveFile(path, bgr24, bgr24len);

    /* bgr24_1280x720.raw to bgr565le_1280x720.raw */
    int32_t bgr565lestride, bgr565lelen;
    void*   bgr565le;
    IMG_MakeBGR24toBGR565le(bgra.width, bgra.height, bgr24stride, bgr24,
                            &bgr565lestride, &bgr565le, &bgr565lelen);
    sprintf(path, "%s/%s", argv[1], "bgr565le_1280x720.raw");
    saveFile(path, bgr565le, bgr565lelen);
    SAFE_FREE(bgr565le);

    /* bgr24_1280x720.raw to bgr555le_1280x720.raw */
    int32_t bgr555lestride, bgr555lelen;
    void*   bgr555le;
    IMG_MakeBGR24toBGR555le(bgra.width, bgra.height, bgr24stride, bgr24,
                            &bgr555lestride, &bgr555le, &bgr555lelen);
    sprintf(path, "%s/%s", argv[1], "bgr555le_1280x720.raw");
    saveFile(path, bgr555le, bgr555lelen);
    SAFE_FREE(bgr555le);

    /* bgr24_1280x720.raw to bgr565be_1280x720.raw */
    int32_t bgr565bestride, bgr565belen;
    void*   bgr565be;
    IMG_MakeBGR24toBGR565be(bgra.width, bgra.height, bgr24stride, bgr24,
                            &bgr565bestride, &bgr565be, &bgr565belen);
    sprintf(path, "%s/%s", argv[1], "bgr565be_1280x720.raw");
    saveFile(path, bgr565be, bgr565belen);
    SAFE_FREE(bgr565be);

    /* bgr24_1280x720.raw to bgr555be_1280x720.raw */
    int32_t bgr555bestride, bgr555belen;
    void*   bgr555be;
    IMG_MakeBGR24toBGR555be(bgra.width, bgra.height, bgr24stride, bgr24,
                            &bgr555bestride, &bgr555be, &bgr555belen);
    sprintf(path, "%s/%s", argv[1], "bgr555be_1280x720.raw");
    saveFile(path, bgr555be, bgr555belen);
    SAFE_FREE(bgr555be);

    return 0;
}
