/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

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
