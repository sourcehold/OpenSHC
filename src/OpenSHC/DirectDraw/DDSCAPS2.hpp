/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectDraw/DDSCAPS2.hpp'
*/

#pragma once

#include "WinDef.h"

namespace OpenSHC {
namespace DirectDraw {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct DDSCAPS2 {

        DWORD dwCaps; // 0x00000000 length: 4
        DWORD dwCaps2; // 0x00000004 length: 4
        DWORD dwCaps3; // 0x00000008 length: 4
        DWORD dwCaps4OrDwVolumeDepth; // 0x0000000C length: 4

    } DDSCAPS2;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DDSCAPS2) == 16, DDSCAPS2);
} // namespace DirectDraw
} // namespace OpenSHC
