/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

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
