/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectDraw/DDPIXELFORMAT.hpp'
*/

#pragma once

#include "WinDef.h"

namespace OpenSHC {
namespace DirectDraw {

#pragma pack(push, 1)
    // SIZE: 0x00000020
    typedef struct DDPIXELFORMAT {

        DWORD dwSize; // 0x00000000 length: 4
        DWORD dwFlags; // 0x00000004 length: 4
        DWORD dwFourCC; // 0x00000008 length: 4
        DWORD union_bitCountOrDepth; // 0x0000000C length: 4
        DWORD union_bitMask_RorY; // 0x00000010 length: 4
        DWORD union_bitMask_GorU; // 0x00000014 length: 4
        DWORD union_bitMask_BorV; // 0x00000018 length: 4
        DWORD union_bitMask_AlphaOrZBit; // 0x0000001C length: 4

    } DDPIXELFORMAT;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DDPIXELFORMAT) == 32, DDPIXELFORMAT);
} // namespace DirectDraw
} // namespace OpenSHC
