/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/Receive.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/DPRECEIVE_EnumInt.hpp"
#include "WinDef.h"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::DPRECEIVE_EnumInt;

    typedef HRESULT(__stdcall Receive)(void*, undefined4, undefined4, DPRECEIVE_EnumInt, LPVOID, LPDWORD);
} // namespace DirectPlay
} // namespace OpenSHC
