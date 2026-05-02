/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectDraw/DDCOLORKEY.hpp'
*/

#pragma once

#include "WinDef.h"

namespace OpenSHC {
namespace DirectDraw {

#pragma pack(push, 1)
    // SIZE: 0x00000008
    typedef struct DDCOLORKEY {

        DWORD field0_0x0; // 0x00000000 length: 4
        DWORD field1_0x4; // 0x00000004 length: 4

    } DDCOLORKEY;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DDCOLORKEY) == 8, DDCOLORKEY);
} // namespace DirectDraw
} // namespace OpenSHC
