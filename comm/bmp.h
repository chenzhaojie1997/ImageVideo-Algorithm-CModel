#ifndef _BMP_H_
#define _BMP_H_

#include "comm.h"

BOOL BmpOrderToNormal(char* nrmOrder, const char* bmpOrder, int width, int height);
BOOL NormalOrderToBmp(char* bmpOrder, char* nrmOrder, int width, int height);

typedef struct BmpHeadType
{
    char bmpType[2];
} BmpHeadType;

typedef struct BmpHeadSize
{
    int sizeOfFile; // 文件大小
    int reserved; // 保留值
    int sizeOfBmpHead; // BMP文件头大小
    int sizeOfBmpInfo; // BMP文件头信息部分大小
    int imgWidth; // 图宽
    int imgHeight; // 图高
} BmpHeadSize;

typedef struct BmpHeadFix
{
    char fix[2];
    char bits[2]; // BMP 位图
} BmpHeadFix;

typedef struct BmpHeadColor
{
    int compressedWay;
    int sizeOfBmpData;
    int horizontalResolution;
    int verticalResolution;
    int color[2];
} BmpHeadColor;

#endif