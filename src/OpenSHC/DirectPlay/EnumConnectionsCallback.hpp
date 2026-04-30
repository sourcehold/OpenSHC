/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/EnumConnectionsCallback.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/DPNAME.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::DPNAME;

    typedef BOOL(__stdcall EnumConnectionsCallback)(LPCGUID, LPVOID, DWORD, DPNAME*, DWORD, LPVOID);
} // namespace DirectPlay
} // namespace OpenSHC
