/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/DPSESSIONDESC2.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/DPSESSION_EnumInt.hpp"
#include "WinDef.h"
#include "basetsd.h"
#include "guiddef.h"
#include "winnt.h"

namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::DPSESSION_EnumInt;

#pragma pack(push, 1)
    // SIZE: 0x00000050
    typedef struct DPSESSIONDESC2 {

        DWORD dwSize; // 0x00000000 length: 4
        DPSESSION_EnumInt dwFlags; // 0x00000004 length: 4
        GUID guidInstance; // 0x00000008 length: 16
        GUID guidApplication; // 0x00000018 length: 16
        DWORD dwMaxPlayers; // 0x00000028 length: 4
        DWORD dwCurrentPlayers; // 0x0000002C length: 4
        LPWSTR lpszSessionName; // 0x00000030 length: 4
        LPWSTR lpszPassword; // 0x00000034 length: 4
        DWORD_PTR dwReserved1; // 0x00000038 length: 4
        DWORD_PTR dwReserved2; // 0x0000003C length: 4
        DWORD_PTR dwUser1; // 0x00000040 length: 4
        DWORD_PTR dwUser2; // 0x00000044 length: 4
        DWORD_PTR dwUser3; // 0x00000048 length: 4
        DWORD_PTR dwUser4; // 0x0000004C length: 4

    } DPSESSIONDESC2;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(DPSESSIONDESC2) == 80, DPSESSIONDESC2);
} // namespace DirectPlay
} // namespace OpenSHC
