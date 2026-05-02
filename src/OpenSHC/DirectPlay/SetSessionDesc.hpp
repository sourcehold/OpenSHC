/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/SetSessionDesc.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/DPSESSIONDESC2.hpp"
#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::DPSESSIONDESC2;

    typedef HRESULT(__stdcall SetSessionDesc)(void*, DPSESSIONDESC2*, DWORD);
} // namespace DirectPlay
} // namespace OpenSHC
