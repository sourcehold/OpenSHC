/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/mss.func.hpp'
*/

#pragma once

#include "OpenSHC/Audio/mss.hpp"
#include "WinDef.h"
#include "basetsd.h"
namespace OpenSHC {
namespace Audio {
    namespace mss_Func {

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2), false,
            Address::SHC_3BB0A8C1_0x0047B510, &OpenSHC::Audio::mss::SndSystemTimeCallback)
        SndSystemTimeCallback;

        MACRO_FUNCTION_RESOLVER(undefined4(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0057E160,
            &OpenSHC::Audio::mss::RegisterMilesAILShutdown)
        RegisterMilesAILShutdown;

    } // namespace mss_Func
} // namespace Audio
} // namespace OpenSHC
