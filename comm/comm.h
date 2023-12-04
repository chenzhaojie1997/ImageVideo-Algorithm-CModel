#ifndef _COMM_H_
#define _COMM_H_

#include <stdio.h>
#include <stdlib.h>

typedef char          s8;
typedef unsigned char u8;
typedef int           s32;
typedef unsigned int  u32;
typedef float         f32;
typedef double        f64;

// index data type
typedef int       idxtype;
typedef long long idxlltype;

enum _BOOL
{
    SUCCESS = 0,
    FAILURE = 1
};
typedef enum _BOOL BOOL;

/* free the point to data safely */
void SafeFree(void** p);

/* read bmp; support width % 4 == 0 only */
BOOL ReadBmp(char* data, const char* name, const u32 height, const u32 width);

/* wrtie bmp; support width % 4 == 0 only */
BOOL WriteBmp(char* data, const char* name, const u32 height, const u32 width);

#endif
