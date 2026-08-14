/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX.func.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX.hpp"
namespace OpenSHC {
namespace Audio {
    namespace SFX_Func {

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x0044A830,
            &OpenSHC::Audio::SFX::ComputePlayerPoints1)
        ComputePlayerPoints1;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int larger, int smaller), false, Address::SHC_3BB0A8C1_0x0044AAB0,
            &OpenSHC::Audio::SFX::UpdateUnitLossSpeechFeedback_RelativeValueForGenie)
        UpdateUnitLossSpeechFeedback_RelativeValueForGenie;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x0044B680,
            &OpenSHC::Audio::SFX::ComputePlayerRanking)
        ComputePlayerRanking;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0044B840,
            &OpenSHC::Audio::SFX::UpdateUnitLossSpeechFeedback)
        UpdateUnitLossSpeechFeedback;

        MACRO_FUNCTION_RESOLVER(int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0044C400,
            &OpenSHC::Audio::SFX::ComputeCurrentPlayerRanking)
        ComputeCurrentPlayerRanking;

    } // namespace SFX_Func
} // namespace Audio
} // namespace OpenSHC
