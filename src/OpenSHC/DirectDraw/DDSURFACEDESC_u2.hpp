/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectDraw/DDSURFACEDESC_u2.hpp'
*/

#pragma once

#include "WinDef.h"

namespace OpenSHC {
namespace DirectDraw {

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union DDSURFACEDESC_u2 {

        DWORD dwMipMapCount; // 0x00000000 length: 4
        DWORD dwZBufferBitDepth; // 0x00000000 length: 4
        DWORD dwRefreshRate; // 0x00000000 length: 4

    } DDSURFACEDESC_u2;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DDSURFACEDESC_u2) == 4, DDSURFACEDESC_u2);
} // namespace DirectDraw
} // namespace OpenSHC
