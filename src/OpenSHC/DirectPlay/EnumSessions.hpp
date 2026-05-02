/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/EnumSessions.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnumInt.hpp"
#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::EnumSessionsFlagsEnumInt;

    typedef HRESULT(__stdcall EnumSessions)(void*, void*, DWORD, undefined4, LPVOID, EnumSessionsFlagsEnumInt);
} // namespace DirectPlay
} // namespace OpenSHC
