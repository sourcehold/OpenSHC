/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectDraw/DDSURFACEDESC.hpp'
*/

#pragma once

#include "WinDef.h"
#include "ddraw.h"

namespace OpenSHC {
namespace DirectDraw {

#pragma pack(push, 1)
    // SIZE: 0x0000006C
    typedef struct DDSURFACEDESC {

        DWORD dwSize; // 0x00000000 length: 4
        DWORD dwFlags; // 0x00000004 length: 4
        DWORD dwHeight; // 0x00000008 length: 4
        DWORD dwWidth; // 0x0000000C length: 4
        DDSURFACEDESC_u1 pitchOrLinearSize; // 0x00000010 length: 4
        DWORD dwBackBufferCount; // 0x00000014 length: 4
        DDSURFACEDESC_u2 mipMapCountOrZBufferBitDepthOrRefreshRate; // 0x00000018 length: 4
        DWORD dwAlphaBitDepth; // 0x0000001C length: 4
        DWORD dwReserved; // 0x00000020 length: 4
        LPVOID lpSurface; // 0x00000024 length: 4
        DDCOLORKEY ddckCKDestOverlay; // 0x00000028 length: 8
        DDCOLORKEY ddckCKDestBlt; // 0x00000030 length: 8
        DDCOLORKEY ddckCKSrcOverlay; // 0x00000038 length: 8
        DDCOLORKEY ddckCKSrcBlt; // 0x00000040 length: 8
        DDPIXELFORMAT ddpfPixelFormat; // 0x00000048 length: 32
        DWORD ddsCaps; // 0x00000068 length: 4

    } DDSURFACEDESC;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DDSURFACEDESC) == 108, DDSURFACEDESC);
} // namespace DirectDraw
} // namespace OpenSHC
