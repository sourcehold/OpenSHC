/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/Open.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/OpenFlagsEnumInt.hpp"
#include "OpenSHC/dplay/DPSESSIONDESC2.hpp"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::OpenFlagsEnumInt;
    using OpenSHC::dplay::DPSESSIONDESC2;

    typedef HRESULT(__stdcall Open)(void*, DPSESSIONDESC2*, OpenFlagsEnumInt);
} // namespace DirectPlay
} // namespace OpenSHC
