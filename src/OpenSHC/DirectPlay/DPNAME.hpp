/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/DPNAME.hpp'
*/

#pragma once

#include "WinDef.h"
#include "winnt.h"

namespace OpenSHC {
namespace DirectPlay {

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef struct DPNAME {

        DWORD dwSize; // 0x00000000 length: 4
        DWORD dwFlags; // 0x00000004 length: 4
        LPWSTR lpszShortName; // 0x00000008 length: 4
        LPWSTR lpszLongName; // 0x0000000C length: 4

    } DPNAME;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DPNAME) == 16, DPNAME);
} // namespace DirectPlay
} // namespace OpenSHC
