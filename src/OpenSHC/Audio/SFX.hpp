/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        int __cdecl ComputePlayerPoints1(int playerID);

        int __cdecl UpdateUnitLossSpeechFeedback_RelativeValueForGenie(int larger, int smaller);

        int __cdecl ComputePlayerRanking(int playerID);

        void __stdcall UpdateUnitLossSpeechFeedback();

        int __stdcall ComputeCurrentPlayerRanking();

    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
