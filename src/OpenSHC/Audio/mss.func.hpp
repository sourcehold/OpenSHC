/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MSS.func.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS.hpp"

#include "WinDef.h"
#include "basetsd.h"
namespace OpenSHC {
namespace Audio {
    namespace MSS_Func {

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2), false,
            Address::SHC_3BB0A8C1_0x0047B510, &OpenSHC::Audio::MSS::SndSystemTimeCallback)
        SndSystemTimeCallback;

        MACRO_FUNCTION_RESOLVER(
            int(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0057E160, &OpenSHC::Audio::MSS::RegisterMilesAILShutdown)
        RegisterMilesAILShutdown;

    } // namespace MSS_Func
} // namespace Audio
} // namespace OpenSHC
