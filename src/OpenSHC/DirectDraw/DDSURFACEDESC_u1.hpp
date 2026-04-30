/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectDraw/DDSURFACEDESC_u1.hpp'
*/

#pragma once

#include "WinDef.h"

namespace OpenSHC {
namespace DirectDraw {

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union DDSURFACEDESC_u1 {

        long lPitch; // 0x00000000 length: 4
        DWORD dwLinearSize; // 0x00000000 length: 4

    } DDSURFACEDESC_u1;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DDSURFACEDESC_u1) == 4, DDSURFACEDESC_u1);
} // namespace DirectDraw
} // namespace OpenSHC
