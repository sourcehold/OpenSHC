/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/CreatePlayer.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/DPNAME.hpp"
#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::DPNAME;

    typedef HRESULT(__stdcall CreatePlayer)(void*, undefined4, DPNAME*, HANDLE, LPVOID, DWORD, DWORD);
} // namespace DirectPlay
} // namespace OpenSHC
