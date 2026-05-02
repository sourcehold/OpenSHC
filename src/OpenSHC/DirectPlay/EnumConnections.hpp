/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/EnumConnections.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/EnumConnectionsCallback.hpp"
#include "OpenSHC/DirectPlay/IDirectPlay4A.hpp"
#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::EnumConnectionsCallback;
    using OpenSHC::DirectPlay::IDirectPlay4A;

    typedef HRESULT(__stdcall EnumConnections)(IDirectPlay4A*, LPCGUID, EnumConnectionsCallback*, LPVOID, DWORD);
} // namespace DirectPlay
} // namespace OpenSHC
