/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectDraw/IDirectDrawSurfaceInterface/IDirectDrawSurface_VTABLE.hpp'
*/

#pragma once

#include "ddraw.h"

namespace OpenSHC {
namespace DirectDraw {
    namespace IDirectDrawSurfaceInterface {

#pragma pack(push, 1)
        // SIZE: 0x00000084
        typedef struct IDirectDrawSurface_VTABLE {

            undefined1 padding_0x0[8]; // 0x00000000 length: 8
            Release* Release; // 0x00000008 length: 4
            undefined1 padding_0xc[8]; // 0x0000000C length: 8
            Blt* Blt; // 0x00000014 length: 4
            undefined1 padding_0x18[4]; // 0x00000018 length: 4
            BltFast* BltFast; // 0x0000001C length: 4
            undefined1 padding_0x20[12]; // 0x00000020 length: 12
            Flip* Flip; // 0x0000002C length: 4
            GetAttachedSurface* GetAttachedSurface; // 0x00000030 length: 4
            undefined1 padding_0x34[36]; // 0x00000034 length: 36
            GetSurfaceDesc* GetSurfaceDesc; // 0x00000058 length: 4
            undefined1 padding_0x5c[8]; // 0x0000005C length: 8
            Lock* Lock; // 0x00000064 length: 4
            undefined1 padding_0x68[4]; // 0x00000068 length: 4
            Restore* Restore; // 0x0000006C length: 4
            undefined1 padding_0x70[16]; // 0x00000070 length: 16
            Unlock* Unlock; // 0x00000080 length: 4

        } IDirectDrawSurface_VTABLE;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IDirectDrawSurface_VTABLE) == 132, IDirectDrawSurface_VTABLE);
    } // namespace IDirectDrawSurfaceInterface
} // namespace DirectDraw
} // namespace OpenSHC
