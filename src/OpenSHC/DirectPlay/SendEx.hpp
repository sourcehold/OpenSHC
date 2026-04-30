/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/SendEx.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/DPSEND_EnumInt.hpp"
#include "WinDef.h"
#include "basetsd.h"
#include "winnt.h"
namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::DPSEND_EnumInt;

    typedef HRESULT(__stdcall SendEx)(
        void*, undefined4, undefined4, DPSEND_EnumInt, LPVOID, DWORD, DWORD, DWORD, LPVOID, DWORD_PTR*);
} // namespace DirectPlay
} // namespace OpenSHC
