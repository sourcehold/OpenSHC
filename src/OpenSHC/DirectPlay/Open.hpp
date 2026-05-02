/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectPlay/Open.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/OpenFlagsEnumInt.hpp"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::OpenFlagsEnumInt;

    typedef HRESULT(__stdcall Open)(void*, void*, OpenFlagsEnumInt);
} // namespace DirectPlay
} // namespace OpenSHC
