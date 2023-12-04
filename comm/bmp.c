#include "comm.h"

BOOL BmpOrderToNormal(char* nrmOrder, const char* bmpOrder, int width, int height) {
    if (NULL == nrmOrder) {
        printf("[ERROR]: @BmpOrderToNormal nrmOrder NULL\n");
        return FAILURE;
    }

    if (NULL == bmpOrder) {
        printf("[ERROR]: @BmpOrderToNormal bmpOrder NULL\n");
        return FAILURE;
    }

    idxtype x, y, c;
    for (x = 0; x < height; ++x) {
        for (y = 0; y < width; ++y) {
            for (c = 0; c < 3; ++c) {
                nrmOrder[(x * width + y) * 3 + c] = bmpOrder[((height - 1 - x) * width + y) * 3 + c];
            }
        }
    }
    return SUCCESS;
}

BOOL NormalOrderToBmp(char* bmpOrder, char* nrmOrder, int width, int height) {
    if (NULL == bmpOrder) {
        printf("[ERROR]: @NormalOrderToBmp bmpOrder NULL\n");
        return FAILURE;
    }

    if (NULL == nrmOrder) {
        printf("[ERROR]: @NormalOrderToBmp nrmOrder NULL\n");
        return FAILURE;
    }

    idxtype x, y, c;
    for (x = 0; x < height; ++x) {
        for (y = 0; y < width; ++y) {
            for (c = 0; c < 3; ++c) {
                bmpOrder[((height - x - 1) * width + y) * 3 + c] = nrmOrder[(x * width + y) * 3 + c];
            }
        }
    }
}