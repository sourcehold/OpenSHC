/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectDraw/IDirectDrawInterface/IDirectDraw_VTABLE.hpp'
*/

#pragma once

#include "ddraw.h"

namespace OpenSHC {
namespace DirectDraw {
    namespace IDirectDrawInterface {

#pragma pack(push, 1)
        // SIZE: 0x00000058
        typedef struct IDirectDraw_VTABLE {

            undefined1 padding_0x0[8]; // 0x00000000 length: 8
            Release* Release; // 0x00000008 length: 4
            undefined1 padding_0xc[12]; // 0x0000000C length: 12
            CreateSurface* CreateSurface; // 0x00000018 length: 4
            undefined1 padding_0x1c[4]; // 0x0000001C length: 4
            EnumDisplayModes* EnumDisplayModes; // 0x00000020 length: 4
            undefined1 padding_0x24[8]; // 0x00000024 length: 8
            GetCaps* GetCaps; // 0x0000002C length: 4
            undefined1 padding_0x30[32]; // 0x00000030 length: 32
            SetCooperativeLevel* SetCooperativeLevel; // 0x00000050 length: 4
            SetDisplayMode* SetDisplayMode; // 0x00000054 length: 4

        } IDirectDraw_VTABLE;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(IDirectDraw_VTABLE) == 88, IDirectDraw_VTABLE);
    } // namespace IDirectDrawInterface
} // namespace DirectDraw
} // namespace OpenSHC
