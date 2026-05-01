/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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
