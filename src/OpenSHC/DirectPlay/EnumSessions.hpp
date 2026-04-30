/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/EnumSessions.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnumInt.hpp"
#include "OpenSHC/dplay/DPSESSIONDESC2.hpp"
#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::EnumSessionsFlagsEnumInt;
    using OpenSHC::dplay::DPSESSIONDESC2;

    typedef HRESULT(__stdcall EnumSessions)(
        void*, DPSESSIONDESC2*, DWORD, undefined4, LPVOID, EnumSessionsFlagsEnumInt);
} // namespace DirectPlay
} // namespace OpenSHC
