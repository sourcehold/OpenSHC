/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectDraw/DDCAPS.hpp'
*/

#pragma once

#include "WinDef.h"
#include "ddraw.h"

namespace OpenSHC {
namespace DirectDraw {

#pragma pack(push, 1)
    // SIZE: 0x000000AC
    typedef struct DDCAPS {

        DWORD dwSize; // 0x00000000 length: 4
        DWORD dwCaps; // 0x00000004 length: 4
        DDCAPS_DX7_dwCaps2Int dwCaps2; // 0x00000008 length: 4
        DWORD dwCKeyCaps; // 0x0000000C length: 4
        DWORD dwFXCaps; // 0x00000010 length: 4
        DWORD dwFXAlphaCaps; // 0x00000014 length: 4
        DWORD dwPalCaps; // 0x00000018 length: 4
        DWORD dwSVCaps; // 0x0000001C length: 4
        DWORD dwAlphaBltConstBitDepths; // 0x00000020 length: 4
        DWORD dwAlphaBltPixelBitDepths; // 0x00000024 length: 4
        DWORD dwAlphaBltSurfaceBitDepths; // 0x00000028 length: 4
        DWORD dwAlphaOverlayConstBitDepths; // 0x0000002C length: 4
        DWORD dwAlphaOverlayPixelBitDepths; // 0x00000030 length: 4
        DWORD dwAlphaOverlaySurfaceBitDepths; // 0x00000034 length: 4
        DWORD dwZBufferBitDepths; // 0x00000038 length: 4
        DWORD dwVidMemTotal; // 0x0000003C length: 4
        DWORD dwVidMemFree; // 0x00000040 length: 4
        DWORD dwMaxVisibleOverlays; // 0x00000044 length: 4
        DWORD dwCurrVisibleOverlays; // 0x00000048 length: 4
        DWORD dwNumFourCCCodes; // 0x0000004C length: 4
        DWORD dwAlignBoundarySrc; // 0x00000050 length: 4
        DWORD dwAlignSizeSrc; // 0x00000054 length: 4
        DWORD dwAlignBoundaryDest; // 0x00000058 length: 4
        DWORD dwAlignSizeDest; // 0x0000005C length: 4
        DWORD dwAlignStrideAlign; // 0x00000060 length: 4
        DWORD dwRops[8]; // 0x00000064 length: 32
        DWORD ddsCaps; // 0x00000084 length: 4
        DWORD dwMinOverlayStretch; // 0x00000088 length: 4
        DWORD dwMaxOverlayStretch; // 0x0000008C length: 4
        DWORD dwMinLiveVideoStretch; // 0x00000090 length: 4
        DWORD dwMaxLiveVideoStretch; // 0x00000094 length: 4
        DWORD dwMinHwCodecStretch; // 0x00000098 length: 4
        DWORD dwMaxHwCodecStretch; // 0x0000009C length: 4
        DWORD dwReserved1; // 0x000000A0 length: 4
        DWORD dwReserved2; // 0x000000A4 length: 4
        DWORD dwReserved3; // 0x000000A8 length: 4

    } DDCAPS;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DDCAPS) == 172, DDCAPS);
} // namespace DirectDraw
} // namespace OpenSHC
