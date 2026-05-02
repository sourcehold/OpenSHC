/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/mss.hpp'
*/

#pragma once

#include "WinDef.h"
#include "basetsd.h"
namespace OpenSHC {
namespace Audio {
    namespace mss {

        void __stdcall SndSystemTimeCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

        undefined4 __stdcall RegisterMilesAILShutdown();

    } // namespace mss
} // namespace Audio
} // namespace OpenSHC
