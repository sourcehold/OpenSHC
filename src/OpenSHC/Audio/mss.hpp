/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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
