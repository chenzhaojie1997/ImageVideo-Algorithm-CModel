/* global coordinate transformation */

#ifndef _GCT_H_
#define _GCT_H_

#include "../comm/comm.h"
#include "../comm/algcomm.h"

/* global coordinate transformation by given coord [x, y] */
BOOL GCT(u8* u8OutData, u32 u32OutWidth, u32 u32OutHeight, 
        f32* f32Xcoord, f32* f32Ycoord, 
        u8* u8DataIn, u32 u32InHeight, u32 u32InWidth, 
        INTER interMethod);

#endif