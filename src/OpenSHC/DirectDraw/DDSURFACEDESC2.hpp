/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectDraw/DDSURFACEDESC2.hpp'
*/

#pragma once

#include "WinDef.h"
#include "ddraw.h"

namespace OpenSHC {
namespace DirectDraw {

#pragma pack(push, 1)
    // SIZE: 0x000000B8
    typedef struct DDSURFACEDESC2 {

        DWORD dwSize; // 0x00000000 length: 4
        DWORD dwFlags; // 0x00000004 length: 4
        DWORD dwHeight; // 0x00000008 length: 4
        DWORD dwWidth; // 0x0000000C length: 4
        long lPitch; // 0x00000010 length: 4
        DWORD dwLinearSize; // 0x00000014 length: 4
        DWORD dwBackBufferCount; // 0x00000018 length: 4
        DWORD dwDepth; // 0x0000001C length: 4
        DWORD dwMipMapCount; // 0x00000020 length: 4
        DWORD dwRefreshRate; // 0x00000024 length: 4
        DWORD dwSrcVBHandle; // 0x00000028 length: 4
        DWORD dwAlphaBitDepth; // 0x0000002C length: 4
        DWORD dwReserved; // 0x00000030 length: 4
        LPVOID lpSurface; // 0x00000034 length: 4
        DDCOLORKEY ddckCKDestOverlay; // 0x00000038 length: 8
        DWORD dwEmptyFaceColor; // 0x00000040 length: 4
        DDCOLORKEY ddckCKDestBlt; // 0x00000044 length: 8
        DDCOLORKEY ddckCKSrcOverlay; // 0x0000004C length: 8
        DDCOLORKEY ddckCKSrcBlt; // 0x00000054 length: 8
        DDPIXELFORMAT ddpfPixelFormat; // 0x0000005C length: 32
        undefined1 padding_0x7c[32]; // 0x0000007C length: 32
        DWORD dwFVF; // 0x0000009C length: 4
        DDSCAPS2 ddsCaps; // 0x000000A0 length: 16
        undefined1 padding_0xb0[4]; // 0x000000B0 length: 4
        DWORD dwTextureStage; // 0x000000B4 length: 4

    } DDSURFACEDESC2;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DDSURFACEDESC2) == 184, DDSURFACEDESC2);
} // namespace DirectDraw
} // namespace OpenSHC
