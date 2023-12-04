#include "comm.h"
#include "bmp.h"

void SafeFree(void** p)
{
    if (NULL == *p);
    else {
        free(*p);
        *p = NULL;
    }
}

BOOL ReadBmp(char* data, const char* name, const u32 height, const u32 width)
{
    FILE* fp = fopen(name, "rb"); // read image by bit
    if (NULL == fp) {
        printf("[ERROR]: @ReadBmp %s fopen\n", name);
        return FAILURE;
    }

    if (width % 4 != 0) { // support width % 4 == 0 only
        printf("[ERROR]: @ReadBmp %s support width%%4==0\n only\n");
        return FAILURE;
    }

    if (NULL == data) {
        printf("[ERROR]: @ReadBmp data null\n");
        return FAILURE;
    }

    char* bmpOrder = (char*) malloc(width * height * 3 * sizeof(char));
    if (NULL == bmpOrder) {
        printf("[ERROR]: @ReadBmp bmp order malloc error\n");
        return FAILURE;
    }

    fseek(fp, 54, SEEK_SET); // skip useless information

    idxtype i;
    for (i = 0; i < height * width * 3; ++i) {
        fread(bmpOrder + i, 1, 1, fp);
    }
    fclose(fp);
    return BmpOrderToNormal(data, bmpOrder, width, height);
}

BOOL WriteBmp(char* data, const char* name, const u32 height, const u32 width) {
    if (NULL == data) {
        printf("[ERROR]: @WriteBmp data NULL\n");
        return FAILURE;
    }

    FILE* fp = fopen(name, "wb"); // write binary file
    if (NULL == fp) {
        printf("[ERROR]: @WriteBmp fp NULL\n");
        return FAILURE;
    }

    BmpHeadType* bmptype = (BmpHeadType*) malloc(sizeof(BmpHeadType));
    if (NULL == bmptype) {
        printf("[ERROR]: @WriteBmp bmptype NULL\n");
        return FAILURE;
    }
    bmptype->bmpType[0] = 'B';
    bmptype->bmpType[1] = 'M';
    fwrite(bmptype, 1, sizeof(BmpHeadType), fp);

    BmpHeadSize* bmpsize = (BmpHeadSize*) malloc(sizeof(BmpHeadSize));
    if (NULL == bmpsize) {
        printf("[ERROR]: @WriteBmp bmpsize NULL\n");
        return FAILURE;
    }
    bmpsize->sizeOfFile = width * height * 3 + 54; // head + data
    bmpsize->reserved = 0;
    bmpsize->sizeOfBmpHead = 54;
    bmpsize->sizeOfBmpInfo = 40;
    bmpsize->imgWidth = width;
    bmpsize->imgHeight = height;
    fwrite(bmpsize, 4, sizeof(BmpHeadSize) / 4, fp);

    BmpHeadFix* bmpfix = (BmpHeadFix*) malloc(sizeof(BmpHeadFix));
    if (NULL == bmpfix) {
        printf("[ERROR]: @WriteBmp bmpfix NULL\n");
        return FAILURE;
    }
    bmpfix->fix[0] = 0;
    bmpfix->fix[1] = 0;
    bmpfix->bits[0] = 24;
    bmpfix->bits[1] = 0;
    fwrite(bmpfix, 1, sizeof(BmpHeadFix), fp);

    BmpHeadColor* bmpcolor = (BmpHeadColor*) malloc(sizeof(BmpHeadColor));
    if (NULL == bmpcolor) {
        printf("[ERROR]: @WriteBmp bmpcolor NULL\n");
        return FAILURE;
    }
    bmpcolor->compressedWay = 0;
    bmpcolor->sizeOfBmpData = width * height * 3;
    bmpcolor->horizontalResolution = 0;
    bmpcolor->verticalResolution = 0;
    bmpcolor->color[0] = 0;
    bmpcolor->color[1] = 0;
    fwrite(bmpcolor, 4, sizeof(BmpHeadColor) / 4, fp);

    char* bmpOrder = (char*) malloc(width * height * 3);
    if (NULL == bmpOrder) {
        printf("[ERROR]: @WriteBmp bmpOrder NULL\n");
        return FAILURE;
    }

    if (FAILURE == NormalOrderToBmp(bmpOrder, data, width, height)) {
        printf("[ERROR]: @WrtieBmp NormalOrderToBmp FAIL\n");
        return FAILURE;
    }

    fwrite(bmpOrder, 1, width * height * 3, fp);
    free(bmpOrder);
    fclose(fp);
    return SUCCESS;
}